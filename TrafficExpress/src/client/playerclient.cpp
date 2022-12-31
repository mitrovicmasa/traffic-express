#include "../../headers/client/playerclient.h"

#include <QApplication>

PlayerClient::PlayerClient(QObject *parent)
    : QObject{parent},m_index(0),m_isHost(false),m_gameOngoing(false)
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

std::vector<QString> PlayerClient::getNames()
{
    return m_names;
}

std::vector<bool> PlayerClient::getReadys()
{
    return m_ready;
}

bool PlayerClient::getHost()
{
    return m_isHost;
}

int PlayerClient::getIndex()
{
    return m_index;
}

QString PlayerClient::getUsername()
{
    return m_username;
}

int PlayerClient::getPlayerCount()
{
    return m_ready.size();
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
    //m_ready.push_back(false);
    this->sendMessage(m_username);
}

void PlayerClient::onReadyRead()
{
    qDebug()<<"onReadyRead";

    QString message(m_clientSocket->readAll());
         qDebug()<<"my message:"<<message;
    ;
     qDebug()<<"gameOngoing:"<<m_gameOngoing;
    if(m_gameOngoing){
        if(message.startsWith("pcw:")){
            qDebug()<<"pcvrecieved";
            int playerPositioned=message.split(":")[1].toInt();
            int wagonIndex=message.split(":")[2].toInt();
            emit playerChoseWagon(playerPositioned,wagonIndex);


        }
        if(message.startsWith("ppc:")){
            int playerPc=message.split(":")[1].toInt();
            int cardIndex=message.split(":")[2].toInt();
            emit playerPlayedCard(playerPc,cardIndex);

        }
        if(message.startsWith("pdc:")){
            int playerToDraw=message.split(":")[1].toInt();
            emit playerDrawCards(playerToDraw);

        }
        if(message.startsWith("ass:")){
            int wagonToMoveSherif=message.split(":")[1].toInt();
            emit actionSheriffSignal(wagonToMoveSherif);
        }
        if(message.startsWith("afs:")){
            int playerToShot=message.split(":")[1].toInt();
            emit actionFireSignal(playerToShot);
        }
        if(message.startsWith("acf:")){
            int wagonIndex=message.split(":")[1].toInt();
            emit actionChangeFloorSignal(wagonIndex);
        }
        if(message.startsWith("acw:")){
            int wagonIndex=message.split(":")[1].toInt();
            emit actionChangeWagonSignal(wagonIndex);
        }
        if(message.startsWith("ars:")){
            int treasureIndex=message.split(":")[1].toInt();
            int wagonIndex=message.split(":")[2].toInt();
            emit actionRobberySignal(treasureIndex,wagonIndex);
        }
        if(message.startsWith("aps:")){

            int treasureIndex=message.split(":")[1].toInt();
            int playerI=message.split(":")[2].toInt();
            int wagonIndex=message.split(":")[3].toInt();
            emit actionPunchSignal(treasureIndex,playerI,wagonIndex);
        }
        if(message.startsWith("dc:")){
            QApplication::quit();
        }

        this->sendMessage(" ");
        return;
    }

    if(m_gameIncoming){
        qDebug()<<"game loaded";
        m_gameIncoming=false;
        m_gameOngoing=true;
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

    }else if(message.startsWith("nomoreac:")){
        m_ready.push_back(false);
        m_names.push_back(m_username);
        emit changeStartColor();

    }else if(message.startsWith("dc:")){
        int dcIndex=message.split(":")[1].toInt();
        m_ready.erase(m_ready.begin()+dcIndex);
        m_names.erase(m_names.begin()+dcIndex);
        if(m_index>dcIndex)
            m_index--;
        emit changeStartColor();



    }
    this->sendMessage(" ");

}

void PlayerClient::onDisconnected()
{
    QApplication::quit();
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
    m_gameOngoing=true;
    std::vector<BanditType>allPossibleBandits={
        BanditType::PICKPOCKET,
            BanditType::SEDUCTRESS,
            BanditType::STUDENT,
            BanditType::RETIREE,
            BanditType::HOMELESS_MAN,
            BanditType::BUSINESS_WOMAN
    };
    std::vector<BanditType>randomlySelectedBandits;
    unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
    std::sample(allPossibleBandits.begin(),allPossibleBandits.end(),
                std::back_inserter(randomlySelectedBandits),this->getPlayerCount(),
                std::default_random_engine(seed));



    std::vector<Player*> players;
   for(BanditType bt:randomlySelectedBandits)
       players.push_back(new Player(bt));

    Game* game=new Game(players);
    game->initialize();
    game->setPhase(Phase::WAGON_SELECTION);
    game->allPlayersDrawCards(6);
         //std::cout<<game->rounds()->size()<<std::endl;
    Game*copy=new Game(*game);
    m_pp=new PlayerPerspective(game,0);




    emit gameLoaded();
    auto tmp=game->toVariant();

    QJsonDocument doc=QJsonDocument::fromVariant(tmp);

    qDebug()<<"QVaraint string"<<doc.toJson(QJsonDocument::JsonFormat::Indented);
     m_clientSocket->write(doc.toJson(QJsonDocument::JsonFormat::Indented));
     m_clientSocket->flush();


}

void PlayerClient::onPlayerChoseWagon(int playerIndex, int wagonIndex)
{
    this->sendMessage("pcw:"+QString::number(playerIndex)+":"+QString::number(wagonIndex));
}

void PlayerClient::onPlayerPlayedCard(int playerIndex, int CardIndex)
{
    this->sendMessage("ppc:"+QString::number(playerIndex)+":"+QString::number(CardIndex));
}

void PlayerClient::onPlayerDrawCards(int playerIndex)
{
    this->sendMessage("pdc:"+QString::number(playerIndex));
}

void PlayerClient::onActionSheriffSignal(int wagonIndex)
{
    this->sendMessage("ass:"+QString::number(wagonIndex));
}

void PlayerClient::onActionFireSignal(int playerIndex)
{
    this->sendMessage("afs:"+QString::number(playerIndex));
}

void PlayerClient::onActionChangeFloorSignal(int wagonIndex)
{
    this->sendMessage("acf:"+QString::number(wagonIndex));
}

void PlayerClient::onActionChangeWagonSignal(int wagonIndex)
{
    this->sendMessage("acw:"+QString::number(wagonIndex));
}

void PlayerClient::onActionRobberySignal(int treasureIndex, int wagonIndex)
{
    this->sendMessage("ars:"+QString::number(treasureIndex)+":"+QString::number(wagonIndex));
}

void PlayerClient::onActionPunchSignal(int treasureIndex, int playerIndex, int wagonIndex)
{
    this->sendMessage("aps:"+QString::number(treasureIndex)+":"+QString::number(playerIndex)
                      +":"+QString::number(wagonIndex));
}


