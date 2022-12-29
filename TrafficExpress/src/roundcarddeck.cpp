#include "../headers/roundcarddeck.h"

RoundCardDeck::RoundCardDeck()
{

}

RoundCardDeck::RoundCardDeck(std::vector<RoundCard *>rcs)
{
    for(auto it=rcs.crbegin();it!=rcs.crend();it++){
        RoundCard*tmp=*it;

        this->push_front(new RoundCard(tmp->typeOfRoundCard(),tmp->event(),tmp->getMiniRounds()));


    }
}

RoundCardDeck::RoundCardDeck(const RoundCardCollection &rcd)
{
    for(auto it=rcd.crbegin();it!=rcd.crend();it++){
        RoundCard*tmp=*it;

        this->push_front(new RoundCard(tmp->typeOfRoundCard(),tmp->event(),tmp->getMiniRounds()));


    }
}

RoundCard *RoundCardDeck::operator[](int i)
{
    return m_rounds[i];
}

RoundCard *RoundCardDeck::back()
{
    return m_rounds.back();
}

RoundCard *RoundCardDeck::front()
{
    return m_rounds.front();
}

int RoundCardDeck::size()
{
    return m_rounds.size();
}

void RoundCardDeck::push_front(RoundCard*c)
{
    m_rounds.insert(m_rounds.begin(),c);
    c->setParentItem(this);
    c->setPos(0,0);

}

void RoundCardDeck::pop_front()
{
    m_rounds.front()->setParentItem(nullptr);
    m_rounds.erase(m_rounds.begin());
}

void RoundCardDeck::setRoundOnScene(int i)
{
    m_rounds[i]->setPos(0,0);
    m_rounds[i]->topLevelItem();
}

RoundCardCollection& RoundCardDeck::getRoundCads()
{
    return m_rounds;
}

int RoundCardDeck::width() const
{
    return 300;
}

int RoundCardDeck::height() const
{
    return 100;
}

QRectF RoundCardDeck::boundingRect() const
{
    return QRectF(0,0,this->width(),this->height());
}

void RoundCardDeck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor::fromRgb(80,90,100));
}

QVariant RoundCardDeck::toVariant() const
{
    QVariantMap map;

    QVariantList list;
    for(RoundCard*rc:m_rounds){
        list.append(rc->toVariant());
    }
    map.insert("rcdList",list);




    return map;
}

void RoundCardDeck::fromVariant(const QVariant &variant)
{
    QVariantMap map=variant.toMap();
    QVariantList list=map.value("rcdList").toList();
    for( auto it=list.rbegin();it!=list.rend();it++){
        RoundCard* rc=new RoundCard();
        rc->fromVariant(*it);
        this->push_front(rc);
    }
}
