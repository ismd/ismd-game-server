#include "lib/Character.h"
#include "lib/Database.h"

extern Database* db;

Character::Character(int id)
{
    _info = db->character(id);
    _items = db->characterItems(id);
}

QVariantMap Character::info()
{
    return _info;
}

int Character::coordinateX()
{
    return _info["coordinateX"].toInt();
}

int Character::coordinateY()
{
    return _info["coordinateY"].toInt();
}

void Character::setCoordinates(int x, int y)
{
    _info["coordinateX"] = x;
    _info["coordinateY"] = y;

    db->setCoordinates(_id, x, y);
}

void Character::appendQuest(Quest* quest)
{
    _quests.append(quest);
}

QList<Quest*> Character::quests()
{
    return _quests;
}

QList<Item*> Character::items()
{
    return _items;
}
