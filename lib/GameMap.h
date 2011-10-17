#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QVector>
#include "lib/MapCell.h"
#include "lib/Npc.h"
#include "lib/Quest.h"

class GameMap
{
public:
    GameMap();
    MapCell* cell(int x, int y);
    Npc* npc(int id);
    Quest* quest(int id);

private:
    void initMap();
    void initNpcs();
    void initMobs();
    QVector<QVector<MapCell*> > _map;
    QVector<Npc*> _npcs;
    QVector<Quest*> _quests;
};

#endif // GAMEMAP_H
