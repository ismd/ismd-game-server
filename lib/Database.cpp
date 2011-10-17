#include "lib/Database.h"

Database::Database()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("game");
    db.setUserName("root");
    db.setHostName("localhost");
    db.setPassword("123");

    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        exit(0);
    }
}

/**
 * Returns idUser or -1 if not authed
 */
int Database::auth(QString login, QString password)
{
    QSqlQuery query("SELECT `id` FROM `User` WHERE `login`='" + login +
                    "' AND `password`='" + password + "' LIMIT 1");

    if (query.next()) {
        QSqlRecord rec = query.record();
        return query.value(rec.indexOf("id")).toInt();
    } else
        return -1;
}

QVariantMap Database::user(int id)
{
    QVariantMap result;
    QSqlQuery query("SELECT * FROM `User` WHERE `id`=" + QString::number(id) + " LIMIT 1");

    if (query.next()) {
        QSqlRecord rec = query.record();

        result["login"] = query.value(rec.indexOf("login")).toString();
        result["email"] = query.value(rec.indexOf("email")).toString();
        result["info"] = query.value(rec.indexOf("info")).toString();
        result["site"] = query.value(rec.indexOf("site")).toString();
        result["regDateTime"] = query.value(rec.indexOf("regDateTime")).toDateTime();

    } else {
        result["login"] = "";
        result["email"] = "";
        result["info"] = "";
        result["site"] = "";
        result["regDateTime"] = QDateTime::currentDateTime();
    }

    return result;
}

QVariantMap Database::character(int id)
{
    QVariantMap result;
    QSqlQuery query("SELECT * FROM `Character` WHERE `id`=" + QString::number(id) + " LIMIT 1");

    if (query.next()) {
        QSqlRecord rec = query.record();

        result["name"] = query.value(rec.indexOf("name")).toString();
        result["level"] = query.value(rec.indexOf("level")).toInt();
        result["money"] = query.value(rec.indexOf("money")).toInt();
        result["coordinateX"] = query.value(rec.indexOf("coordinateX")).toInt();
        result["coordinateY"] = query.value(rec.indexOf("coordinateY")).toInt();
        result["avatar"] = query.value(rec.indexOf("avatar")).toString();
    } else {
        result["name"] = "";
        result["level"] = 0;
        result["money"] = 0;
        result["coordinateX"] = 0;
        result["coordinateY"] = 0;
        result["avatar"] = "";
    }

    return result;
}

void Database::setCoordinates(int idCharacter, int x, int y)
{
    QSqlQuery query;
    query.prepare("UPDATE `Character` SET `coordinateX`=:x, `coordinateY`=:y WHERE `id`=:id LIMIT 1");
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":id", idCharacter);
    query.exec();
}

QList<Mob*> Database::mobs()
{
    QList<Mob*> mobs;
    QSqlQuery query("SELECT * FROM `Mob`");

    while (query.next()) {
        int id = query.record().value("id").toInt();
        QString title = query.record().value("title").toString();
        int maxHp = query.record().value("hp").toInt();
        int damage = query.record().value("damage").toInt();
        int maxOnMap = query.record().value("maxOnMap").toInt();
        int experience = query.record().value("experience").toInt();

        Mob* mob = new Mob(title, maxHp, damage, maxOnMap, experience);

        QSqlQuery query1("SELECT * FROM `MobCell` WHERE `idMob`=" + QString::number(id));
        while (query1.next()) {
            int x = query1.record().value("coordinateX").toInt();
            int y = query1.record().value("coordinateY").toInt();

            mob->appendAvailableCoord(x, y);
        }

        mobs.append(mob);
    }

    return mobs;
}

QList<Item*> Database::characterItems(int idCharacter)
{
    // FIXME: it's better to store items in memory and to get only the item's id from db
    QList<Item*> items;
    QString queryStr;
    queryStr = "SELECT Item.id, Item.title, Item.idType, Item.price, Item.description FROM CharacterItem ";
    queryStr += "INNER JOIN Item ON CharacterItem.idItem=Item.id WHERE idCharacter=";
    queryStr += QString::number(idCharacter);
    QSqlQuery query(queryStr);

    while (query.next()) {
        int id = query.record().value("id").toInt();
        QString title = query.record().value("title").toString();
        int idType = query.record().value("idType").toInt();
        int price = query.record().value("price").toInt();
        QString description = query.record().value("description").toString();

        items.append(new Item(id, title, idType, price, description));
    }

    return items;
}

QList<Item*> Database::npcItems(int idNpc)
{
    QList<Item*> items;
    QSqlQuery query(QString("SELECT Item.id, Item.title, Item.idType, Item.price, Item.description FROM NpcItem ") +
                    QString("INNER JOIN Item ON NpcItem.idItem=Item.id WHERE idNpc=") +
                    QString::number(idNpc));

    while (query.next()) {
        int id = query.record().value("id").toInt();
        QString title = query.record().value("title").toString();
        int idType = query.record().value("idType").toInt();
        int price = query.record().value("price").toInt();
        QString description = query.record().value("description").toString();

        items.append(new Item(id, title, idType, price, description));
    }

    return items;
}
