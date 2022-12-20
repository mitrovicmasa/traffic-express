#include "deck.h"
#include <qgraphicsscene.h>
#include <iostream>

Deck::Deck():QGraphicsObject()
{

}

Deck::Deck(const Deck &d)
    :QGraphicsObject()
{
    //TODO
    for(Card* c:d.m_cards)
        this->push_back(c->Copy());
}

Deck::Deck(CardColection cc)
{
    auto cpy=CardColection(cc);
    for(Card*c:cpy){
        this->push_back(c);

    }

}

CardColection &Deck::getCards()
{
    return m_cards;
}

// GUI

void Deck::push_back(Card *card)
{
    connect(card, &Card::clicked, this, &Deck::test);
    m_cards.push_back(card);
    card->setParentItem(this);
    card->setPos(5,20);
}

void Deck::pop_back()
{
    disconnect(m_cards.back(),&Card::clicked,this,&Deck::test);
    m_cards.back()->setParentItem(nullptr);
    m_cards.pop_back();
}

int Deck::size()
{
    return m_cards.size();
}

bool Deck::empty()
{
    return m_cards.empty();
}

Card *Deck::back()
{
    return m_cards.back();
}

Card *Deck::front()
{
    return m_cards.front();
}

Card *Deck::operator[](int ind)
{
    return m_cards[ind];
}

void Deck::push_front(Card *card)
{
    connect(card, &Card::clicked, this, &Deck::test);
    m_cards.insert(m_cards.begin(),card);
    card->setParentItem(this);
    card->setPos(5,20);
}

void Deck::pop_front()
{
    disconnect(m_cards.front(),&Card::clicked,this,&Deck::test);
    m_cards.front()->setParentItem(nullptr);
    m_cards.erase(m_cards.begin());
}

QRectF Deck::boundingRect() const
{
    return QRectF(0,0,100,120);
}

void Deck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(210,222,230));
    painter->drawText(boundingRect(), "DECK:");
}

void Deck::test()
{
    std::cout<<"Card clicked from deck!"<<std::endl;
}

void Deck::setAllCardsFaceDown()
{
    for(Card*x:m_cards)
        x->setFaceUp(false);
}

void Deck::setAllCardsFaceUp()
{
    for(Card*x:m_cards)
        x->setFaceUp(true);
}

void Deck::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    std::cout<<"Deck clicked!Deck size:"<<m_cards.size()<<std::endl;
}
