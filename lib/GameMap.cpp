#include "lib/GameMap.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>
#include "lib/Database.h"
#include "lib/Mob.h"

extern Database* db;

GameMap::GameMap()
{
    initMap();
    initNpcs();
    initMobs();
}

void GameMap::initMap()
{
    qDebug() << "Initializing map";

    QFile mapFile("init/map.txt");
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: can't initialize map";
        return;
    }

    QVector<QByteArray> reversedMap;
    while (!mapFile.atEnd())
        reversedMap.append(mapFile.readLine().trimmed());

    // Reversing map
    for (int j = 0; j < reversedMap[0].size(); j++) {
        QVector<MapCell*> tmp;

        for (int i = 0; i < reversedMap.size(); i++) {
            int type = reversedMap[i][j] - '0' ? reversedMap[i][j] - '0' : 0;
            tmp.append(new MapCell(type));
        }

        _map.append(tmp);
    }

    qDebug() << "Map was initialized";

    // Debugging map
//    qDebug() << "Reversed map:";
//    for (int i = 0; i < _map.size(); i++)
//        qDebug() << _map[i];
}

void GameMap::initNpcs()
{
    QDir npcsDir("init/npcs");
    QStringList npcsFiles = npcsDir.entryList();

    foreach (QString name, npcsFiles) {
        if (name == "." || name == "..")
            continue;

        qDebug() << "Adding NPC `" + name + "'";

        QFile npcFile("init/npcs/" + name);
        if (!npcFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error: can't initialize NPC `" + name + "'";
            continue;
        }

        // Reading lines:
        // 1. coordinates
        // 2. ids of quests
        QString coordinates = npcFile.readLine().trimmed();
        QString questsStr = QString::fromUtf8(npcFile.readLine().trimmed());

        QStringList coords = coordinates.split(',');
        int x = coords.at(0).toInt();
        int y = coords.at(1).toInt();
        int idNpc = _npcs.size();

        Npc* npc = new Npc(idNpc, name, x, y);

        QStringList idQuests = questsStr.split(',');
        foreach (QString idQuest, idQuests) {
            QFile questFile("init/quests/" + idQuest);

            if (!questFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Error: can't initialize quest with id " + idQuest;
                continue;
            }

            QString title = QString::fromUtf8(questFile.readLine().trimmed());
            QString text = QString::fromUtf8(questFile.readLine().trimmed());

            Quest* quest = new Quest(idQuest.toInt(), title, text);

            npc->appendQuest(quest);
            _quests.append(quest);

            qDebug() << "Quest with id " + idQuest + " was added";
        }

        _map[x][y]->appendNpc(npc);
        _npcs.append(npc);

        qDebug() << "Success";
    }
}

void GameMap::initMobs()
{
    QList<Mob*> mobs = db->mobs();

    foreach (Mob* mob, mobs) {
        qDebug() << "Adding mob `" + mob->title() + "'";

        for (int i = 0; i < mob->maxOnMap(); i++) {
            coord c = mob->randomAvailableCoord();

            _map[c.x][c.y]->appendMob(mob);
        }
    }
}

MapCell* GameMap::cell(int x, int y)
{
    if (x < 0 || x >= _map.size())
        return new MapCell(0);

    if (y < 0 || y >= _map.at(x).size())
        return new MapCell(0);

    return _map[x][y];
}

Npc* GameMap::npc(int id)
{
    if (id < 0 || id >= _npcs.size())
        return new Npc(-1, "", -1, -1);

    if (_npcs.at(id)->id() != id) {
        qDebug() << "Error: bad initialization of NPC `" + _npcs.at(id)->name() + "'";
        return new Npc(-1, "", -1, -1);
    }

    return _npcs.at(id);
}

Quest* GameMap::quest(int id)
{
    if (id < 0 || id >= _quests.size())
        return new Quest(-1, "", "");

    if (_quests.at(id)->id() != id) {
        qDebug() << "Error: bad initialization of quest id=" + QString::number(_quests.at(id)->id());
        return new Quest(-1, "", "");
    }

    return _quests.at(id);
}
