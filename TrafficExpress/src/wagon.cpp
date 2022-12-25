#include "../headers/wagon.h"
#include <strings.h>
#include<QRandomGenerator>
#include <qpainter.h>
#include <iostream>


// Constructors
Wagon::Wagon(TreasureChest &upt, TreasureChest &downt, PlayerGroup &upp, PlayerGroup &downp,bool isLocomotive)
    :QGraphicsObject()
{
    setFlags(GraphicsItemFlag::ItemIsSelectable);
    auto tc=TreasureChest(downt);

    for(Treasure*t:tc){
        this->addContentDown(t);

    }

    auto tc1=TreasureChest(upt);

    for(Treasure*t:tc1){
        this->addContentUp(t);

    }

    auto pg=PlayerGroup(upp);

    for(Player*p:pg){
        this->addPlayerUp(p);

    }

    auto pg1=PlayerGroup(downp);

    for(Player*p:pg1){
        this->addPlayerDown(p);

    }

    this->setIsLocomotive(isLocomotive);

    if(this->isLocomotive()) {
        this->addSheriffDown();
    }
}


Wagon::Wagon()
{

}

Wagon::Wagon(TreasureChest contentDown, TreasureChest contentUp)
    :QGraphicsObject(),m_contentUp(contentUp),m_contentDown(contentDown)
{
    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

//Wagon::Wagon(const Wagon &other)
//{
//    for(Treasure*t:other.m_contentUp)
//        this->addContentUp(new Treasure(*t));

//    for(Treasure*t:other.m_contentDown)
//        this->addContentDown(new Treasure(*t));

//    for(Player*p:other.m_playersUp)
//        this->addPlayerUp(new Player(*p));

//    for(Player*p:other.m_playersDown)
//        this->addPlayerDown(new Player(*p));
//    setFlags(GraphicsItemFlag::ItemIsSelectable);

//}

// Getters
TreasureChest& Wagon::getContentDown()
{
    return m_contentDown;
}

TreasureChest& Wagon::getContentUp()
{
    return m_contentUp;
}

PlayerGroup &Wagon::getPlayersUp()
{
    return m_playersUp;
}

PlayerGroup &Wagon::getPlayersDown()
{
    return m_playersDown;
}

// Setters
void Wagon::setContentDown(TreasureChest newContentDown)
{
    for(Treasure*x:m_contentDown){
        delete x;
    }
    m_contentDown.clear();

 //   m_contentDown = newContentDown;
    for(Treasure* t: newContentDown) {
        connect(t, &Treasure::clicked, this, &Wagon::testTreasure);
        m_contentDown.push_back(t);
        t->setParentItem(this);
        t->setPos(10+(m_contentDown.size()-1)*(2*t->sirina()),-30+height()-t->visina());
    }
}

void Wagon::addContentUp(Treasure *t)
{
    connect(t, &Treasure::clicked, this, &Wagon::testTreasure);
    connect(t, &Treasure::clickedTreasure, this, &Wagon::OnCickedTreasuere);
    m_contentUp.push_back(t);
    t->setParentItem(this);
    t->setPos(15+(m_contentUp.size()-1)*(1.2*t->sirina()),70-t->visina());
}

void Wagon::addContentDown(Treasure *t)
{
    connect(t, &Treasure::clicked, this, &Wagon::testTreasure);
    connect(t, &Treasure::clickedTreasure, this, &Wagon::OnCickedTreasuere);
    m_contentDown.push_back(t);
    t->setParentItem(this);
    t->setPos(15+(m_contentDown.size()-1)*(1.2*t->sirina()),-40+height()-t->visina());
}

void Wagon::addPlayerUp(Player *p)
{
    p->setRoof(true);
    connect(p, &Player::clickedPlayer, this, &Wagon::onClickedPlayer);
    m_playersUp.push_back(p);
    p->setParentItem(this);
    p->setPos(5+(p->width()+5)*(m_playersUp.size()-1),70-p->height()-25);

}

void Wagon::addPlayerDown(Player *p)
{
    p->setRoof(false);
    connect(p, &Player::clickedPlayer, this, &Wagon::onClickedPlayer);
    m_playersDown.push_back(p);
    p->setParentItem(this);
    p->setPos(5+(p->width()+5)*(m_playersDown.size()-1),+80);
}

void Wagon::addSheriffDown()
{
    m_sheriff = new Sheriff();
    m_sheriff->setParentItem(this);
    m_sheriff->setPos(10,80);

//    for(Player* player: m_playersDown) {
//        takePlayerDown(player);
//        addPlayerUp(player);
//    }
}

void Wagon::takeSheriffDown()
{
    m_sheriff->setParentItem(nullptr);
    m_sheriff = nullptr;
}

Treasure *Wagon::takeContentUp(TreasureType t)
{
    Treasure* r;
    std::vector<Treasure*>tmp;
    for(int i=0;i<m_contentDown.size();i++){
        if(m_contentDown[i]->getType()==t)
            tmp.push_back(m_contentDown[i]);
        }
    if(tmp.size()>0){
        int index=QRandomGenerator::global()->bounded((int)tmp.size());
        r=tmp[index];
        m_contentDown.erase(std::find(m_contentDown.begin(),m_contentDown.end(),r));
        disconnect(r, &Treasure::clicked, this, &Wagon::testTreasure);
        disconnect(r, &Treasure::clickedTreasure, this, &Wagon::OnCickedTreasuere);
        repositionTreasure();
        return r;
    }
    return new Treasure(0,TreasureType::MONEYBAG);

}

Treasure *Wagon::takeContentDown(TreasureType t)
{
    Treasure* r;
    std::vector<Treasure*>tmp;
    for(int i=0;i<m_contentDown.size();i++){
        if(m_contentDown[i]->getType()==t)
            tmp.push_back(m_contentDown[i]);
        }
    if(tmp.size()>0){
        int index=QRandomGenerator::global()->bounded((int)tmp.size());
        r=tmp[index];
        m_contentDown.erase(std::find(m_contentDown.begin(),m_contentDown.end(),r));
        r->setParentItem(nullptr);
        disconnect(r, &Treasure::clicked, this, &Wagon::testTreasure);
        disconnect(r, &Treasure::clickedTreasure, this, &Wagon::OnCickedTreasuere);
        repositionTreasure();
        return r;
    }
    return new Treasure(0,TreasureType::MONEYBAG);

}

Player *Wagon::takePlayerUp(BanditType bandit)
{
    Player* playerToRemove=nullptr;


    for(auto x=m_playersUp.begin();x!=m_playersUp.end();x++){
        if((*x)->id()==bandit){
            playerToRemove=*x;
            (*x)->setParentItem(nullptr);
            m_playersUp.erase(x);
            disconnect(playerToRemove, &Player::clickedPlayer, this, &Wagon::onClickedPlayer);
            repositionPlayers();
            break;
        }
    }
    return playerToRemove;



}

Player *Wagon::takePlayerDown(BanditType bandit)
{
    Player* playerToRemove=nullptr;


    for(auto x=m_playersDown.begin();x!=m_playersDown.end();x++){
        if((*x)->id()==bandit){
            playerToRemove=*x;
            (*x)->setParentItem(nullptr);
            m_playersDown.erase(x);
            disconnect(playerToRemove, &Player::clickedPlayer, this, &Wagon::onClickedPlayer);
            repositionPlayers();
            break;
        }
    }
    return playerToRemove;

}

Treasure *Wagon::takeContentUp(Treasure *t)
{
    for(auto it=m_contentUp.begin();it!=m_contentUp.end();it++){
        if(*it==t){
            t->setParentItem(nullptr);
            disconnect(*it, &Treasure::clicked, this, &Wagon::testTreasure);
            disconnect(*it, &Treasure::clickedTreasure, this, &Wagon::OnCickedTreasuere);
            m_contentUp.erase(it);
            repositionTreasure();
            return t;
        }
    }
    return nullptr;
}

Treasure *Wagon::takeContentDown(Treasure *t)
{
    for(auto it=m_contentDown.begin();it!=m_contentDown.end();it++){
        if(*it==t){
            t->setParentItem(nullptr);
            disconnect(*it, &Treasure::clicked, this, &Wagon::testTreasure);
            disconnect(*it, &Treasure::clickedTreasure, this, &Wagon::OnCickedTreasuere);
            m_contentDown.erase(it);
            repositionTreasure();
            return t;
        }
    }
    return nullptr;
}

Player *Wagon::takePlayerUp(Player *p)
{


    for(auto it=m_playersUp.begin();it!=m_playersUp.end();it++){
        if((*it)==p){
            disconnect(p, &Player::clickedPlayer, this, &Wagon::onClickedPlayer);

            p->setParentItem(nullptr);
            m_playersUp.erase(it);
            repositionPlayers();


            return p;
        }
    }
    return nullptr;
}

Player *Wagon::takePlayerDown(Player *p)
{
    for(auto it=m_playersDown.begin();it!=m_playersDown.end();it++){
        if((*it)==p){
            disconnect(p, &Player::clickedPlayer, this, &Wagon::onClickedPlayer);

            p->setParentItem(nullptr);
            m_playersDown.erase(it);
            repositionPlayers();


            return p;
        }
    }
    return nullptr;
}



int Wagon::numberOfTreasureInWagonDown(TreasureType type) const
{
    return std::count_if(m_contentDown.begin(), m_contentDown.end(), [type](auto treasure) { return treasure->getType() == type; });
}

std::string Wagon::toString()
{
    std::string r="myContentUp:\n";
        for(auto begin=m_contentUp.begin();begin!=m_contentUp.end();begin++)
            r+=(*begin)->toString()+", ";
        r+="\nMyContentDown:\n";
        for(auto begin=m_contentDown.begin();begin!=m_contentDown.end();begin++)
            r+=(*begin)->toString()+", ";
        return r;

}

//Sheriff *Wagon::sheriffActions(Sheriff *s) {

//    for(Player* player: m_playersDown) {
//        if (s->positionInTrain() == player->positionInTrain()) {
//            takePlayerDown(player);
             // addPlayerUp(player);
//
//        }
//    }

//}

// GUI

int Wagon::height() const
{
    return 180;
}

int Wagon::width() const
{
    return 180;
}

QRectF Wagon::boundingRect() const
{
    return QRectF(0,0,width(),height());
}

void Wagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->isLocomotive())
        painter->drawPixmap(boundingRect(), QPixmap("://locomotive.png"), QRectF(0,0,0,0));
    else
        painter->drawPixmap(boundingRect(), QPixmap("://wagon2.png"), QRectF(0,0,0,0));
}

