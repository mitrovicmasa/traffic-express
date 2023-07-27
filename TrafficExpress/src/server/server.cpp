#include <server/playerserver.h>

#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  auto *server = new PlayerServer();
  server->startServer();

  return a.exec();
}
