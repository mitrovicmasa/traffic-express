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

    //to pp
    void playerChoseWagon(int playerIndex,int wagonIndex);
    void playerPlayedCard(int playerIndex,int CardIndex);
    void playerDrawCards(int playerIndex);


public slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

    void onClickedReady();
    void onClickedStart();

    //pp reacts
    void onPlayerChoseWagon(int playerIndex,int wagonIndex);
    void onPlayerPlayedCard(int playerIndex,int CardIndex);
    void onPlayerDrawCards(int playerIndex);




private:
    QTcpSocket *m_clientSocket;
    PlayerPerspective*m_pp;
    std::vector<QString>m_names;
    int m_index;
    std::vector<bool>m_ready;
    bool m_isHost;
    QString m_username;
    bool m_gameIncoming;
    bool m_gameOngoing;


};

#endif // PLAYERCLIENT_H