void Wagon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    emit clicked();
    emit clickedWagon(this);
}

void Wagon::testTreasure()
{
    std::cout<< "Treasure clicked!" << std::endl;
}

void Wagon::testPlayers()
{
    std::cout<< "Player clicked!" << std::endl;
}

void Wagon::repositionTreasure()
{
    for(int i=0;i<m_contentDown.size();i++){
        m_contentDown[i]->setPos(15+(i)*(2*(m_contentDown[i]->sirina())),
                                 -40+height()-(m_contentDown[i]->visina()));
    }
}

void Wagon::repositionPlayers()
{
    for(int i=0;i<m_playersUp.size();i++){
        m_playersUp[i]->setPos(5+(m_playersUp[i]->width()+5)*(i),70-m_playersUp[i]->height()-25);

    }
    for(int i=0;i<m_playersDown.size();i++){
        m_playersDown[i]->setPos(5+(m_playersDown[i]->width()+5)*(i),+80);

    }


}

void Wagon::OnCickedTreasuere(Treasure *t)
{   //std::cout<<"Treasure signals wagon"<<std::endl;
    emit clickedTreasureInWagon(t,this);
}

void Wagon::onClickedPlayer(Player *p)
{

    emit clickedPlayerInWagon(p,this);
}

bool Wagon::isLocomotive() const
{
    return m_isLocomotive;
}

void Wagon::setIsLocomotive(bool newIsLocomotive)
{
    m_isLocomotive = newIsLocomotive;
}





