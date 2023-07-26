#include <QCoreApplication>

#include <server/playerserver.h>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto*server=new PlayerServer();
    server->startServer();

    return a.exec();
}
