#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include "lib/GameMap.h"
#include "lib/Client.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(int socketNumber, QObject *parent = 0);

private slots:
    void slotNewConnection();

private:
    int _socketNumber;
    QTcpServer* _server;
    QMap<QTcpSocket*, Client*> _clients;
    GameMap* _map;
};

#endif // SERVER_H
