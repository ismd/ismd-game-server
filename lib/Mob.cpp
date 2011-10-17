#include <QTime>
#include "lib/Mob.h"

Mob::Mob(QString title, int maxHp, int damage, int maxOnMap, int experience) :
    _title(title),
    _hp(maxHp),
    _maxHp(maxHp),
    _damage(damage),
    _maxOnMap(maxOnMap),
    _experience(experience)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

QString Mob::title()
{
    return _title;
}

int Mob::hp()
{
    return _hp;
}

int Mob::maxHp()
{
    return _maxHp;
}

int Mob::damage()
{
    return _damage;
}

int Mob::maxOnMap()
{
    return _maxOnMap;
}

int Mob::experience()
{
    return _experience;
}

void Mob::appendAvailableCoord(int x, int y)
{
    coord c;
    c.x = x;
    c.y = y;

    _availableCoords.append(c);
}

coord Mob::randomAvailableCoord()
{
    coord currCoord;
    int c = qrand() % _availableCoords.size();

    currCoord.x = _availableCoords.at(c).x;
    currCoord.y = _availableCoords.at(c).y;

    return currCoord;
}
