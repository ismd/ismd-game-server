#include "lib/Npc.h"
#include "lib/Database.h"

extern Database* db;

Npc::Npc(int id, QString name, int x, int y) :
    _id(id),
    _name(name),
    _coordinateX(x),
    _coordinateY(y)
{
    _items = db->npcItems(id);
}

int Npc::id()
{
    return _id;
}

QString Npc::name()
{
    return _name;
}

int Npc::coordinateX()
{
    return _coordinateX;
}

int Npc::coordinateY()
{
    return _coordinateY;
}

QList<Quest*> Npc::quests()
{
    return _quests;
}

QList<Item*> Npc::items()
{
    return _items;
}

void Npc::appendQuest(Quest* quest)
{
    _quests.append(quest);
}
