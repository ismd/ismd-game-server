#ifndef MOB_H
#define MOB_H

#include <QString>
#include <QList>

struct coord {
    int x;
    int y;
};

class Mob
{
public:
    Mob(QString title, int maxHp, int damage, int maxOnMap, int experience);
    QString title();
    int hp();
    int maxHp();
    int damage();
    int maxOnMap();
    int experience();
    void appendAvailableCoord(int x, int y);
    coord randomAvailableCoord();

private:
    QString _title;
    int _hp;
    int _maxHp;
    int _damage;
    int _maxOnMap;
    int _experience;
    QList<coord> _availableCoords;
};

#endif // MOB_H
