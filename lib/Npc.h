#ifndef NPC_H
#define NPC_H

#include <QStringList>
#include "lib/Quest.h"
#include "lib/Item.h"

class Npc
{
public:
    Npc(int id, QString name, int x, int y);
    int id();
    QString name();
    int coordinateX();
    int coordinateY();
    QList<Quest*> quests();
    QList<Item*> items();
    void appendQuest(Quest* quest);

private:
    int _id;
    QString _name;
    int _coordinateX;
    int _coordinateY;
    QList<Quest*> _quests;
    QList<Item*> _items;
};

#endif // NPC_H
