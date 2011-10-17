#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QList>
#include "lib/Mob.h"
#include "lib/Item.h"

class Database
{
public:
    Database();
    int auth(QString, QString);
    QVariantMap user(int id);
    QVariantMap character(int id);
    void setCoordinates(int idCharacter, int x, int y);
    QList<Mob*> mobs();
    QList<Item*> characterItems(int idCharacter);
    QList<Item*> npcItems(int idNpc);
};

#endif // DATABASE_H
