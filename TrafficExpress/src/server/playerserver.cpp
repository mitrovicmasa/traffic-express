#include "../../headers/server/playerserver.h"

PlayerServer::PlayerServer(QObject *parent) : QObject{parent} {}

void PlayerServer::startServer() {
  m_gameOngoing = false;
  m_gameToCome = false;
  m_server = new QTcpServer();
  m_clients = std::vector<QTcpSocket *>();
  m_server->setMaxPendingConnections(4);
  if (!m_server->listen(QHostAddress::Any, 12345)) {
    qDebug() << "serever could not start";
  } else {
    qDebug() << "server started";
  }
  connect(m_server, &QTcpServer::newConnection, this,
          &PlayerServer::onNewConection);
}

void PlayerServer::sendMessage(QTcpSocket *soc, QString message) {
  soc->write(message.toUtf8());
  soc->flush();
  soc->waitForReadyRead(-1);
  // soc->waitForBytesWritten(-1);
}

int PlayerServer::findSocketIndex(QTcpSocket *client) {
  for (int i = 0; i < m_clients.size(); i++) {
    if (m_clients[i] == client) return i;
  }

  return -1;
}

void PlayerServer::onNewConection() {
  QTcpSocket *client = m_server->nextPendingConnection();
  if (m_gameOngoing || m_gameToCome || m_clients.size() >= 4) {
    client->disconnect();
    return;
  }

  m_clients.push_back(client);
  m_ready.push_back(false);
  m_firstConnect.push_back(true);

  connect(client, &QTcpSocket::disconnected, this, &PlayerServer::onDisconnect);
  connect(client, &QTcpSocket::readyRead, this, &PlayerServer::onReadyRead);
}

void PlayerServer::onReadyRead() {
  qDebug() << "ReadyRead";

  auto *client = qobject_cast<QTcpSocket *>(QObject::sender());
  int playerIndex = findSocketIndex(client);

  QString message(client->readAll());
  qDebug() << "PlayerIndex:" << playerIndex;
  message = message.trimmed();
  qDebug() << message;

  if (m_gameOngoing && message != "") {
    for (int i = 0; i < m_clients.size(); i++) {
      if (i != playerIndex) this->sendMessage(m_clients[i], message);
    }
  }

  if (m_gameToCome && playerIndex == 0) {
    qDebug() << "GameToCome";
    m_gameToCome = false;
    m_gameOngoing = true;
    for (int i = 0; i < m_clients.size(); i++) {
      if (i != playerIndex) this->sendMessage(m_clients[i], message);
    }
  }

  if (m_firstConnect[playerIndex]) {
    qDebug() << "frst con";
    m_firstConnect[playerIndex] = false;

    m_names.push_back(message);

    QString s = "host";
    if (client != m_clients[0]) s = "!" + s;
    this->sendMessage(client, s);

    for (int i = 0; i < m_clients.size(); i++) {
      if (i != playerIndex) {
        QString ready = "0";
        if (m_ready[i]) ready = "1";
        this->sendMessage(m_clients[i], "cc:" + message);
        this->sendMessage(m_clients[playerIndex],
                          "ac:" + m_names[i] + ":" + ready);
      }
    }
    this->sendMessage(m_clients[playerIndex], "nomoreac:");
    // return;
  } else {
    if (message.startsWith("start:")) {
      m_gameToCome = true;
      for (int i = 0; i < m_clients.size(); i++) {
        if (i != playerIndex) this->sendMessage(m_clients[i], "start:");
      }
    }
    if (message.startsWith("ready:") && !m_gameOngoing) {
      qDebug() << "ready:" << playerIndex;
      m_ready[playerIndex] = !m_ready[playerIndex];
      for (int i = 0; i < m_clients.size(); i++) {
        if (i != playerIndex)
          this->sendMessage(m_clients[i],
                            "ready:" + QString::number(playerIndex));
      }
    }
  }
}

void PlayerServer::onDisconnect() {
  auto *client = qobject_cast<QTcpSocket *>(QObject::sender());
  int playerIndex = findSocketIndex(client);

  m_gameOngoing = false;
  m_gameToCome = false;

  m_clients.erase(m_clients.begin() + playerIndex);
  m_firstConnect.erase(m_firstConnect.begin() + playerIndex);
  m_names.erase(m_names.begin() + playerIndex);
  m_ready.erase(m_ready.begin() + playerIndex);
  client->deleteLater();
  for (auto &m_client : m_clients)
    this->sendMessage(m_client, "dc:" + QString::number(playerIndex));

  if (!m_clients.empty()) this->sendMessage(m_clients[0], "host");
}
