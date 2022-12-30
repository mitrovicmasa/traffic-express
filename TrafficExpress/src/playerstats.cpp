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
        m_player=new Player(p->isItMyMove(),p->id(),p->hand(),p->deck(),p->bullet_deck(),p->positionInTrain(),
                                       p->roof(),p->treasure());
        int i=0;
        for(Treasure *t :m_player->treasure()){

            t->setParentItem(this);
            t->setPos(i*30+80, 20);
            i++;
            connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
        }


    }
    repositionTreasure();
}

void PlayerStats::addTreasureToPlayer(Treasure *t)
{
    m_player->treasure().push_back(t);
    t->setParentItem(this);
    t->setPos((m_player->treasure().size()-1)*30+80, 20);
    connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
    repositionTreasure();

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
            repositionTreasure();
            return t;
        }
    }
    return nullptr;
}

Player *PlayerStats::getPlayer()
{
    return m_player;
}

void PlayerStats::repositionTreasure()
{

    for(int i=0;i<m_player->treasure().size();i++){
        m_player->treasure()[i]->setPos(15+(i)*(1.2*(m_player->treasure()[i]->sirina())),20);
    }
}

// GUI
QRectF PlayerStats::boundingRect() const
{
    return QRectF(0,0,380,70);
}

void PlayerStats::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawPixmap(boundingRect(), QPixmap("://button.png"), QRectF(0,0,0,0));
    //painter->setPen(QColor(255,255,255));
    int num=0;
    for (Card *b : m_player->bullet_deck()->getCards()){
        num = ((BulletCard*)b)->numOfBullets();
    }

    QString bandit = QString::fromStdString(toString(m_player->id()));

    if (m_player->id() == BanditType::PICKPOCKET)
        painter->setPen(Qt::green);
    else if (m_player->id() == BanditType::STUDENT)
        painter->setPen(QColor(51,153,255));
    else if (m_player->id() == BanditType::SEDUCTRESS)
            painter->setPen(QColor(255,255,102));
    else if (m_player->id() == BanditType::RETIREE)
            painter->setPen(Qt::red);
    else if (m_player->id() == BanditType::HOMELESS_MAN)
            painter->setPen(QColor(204,0,204));

    painter->drawText(boundingRect(), "    "+ bandit + " - Number of bullets: " + QString::number(num));

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
