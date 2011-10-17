#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "lib/User.h"
#include "lib/Character.h"
#include "lib/GameMap.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* socket, GameMap* map, QObject *parent = 0);

public slots:
    void slotRead();

private:
    QTcpSocket* _socket;
    quint16 _nextBlockSize;
    void sendMessage(const QString& message, const QVariant& args);
    void parseRequest(const QString& message, const QVariant& args);
    void sendCellContent();
    User* _user;
    Character* _character;
    GameMap* _map;
};

#endif // CLIENT_H
