#include "../headers/playerstats.h"

#include <QPainter>
#include <string.h>

// Constructors
PlayerStats::PlayerStats()
    :QGraphicsObject(), m_player(new Player(BanditType::BUSINESS_WOMAN))
{
    int i = 0;
    for(Treasure *t :m_player->treasure()) {
        t->setParentItem(this);
        t->setPos(i*30+80, 20);
        i++;
        connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
    }
}

PlayerStats::PlayerStats(Player *p, bool deepCopy)
    :QGraphicsObject()
{
    if(!deepCopy) { //shallow copy
        m_player = p;
        int i=0;
        for(Treasure *t: m_player->treasure()) {
            t->setParentItem(this);
            t->setPos(i*30+80, 20);
            i++;
            connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
        }
    } else { //deep copy
        m_player=new Player(p->isItMyMove(),p->id(),p->hand(),p->deck(),p->bullet_deck(),
                            p->positionInTrain(),p->roof(),p->treasure());
        int i=0;
        for(Treasure *t: m_player->treasure()) {
            t->setParentItem(this);
            t->setPos(i*30+80, 20);
            i++;
            connect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
        }
    }

    repositionTreasure();
}

// Get methods
Player *PlayerStats::getPlayer()
{
    return m_player;
}

// Other methods
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
    for(auto it = this->getPlayer()->treasure().begin(); it != this->getPlayer()->treasure().end(); it++){
        if(t == *it) {
            disconnect(t, &Treasure::clickedTreasure, this, &PlayerStats::onTreasureClicked);
            t->setParentItem(nullptr);
            this->getPlayer()->treasure().erase(it);
            repositionTreasure();
            return t;
        }
    }
    return nullptr;
}

void PlayerStats::repositionTreasure()
{
    for(int i=0;i<m_player->treasure().size();i++){
        m_player->treasure()[i]->setPos(15+(i)*(1.2*(m_player->treasure()[i]->width())),20);
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

    int num=0;
    for (Card *b : m_player->bullet_deck()->getCards()){
        num = ((BulletCard*)b)->numOfBullets();
    }

    QString bandit = QString::fromStdString(toString(m_player->id()));

    if (m_player->id() == BanditType::PICKPOCKET)
        painter->setPen(QColor(40,200,60));
    else if (m_player->id() == BanditType::STUDENT)
        painter->setPen(QColor(70,180,240));
    else if (m_player->id() == BanditType::SEDUCTRESS)
            painter->setPen(QColor(255,255,102));
    else if (m_player->id() == BanditType::RETIREE)
            painter->setPen(QColor(240,70,80));
    else if (m_player->id() == BanditType::HOMELESS_MAN)
            painter->setPen(QColor(245,178,23));
    else if (m_player->id() == BanditType::BUSINESS_WOMAN)
            painter->setPen(QColor(204,0,204));

    painter->drawText(boundingRect(), "    "+ bandit + " - Number of bullets: " + QString::number(num));

}


void PlayerStats::onTreasureClicked(Treasure *t)
{
    emit clickedTreasueInPlayeStats(t,this);
}
