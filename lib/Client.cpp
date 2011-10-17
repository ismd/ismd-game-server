#include <QTime>
#include <QHostAddress>
#include "lib/Client.h"
#include "lib/Database.h"

extern Database* db;

Client::Client(QTcpSocket* socket, GameMap* map, QObject *parent) :
    QObject(parent),
    _socket(socket),
    _nextBlockSize(0),
    _map(map)
{
}

void Client::sendMessage(const QString &message, const QVariant &args)
{
    // It's for emulating network delay
//    QTest::qSleep(2000);

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << quint16(0) << QTime::currentTime() << message << args;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    _socket->write(arrBlock);

    qDebug() << QDateTime::currentDateTime().toString() + "\t" + _socket->peerAddress().toString() +
                "\t" + "SEND: " + message;
}

void Client::slotRead()
{
    QDataStream in(_socket);
    in.setVersion(QDataStream::Qt_4_7);

    for (;;) {
        if (!_nextBlockSize) {
            if (_socket->bytesAvailable() < sizeof(quint16))
                break;

            in >> _nextBlockSize;
        }

        if (_socket->bytesAvailable() < _nextBlockSize)
            break;

        QString message;
        QVariant args;

        in >> message >> args;

        qDebug() << QDateTime::currentDateTime().toString() + "\t" + _socket->peerAddress().toString() +
                    "\t" + "RECEIVE: " + message;

        parseRequest(message, args);

        _nextBlockSize = 0;
    }
}

/**
 * Request processor
 * Parses request from client, makes needed instructions and sends responses
 */
void Client::parseRequest(const QString& message, const QVariant& args)
{
    // auth
    if (message == "reqAuth") {
        QVariantMap arg = args.toMap();
        QString login = arg["login"].toString();
        QString password = arg["password"].toString();

        int idUser = db->auth(login, password);
        if (idUser != -1) {
            _user = new User(idUser);

            // FIXME: it must be correct initialization of Character here
            _character = new Character(idUser);
        }

        sendMessage("rspAuth", (idUser != -1 ? true : false));
    // character info
    } else if (message == "reqCharacterInfo") {
        QVariantMap info = _character->info();
        sendMessage("rspCharacterInfo", info);
    // get quest
    } else if (message == "reqGetQuest") {
        QVariantMap arg = args.toMap();
        int idNpc = arg["idNpc"].toInt();
        int idQuest = arg["idQuest"].toInt();

        Npc* npc = _map->npc(idNpc);
        Quest* quest = _map->quest(idQuest);

        if (_character->coordinateX() != npc->coordinateX() ||
                _character->coordinateY() != npc->coordinateY())
            return;

        if (!npc->quests().contains(quest))
            return;

        _character->appendQuest(quest);
        // TODO: check if user already have this quest

        sendMessage("rspGetQuest", QVariant());
    // quests
    } else if (message == "reqQuests") {
        QList<Quest*> quests = _character->quests();
        QVariantList s_arg;

        foreach (Quest* quest, quests) {
            QVariantMap q;

            q["id"] = quest->id();
            q["title"] = quest->title();
            q["text"] = quest->text();

            s_arg.append(q);
        }

        sendMessage("rspQuests", s_arg);
    // move
    } else if (message == "reqMove") {
        QVariantMap arg = args.toMap();
        int dx = arg["dx"].toInt();
        int dy = arg["dy"].toInt();
        int oldX = _character->coordinateX();
        int oldY = _character->coordinateY();
        bool goodMoving = false;

        if ((qAbs(dx) == 1 && dy == 0) || (dx == 0 && qAbs(dy) == 1)) {
            int newX = oldX + dx;
            int newY = oldY + dy;

            // checking if map[x][y] is available
            if (_map->cell(newX, newY)->type() == 1) {
                _character->setCoordinates(newX, newY);
                sendMessage("rspMove", args);
                goodMoving = true;

                sendCellContent();
            }
        }

        if (!goodMoving) {
            QVariantMap s_arg;
            s_arg["dx"] = 0;
            s_arg["dy"] = 0;

            sendMessage("rspMove", s_arg);
        }
    // cell content
    } else if (message == "reqCellContent") {
        sendCellContent();
    // character items
    } else if (message == "reqCharacterItems") {
        QList<Item*> items = _character->items();
        QVariantList s_arg;

        foreach (Item* item, items)
            s_arg.append(item->info());

        sendMessage("rspCharacterItems", s_arg);
    // unknown
    } else
        qDebug() << QTime::currentTime().toString() + "\t" + _socket->peerAddress().toString() +
                    "\t" + "Unknown request: " + message;
}

void Client::sendCellContent()
{
    int coordX = _character->coordinateX();
    int coordY = _character->coordinateY();
    QVariantMap s_arg;

    // NPCs
    QList<Npc*> npcs = _map->cell(coordX, coordY)->npcs();
    QVariantList npcsList;

    foreach (Npc* npc, npcs) {
        QVariantMap npcInfo;
        npcInfo["id"] = npc->id();
        npcInfo["name"] = npc->name();

        // Quests
        QVariantList quests;
        foreach (Quest* quest, npc->quests()) {
            QVariantMap questInfo;
            questInfo["id"] = quest->id();
            questInfo["title"] = quest->title();
            questInfo["text"] = quest->text();

            quests.append(questInfo);
        }

        npcInfo["quests"] = quests;

        // Items
        QVariantList items;
        foreach (Item* item, npc->items()) {
            QVariantMap itemInfo;
            itemInfo["id"] = item->id();
            itemInfo["title"] = item->title();
            itemInfo["idType"] = item->idType();
            itemInfo["price"] = item->price();
            itemInfo["description"] = item->description();

            items.append(itemInfo);
        }

        npcInfo["items"] = items;

        npcsList.append(npcInfo);
    }

    s_arg["npcs"] = npcsList;

    // Mobs
    QList<Mob*> mobs = _map->cell(coordX, coordY)->mobs();
    QVariantList mobsList;

    foreach (Mob* mob, mobs) {
        QVariantMap mobInfo;
        mobInfo["title"] = mob->title();
        mobInfo["hp"] = mob->hp();
        mobInfo["maxHp"] = mob->maxHp();
        mobInfo["damage"] = mob->damage();
        mobInfo["experience"] = mob->experience();

        mobsList.append(mobInfo);
    }

    s_arg["mobs"] = mobsList;

    sendMessage("rspCellContent", s_arg);
}
