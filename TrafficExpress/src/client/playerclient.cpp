#include "../../headers/client/playerclient.h"

PlayerClient::PlayerClient(QObject *parent)
    : QObject{parent},m_index(0),m_isHost(false)
{
    m_ready=std::vector<bool>();
    m_names=std::vector<QString>();

}

void PlayerClient::startClient()
{
    m_gameIncoming=false;
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

PlayerPerspective *PlayerClient::getPlayerPerspective()
{
    return m_pp;
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
    ;

    if(m_gameIncoming){
        qDebug()<<"game loaded";
        m_gameIncoming=false;
        Game*g =new Game();
        QJsonDocument doc=QJsonDocument::fromJson(message.toUtf8());

        QVariant v(doc.toVariant());

        g->fromVariant(v);
        m_pp=new PlayerPerspective(g,m_index);
        emit gameLoaded();
        this->sendMessage(" ");
        return;
    }





    if(message.startsWith("host")){

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
        qDebug()<<"Ready in client!!!!!!!!!!!1";
        int indexOfReady=(message.split(":")[1]).toInt();
        m_ready[indexOfReady]=!m_ready[indexOfReady];

        emit changeStartColor();


    }else if(message.startsWith("start:")){
        qDebug()<<"GameIncomingRecieved";
        qDebug()<<message;
        m_gameIncoming=true;

    }
    this->sendMessage(" ");

}

void PlayerClient::onDisconnected()
{

}

void PlayerClient::onClickedReady()
{
//    qDebug()<<"readyClicked";
//    qDebug()<<"all ready"<<this->allReady();
//    qDebug()<<"host:"<<m_isHost;
    qDebug()<<"Index:"<<m_index;
    m_ready[m_index]=!m_ready[m_index];
    emit changeReadyColor(m_ready[m_index]);
    emit changeStartColor();

//    qDebug()<<"readyClicked";
//    qDebug()<<"m_ready size:"<<m_ready.size();
//    qDebug()<<"host:"<<m_isHost;


    this->sendMessage("ready:"+QString::number(m_index));
}

void PlayerClient::onClickedStart()
{
     qDebug()<<"startClicked"<<m_index;
     this->sendMessage("start:");

         std::vector<Player*> players;
             players = {
                 new Player(BanditType::PICKPOCKET),
                 new Player(BanditType::SEDUCTRESS),
                 new Player(BanditType::STUDENT),
         //        new Player(BanditType::RETIREE),
         //        new Player(BanditType::HOMELESS_MAN),
         //        new Player(BanditType::BUSINESS_WOMAN)
             };

    Game* game=new Game(players);
    game->initialize();
    game->setPhase(Phase::WAGON_SELECTION);
    game->allPlayersDrawCards(6);
         //std::cout<<game->rounds()->size()<<std::endl;
    Game*copy=new Game(*game);
    m_pp=new PlayerPerspective(copy,0);
    emit gameLoaded();
    auto tmp=copy->toVariant();

    QJsonDocument doc=QJsonDocument::fromVariant(tmp);

    qDebug()<<"QVaraint string"<<doc.toJson(QJsonDocument::JsonFormat::Indented);
     m_clientSocket->write(doc.toJson(QJsonDocument::JsonFormat::Indented));
     m_clientSocket->flush();


}
