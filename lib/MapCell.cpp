#include "lib/MapCell.h"

MapCell::MapCell(int type)
{
    _type = type;
}

int MapCell::type()
{
    return _type;
}

void MapCell::appendNpc(Npc* npc)
{
    _npcs.append(npc);
}

void MapCell::appendMob(Mob* mob)
{
    _mobs.append(mob);
}

QList<Npc*> MapCell::npcs()
{
    return _npcs;
}

QList<Mob*> MapCell::mobs()
{
    return _mobs;
}
