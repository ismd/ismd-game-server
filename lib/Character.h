#ifndef CHARACTER_H
#define CHARACTER_H

#include <QVariantMap>
#include "lib/Quest.h"
#include "lib/Item.h"

class Character
{
public:
    Character(int id);
    QVariantMap info();
    int coordinateX();
    int coordinateY();
    void setCoordinates(int x, int y);
    void appendQuest(Quest*);
    QList<Quest*> quests();
    QList<Item*> items();

private:
    int _id;
    QVariantMap _info;
    QList<Quest*> _quests;
    QList<Item*> _items;
};

#endif // CHARACTER_H
