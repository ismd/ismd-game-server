#ifndef MAPCELL_H
#define MAPCELL_H

#include <QList>
#include "lib/Npc.h"
#include "lib/Mob.h"

class MapCell
{
public:
    MapCell(int type);
    int type();
    void appendNpc(Npc*);
    void appendMob(Mob*);
    QList<Npc*> npcs();
    QList<Mob*> mobs();

private:
    int _type;
    QList<Npc*> _npcs;
    QList<Mob*> _mobs;
};

#endif // MAPCELL_H
