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

    auto tc = TreasureChest(downt);
    for(Treasure* t: tc) {
        this->addContentDown(t);
    }

    auto tc1=TreasureChest(upt);
    for(Treasure* t: tc1) {
        this->addContentUp(t);
    }

    auto pg=PlayerGroup(upp);
    for(Player* p: pg) {
        this->addPlayerUp(p);
    }

    auto pg1=PlayerGroup(downp);
    for(Player* p: pg1) {
        this->addPlayerDown(p);
    }

    this->setIsLocomotive(isLocomotive);
    if(this->isLocomotive()) {
        this->addSheriffDown(new Sheriff());
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


// Get methods
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

bool Wagon::isLocomotive() const
{
    return m_isLocomotive;
}


// Set methods
void Wagon::setContentDown(TreasureChest newContentDown)
{
    for(Treasure* x: m_contentDown) {
        delete x;
    }
    m_contentDown.clear();

    for(Treasure* t: newContentDown) {
        m_contentDown.push_back(t);
        t->setParentItem(this);
        t->setPos(10+(m_contentDown.size()-1)*(2*t->width()),-30+height()-t->height());
    }
}

void Wagon::setContentUp(TreasureChest newContentUp)
{
    for(Treasure* x: m_contentUp) {
        delete x;
    }
    m_contentUp.clear();

    for(Treasure* t: newContentUp) {
        m_contentUp.push_back(t);
        t->setParentItem(this);
        t->setPos(10+(m_contentUp.size()-1)*(2*t->width()),-30+height()-t->height());
    }
    repositionTreasure();
}

void Wagon::setIsLocomotive(bool newIsLocomotive)
{
    m_isLocomotive = newIsLocomotive;
}


// Other methods
void Wagon::addContentUp(Treasure *t)
{
    connect(t, &Treasure::clickedTreasure, this, &Wagon::onCickedTreasure);
    m_contentUp.push_back(t);
    t->setParentItem(this);
    t->setPos(15+(m_contentUp.size()-1)*(1.2*t->width()),70-t->height());
    repositionTreasure();
}

void Wagon::addContentDown(Treasure *t)
{
    connect(t, &Treasure::clickedTreasure, this, &Wagon::onCickedTreasure);
    m_contentDown.push_back(t);
    t->setParentItem(this);
    t->setPos(15+(m_contentDown.size()-1)*(1.2*t->height()),-40+height()-t->width());
    repositionTreasure();
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

void Wagon::addSheriffDown(Sheriff *s)
{
    m_sheriff = s;
    m_sheriff->setParentItem(this);
    m_sheriff->setPos(10,80);

}

Sheriff* Wagon::takeSheriffDown()
{
    Sheriff *tmp = m_sheriff;
    m_sheriff->setParentItem(nullptr);
    m_sheriff = nullptr;
    return tmp;
}

Treasure *Wagon::takeContentUp(TreasureType t)
{
    Treasure* r;
    std::vector<Treasure*>tmp;
    for(int i = 0; i < m_contentDown.size(); i++) {
        if(m_contentDown[i]->getType() == t)
            tmp.push_back(m_contentDown[i]);
    }
    if(tmp.size() > 0) {
        int index=QRandomGenerator::global()->bounded((int)tmp.size());
        r = tmp[index];
        m_contentDown.erase(std::find(m_contentDown.begin(),m_contentDown.end(),r));
        disconnect(r, &Treasure::clickedTreasure, this, &Wagon::onCickedTreasure);
        repositionTreasure();
        return r;
    }
    return new Treasure(0,TreasureType::MONEYBAG);

}

Treasure *Wagon::takeContentDown(TreasureType t)
{
    Treasure* r;
    std::vector<Treasure*> tmp;
    for(int i=0; i < m_contentDown.size(); i++){
        if(m_contentDown[i]->getType() == t)
            tmp.push_back(m_contentDown[i]);
    }
    if(tmp.size() > 0) {
        int index=QRandomGenerator::global()->bounded((int)tmp.size());
        r = tmp[index];
        m_contentDown.erase(std::find(m_contentDown.begin(),m_contentDown.end(),r));
        r->setParentItem(nullptr);
        disconnect(r, &Treasure::clickedTreasure, this, &Wagon::onCickedTreasure);
        repositionTreasure();
        return r;
    }
    return new Treasure(0,TreasureType::MONEYBAG);
}

Player *Wagon::takePlayerUp(BanditType bandit)
{
    Player* playerToRemove=nullptr;
    for(auto x = m_playersUp.begin(); x != m_playersUp.end(); x++){
        if((*x)->id()==bandit){
            playerToRemove = *x ;
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
    for(auto x = m_playersDown.begin(); x != m_playersDown.end(); x++){
        if((*x)->id() == bandit){
            playerToRemove = *x;
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
    for(auto it = m_contentUp.begin(); it != m_contentUp.end(); it++){
        if(*it == t){
            t->setParentItem(nullptr);
            disconnect(*it, &Treasure::clickedTreasure, this, &Wagon::onCickedTreasure);
            m_contentUp.erase(it);
            repositionTreasure();
            return t;
        }
    }
    return nullptr;
}

Treasure *Wagon::takeContentDown(Treasure *t)
{
    for(auto it = m_contentDown.begin(); it != m_contentDown.end(); it++){
        if(*it == t){
            t->setParentItem(nullptr);
            disconnect(*it, &Treasure::clickedTreasure, this, &Wagon::onCickedTreasure);
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
    for(auto it = m_playersDown.begin(); it != m_playersDown.end(); it++){
        if((*it) == p) {
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

int Wagon::getTreasureIndex(Treasure* t, bool roof) const
{
    int treasureIndex = -1;

    if (!roof) {
        for (auto it = m_contentDown.begin(); it != m_contentDown.end(); ++it) {
            if (*it == t) {
                treasureIndex = std::distance(m_contentDown.begin(), it);
                break;
            }
        }
    } else if (roof) {
        for (auto it = m_contentUp.begin(); it != m_contentUp.end(); ++it) {
            if (*it == t) {
                treasureIndex = std::distance(m_contentUp.begin(), it);
                break;
            }
        }
    }

    return treasureIndex;
}

std::string Wagon::toString()
{
    std::string r = "myContentUp:\n";
        for(auto begin = m_contentUp.begin(); begin != m_contentUp.end(); begin++)
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
    if(this->isLocomotive())
        painter->drawPixmap(boundingRect(), QPixmap("://locomotive2.png"), QRectF(0,0,0,0));
    else
        painter->drawPixmap(boundingRect(), QPixmap("://wagon3.png"), QRectF(0,0,0,0));
}

void Wagon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    emit clickedWagon(this);
}


void Wagon::repositionTreasure()
{
    for(int i = 0; i < m_contentDown.size(); i++){
        m_contentDown[i]->setPos(15+(i)*(1.2*(m_contentDown[i]->width())),
                                 -40+height()-(m_contentDown[i]->height()));
    }

    for(int i = 0; i < m_contentUp.size(); i++){
        m_contentUp[i]->setPos(15+(i)*(1.2*(m_contentUp[i]->width())),
                                 70-m_contentUp[i]->height());
    }
}

void Wagon::repositionPlayers()
{
    for(int i = 0; i < m_playersUp.size(); i++){
        m_playersUp[i]->setPos(5+(m_playersUp[i]->width()+5)*(i),70-m_playersUp[i]->height()-25);

    }
    for(int i = 0; i < m_playersDown.size(); i++) {
        m_playersDown[i]->setPos(5+(m_playersDown[i]->width()+5)*(i),+80);

    }
}

void Wagon::onCickedTreasure(Treasure *t)
{
    emit clickedTreasureInWagon(t,this);
}

void Wagon::onClickedPlayer(Player *p)
{
    emit clickedPlayerInWagon(p,this);
}

// Serializable interface
QVariant Wagon::toVariant() const
{
    QVariantMap map;
    map.insert("isLocomotive",m_isLocomotive);
    map.insert("containsSherif",m_sheriff!=nullptr);
    QVariantList list;
    for(Treasure*t:m_contentDown){
        list.append(t->toVariant());
    }
    map.insert("contentDown",list);


    return map;
}

void Wagon::fromVariant(const QVariant &variant)
{
    QVariantMap map=variant.toMap();
    m_isLocomotive=map.value("isLocomotive").toBool();
    m_sheriff=map.value("containsSherif").toBool()? new Sheriff() :nullptr;
    QVariantList list=map.value("contentDown").toList();
    for(auto &t:list){

        Treasure*tr=new Treasure();
        tr->fromVariant(t);
        addContentDown(tr);
    }


}







