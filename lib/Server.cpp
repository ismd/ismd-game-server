#include <QTcpSocket>
#include "lib/Server.h"

Server::Server(int socketNumber, QObject *parent) :
    QObject(parent),
    _socketNumber(socketNumber)
{
    _map = new GameMap;
    _server = new QTcpServer(this);

    if (!_server->listen(QHostAddress::Any, _socketNumber)) {
        qDebug() << "Server error. Unable to start the server:" <<
                     _server->errorString();

        _server->close();
        return;
    }

    connect(_server, SIGNAL(newConnection()), SLOT(slotNewConnection()));
}

void Server::slotNewConnection()
{
    QTcpSocket* clientSocket = _server->nextPendingConnection();
    _clients[clientSocket] = new Client(clientSocket, _map, this);

    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()), _clients[clientSocket], SLOT(slotRead()));
}
