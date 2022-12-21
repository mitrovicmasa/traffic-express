#include "../headers/playerstats.h"

#include <QPainter>
#include <string.h>

// Constructors
PlayerStats::PlayerStats()
    :QGraphicsObject(), m_player(new Player(BanditType::BUSINESS_WOMAN))
{
    int i = 0;
    for(Treasure *t :m_player->treasure()){

        t->setParentItem(this);
        t->setPos(i*30+80, 20);
        i++;
        connect(t, &Treasure::clicked, this, &PlayerStats::test);
       }
}

PlayerStats::PlayerStats(Player *p, bool deepCopy)
    :QGraphicsObject()
{
    if(!deepCopy){//shalow copy
        m_player=p;
        int i=0;
        for(Treasure *t :m_player->treasure()){

            t->setParentItem(this);
            t->setPos(i*30+80, 20);
            i++;
            connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
        }
    }else{//deepCopy
        m_player=new Player(p->isItMyMove(),p->id(),p->hand(),p->deck(),p->bulletDeck(),p->positionInTrain(),
                                       p->roof(),p->treasure());
        int i=0;
        for(Treasure *t :m_player->treasure()){

            t->setParentItem(this);
            t->setPos(i*30+80, 20);
            i++;
            connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
        }


    }
}

void PlayerStats::addTreasureToPlayer(Treasure *t)
{
    m_player->treasure().push_back(t);
    t->setParentItem(this);
    t->setPos((m_player->treasure().size()-1)*30+80, 20);

    connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
}

Treasure *PlayerStats::takeTreasureFromPlayer(Treasure *t)
{
//    for(Treasure*t1:this->getPlayer()->treasure())
//        qDebug()<<t1<<"\n";

    for(auto it=this->getPlayer()->treasure().begin();it!=this->getPlayer()->treasure().end();it++){
//        qDebug()<<*it<<"\n";
        if(t==*it){
//            qDebug()<<"good felling"<<"\n";
            disconnect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
            t->setParentItem(nullptr);
            this->getPlayer()->treasure().erase(it);
            return t;
        }
    }
    return nullptr;
}

Player *PlayerStats::getPlayer()
{
    return m_player;
}

// GUI
QRectF PlayerStats::boundingRect() const
{
    return QRectF(0,0,300,70);
}

void PlayerStats::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(boundingRect(),QColor(210,222,230));

    int num;
    for (BulletCard *b :m_player->bulletDeck()){
        num = b->numOfBullets();

    }
    QString bandit = QString::fromStdString(toString(m_player->id()));
    painter->drawText(boundingRect(),  bandit + " - Number of bullets: " + QString::number(num));
}

void PlayerStats::test()
{
    std::cout<<"Clicked treasure!"<<std::endl;
}

void PlayerStats::onTreasureClicked(Treasure *t)
{
    //std::cout<<" treasure clicked in player stats"<<std::endl;

    emit clickedTreasueInPlayeStats(t,this);
}
