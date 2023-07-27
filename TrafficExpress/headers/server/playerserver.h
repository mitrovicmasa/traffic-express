#ifndef PLAYERSERVER_H
#define PLAYERSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class PlayerServer : public QObject {
  Q_OBJECT

 public:
  explicit PlayerServer(QObject *parent = nullptr);

  void startServer();
  void sendMessage(QTcpSocket *soc, QString message);
  int findSocketIndex(QTcpSocket *);

 public slots:
  void onNewConection();
  void onReadyRead();
  void onDisconnect();

 private:
  QTcpServer *m_server;
  std::vector<QTcpSocket *> m_clients;
  std::vector<QString> m_names;
  std::vector<bool> m_firstConnect;
  std::vector<bool> m_ready;
  bool m_gameOngoing;
  bool m_gameToCome;

 signals:
};

#endif  // PLAYERSERVER_H
