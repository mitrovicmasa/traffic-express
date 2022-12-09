#include "../headers/wagon.h"
#include <strings.h>
#include<QRandomGenerator>
#include <qpainter.h>

//// Constructors
Wagon::Wagon()
    :QGraphicsObject()
{

}

Wagon::Wagon(const std::vector<Treasure *> &contentDown, const std::vector<Treasure *> &contentUp)
    :QGraphicsObject(),m_contentUp(contentUp),m_contentDown(contentDown)
{

}

void Wagon::addContentUp(Treasure *t)
{
    m_contentUp.push_back(t);
    t->setParentItem(this);
    t->setPos(10+(m_contentUp.size()-1)*(2*t->sirina()),-t->visina());
}

void Wagon::addContentDown(Treasure *t)
{
    m_contentDown.push_back(t);
    t->setParentItem(this);
    t->setPos(10+(m_contentDown.size()-1)*(2*t->sirina()),visina()-t->visina());
}

void Wagon::addPlayerUp(Player *p)
{
    m_playersUp.push_back(p);
    p->setParentItem(this);
    p->setPos(5+(p->width()+5)*(m_playersUp.size()-1),-p->height()-25);
}

void Wagon::addPlayerDown(Player *p)
{
    m_playersDown.push_back(p);
    p->setParentItem(this);
    p->setPos(5+(p->width()+5)*(m_playersDown.size()-1),+25);
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

int Wagon::visina() const
{
    return 100;
}

int Wagon::sirina() const
{
    return 200;
}

QRectF Wagon::boundingRect() const
{
    return QRectF(0,0,sirina(),visina());
}

void Wagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor::fromRgb(100,100,200));
}





