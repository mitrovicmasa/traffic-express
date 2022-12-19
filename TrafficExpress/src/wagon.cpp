#include "../headers/wagon.h"
#include <strings.h>
#include<QRandomGenerator>
#include <qpainter.h>
#include <iostream>
//// Constructors
Wagon::Wagon()
    :QGraphicsObject()
{
    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

Wagon::Wagon(const std::vector<Treasure *> &contentDown, const std::vector<Treasure *> &contentUp)
    :QGraphicsObject(),m_contentUp(contentUp),m_contentDown(contentDown)
{
    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

Wagon::Wagon(const Wagon &other)
    :m_contentUp(std::vector<Treasure*>()),
      m_contentDown(std::vector<Treasure*>()),
      m_playersUp(std::vector<Player*>()),
      m_playersDown(std::vector<Player*>())
{
    for(Treasure*t:other.m_contentUp)
        this->addContentUp(new Treasure(*t));

    for(Treasure*t:other.m_contentDown)
        this->addContentDown(new Treasure(*t));

    for(Player*p:other.m_playersUp)
        this->addPlayerUp(new Player(*p));

    for(Player*p:other.m_playersDown)
        this->addPlayerDown(new Player(*p));


}

// Getters
std::vector<Treasure*> Wagon::contentDown()
{
    return m_contentDown;
}

std::vector<Treasure*> Wagon::contentUp()
{
    return m_contentUp;
}

// Setters
void Wagon::setContentDown(std::vector<Treasure*> newContentDown)
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
    t->setPos(10+(m_contentUp.size()-1)*(2*t->sirina()),70-t->visina());
}

void Wagon::addContentDown(Treasure *t)
{
    connect(t, &Treasure::clicked, this, &Wagon::testTreasure);
    connect(t, &Treasure::clickedTreasure, this, &Wagon::OnCickedTreasuere);
    m_contentDown.push_back(t);
    t->setParentItem(this);
    t->setPos(10+(m_contentDown.size()-1)*(2*t->sirina()),-30+height()-t->visina());
}

void Wagon::addPlayerUp(Player *p)
{
    connect(p, &Player::clicked, this, &Wagon::testPlayers);
    m_playersUp.push_back(p);
    p->setParentItem(this);
    p->setPos(5+(p->width()+5)*(m_playersUp.size()-1),70-p->height()-25);
}

void Wagon::addPlayerDown(Player *p)
{
    connect(p, &Player::clicked, this, &Wagon::testPlayers);
    m_playersDown.push_back(p);
    p->setParentItem(this);
    p->setPos(5+(p->width()+5)*(m_playersDown.size()-1),+80);
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
            break;
        }
    }
    return playerToRemove;

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
    painter->drawPixmap(boundingRect(), QPixmap("://wagon.png"), QRectF(0,0,0,0));
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
        m_contentDown[i]->setPos(10+(i)*(2*(m_contentDown[i]->sirina())),
                                 -30+height()-(m_contentDown[i]->visina()));
    }
}

void Wagon::OnCickedTreasuere(Treasure *t)
{   //std::cout<<"Treasure signals wagon"<<std::endl;
    emit clickedTreasureInWagon(t,this);
}





