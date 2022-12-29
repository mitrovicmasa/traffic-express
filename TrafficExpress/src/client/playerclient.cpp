#include "../../headers/client/playerclient.h"

PlayerClient::PlayerClient(QObject *parent)
    : QObject{parent},m_index(0),m_isHost(false)
{
    m_ready=std::vector<bool>();
    m_names=std::vector<QString>();

}

void PlayerClient::startClient()
{
    m_clientSocket=new QTcpSocket();
    connect(m_clientSocket,&QTcpSocket::connected,this,&PlayerClient::onConnected);
    connect(m_clientSocket,&QTcpSocket::disconnected,this,&PlayerClient::onDisconnected);
    connect(m_clientSocket,&QTcpSocket::readyRead,this,&PlayerClient::onReadyRead);
    m_clientSocket->connectToHost("localhost",12345);
    if(!m_clientSocket->waitForConnected(1000)){
        qDebug()<<"not conected to server port 12345";
    }else{
        qDebug()<<"conected server is listenng to port 12345";
    }

}

void PlayerClient::sendMessage(QString message)
{
    m_clientSocket->write(message.toUtf8());
    m_clientSocket->flush();
    //m_clientSocket->waitForBytesWritten(-1);
}

bool PlayerClient::getHost()
{
    return m_isHost;
}

QString PlayerClient::getUsername()
{
    return m_username;
}

void PlayerClient::setUsername(QString name)
{
    m_username=name;
}

bool PlayerClient::allReady()
{
    return std::accumulate(m_ready.begin(),m_ready.end(),true,[](bool x, bool y){return x && y;});
}

void PlayerClient::onConnected()
{
    m_ready.push_back(false);
    this->sendMessage(m_username);
}

void PlayerClient::onReadyRead()
{
    qDebug()<<"onReadyRead";


    QString message(m_clientSocket->readAll());
    qDebug()<<"my message:"<<message;
    if(message.startsWith("host")){
        qDebug()<<"host message:"<<message;
        m_isHost=true;
        emit changeStartColor();
    }else if(message.startsWith("!host")){
        m_isHost=false;
        emit changeStartColor();
    }else if(message.startsWith("cc:")){
        QString name=message.split(":")[1];
        m_names.push_back(name);
        m_ready.push_back(false);
        emit changeStartColor();

    }else if(message.startsWith("ac:")){
        QString name=message.split(":")[1];
        QString ready=message.split(":")[2];
        m_names.push_back(name);
        m_index+=1;
        m_ready.push_back((bool)ready.toInt());
        emit changeStartColor();
    }else if(message.startsWith("ready:")){
        int indexOfReady=(message.split(":")[1]).toInt();
        m_ready[indexOfReady]=!m_ready[indexOfReady];

        emit changeStartColor();


    }
    this->sendMessage("ok");
    qDebug()<<message;
}

void PlayerClient::onDisconnected()
{

}

void PlayerClient::onClickedReady()
{
    qDebug()<<"readyClicked";
    qDebug()<<"all ready"<<this->allReady();
    qDebug()<<"host:"<<m_isHost;

    m_ready[m_index]=!m_ready[m_index];
    emit changeReadyColor(m_ready[m_index]);
    emit changeStartColor();

    qDebug()<<"readyClicked";
    qDebug()<<"m_ready size:"<<m_ready.size();
    qDebug()<<"host:"<<m_isHost;


    //this->sendMessage("ready:"+QString::number(m_index));
}

void PlayerClient::onClickedStart()
{
     qDebug()<<"startClicked";
}
