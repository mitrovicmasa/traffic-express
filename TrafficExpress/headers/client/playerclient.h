#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <playerperspective.h>

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
    void setUsername(QString);

    bool allReady();

signals:
    void changeReadyColor(bool);
    void changeStartColor();

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


};

#endif // PLAYERCLIENT_H
