#include "lib/Item.h"

Item::Item(int id, QString title, int idType, int price, QString description) :
    _id(id),
    _title(title),
    _idType(idType),
    _price(price),
    _description(description)
{
}

QVariantMap Item::info()
{
    QVariantMap info;

    info["title"] = _title;
    info["idType"] = _idType;
    info["price"] = _price;
    info["description"] = _description;

    return info;
}

int Item::id()
{
    return _id;
}

QString Item::title()
{
    return _title;
}

int Item::idType()
{
    return _idType;
}

int Item::price()
{
    return _price;
}

QString Item::description()
{
    return _description;
}
