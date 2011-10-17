#include <QtCore/QCoreApplication>
#include "lib/Server.h"
#include "lib/Database.h"

Database* db = new Database;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server svr(2327);

    return a.exec();
}
