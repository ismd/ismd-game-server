#include "lib/User.h"
#include "lib/Database.h"

extern Database* db;

User::User(int id) :
    _id(id)
{
    _info = db->user(id);
}

QVariantMap User::info()
{
    return _info;
}
