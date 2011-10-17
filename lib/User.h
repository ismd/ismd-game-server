#ifndef USER_H
#define USER_H

#include <QVariantMap>

class User
{
public:
    User(int id);
    QVariantMap info();

private:
    int _id;
    QVariantMap _info;
};

#endif // USER_H
