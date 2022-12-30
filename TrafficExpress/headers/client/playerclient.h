#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <playerperspective.h>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class PlayerClient : public QObject
{
    Q_OBJECT
public:
    explicit PlayerClient(QObject *parent = nullptr);
    void startClient();
    void sendMessage(QString message);

    bool getHost();
    int getIndex();
    QString getUsername();
    PlayerPerspective*getPlayerPerspective();

    void setUsername(QString);

    bool allReady();

signals:
    void changeReadyColor(bool);
    void changeStartColor();

    void gameLoaded();

public slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

    void onClickedReady();
    void onClickedStart();

private:
    QTcpSocket *m_clientSocket;
    PlayerPerspective*m_pp;
    std::vector<QString>m_names;
    int m_index;
    std::vector<bool>m_ready;
    bool m_isHost;
    QString m_username;
    bool m_gameIncoming;


};

#endif // PLAYERCLIENT_H
