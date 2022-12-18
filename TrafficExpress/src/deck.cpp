#include "deck.h"
#include <qgraphicsscene.h>
#include <iostream>

Deck::Deck():QGraphicsObject(),std::vector<Card*>()
{

}

Deck::Deck(const Deck &d)
    :QGraphicsObject(),std::vector<Card*>()
{
    for(Card* c:d)
        this->push_back(c->Copy());
}

// GUI

void Deck::push_back(Card *card)
{
    connect(card, &Card::clicked, this, &Deck::test);
    std::vector<Card*>::push_back(card);
    card->setParentItem(this);
    card->setPos(5,20);
}

void Deck::pop_back()
{
    disconnect(this->back(),&Card::clicked,this,&Deck::test);
    this->back()->setParentItem(nullptr);
    std::vector<Card*>::pop_back();
}

void Deck::push_front(Card *card)
{
    connect(card, &Card::clicked, this, &Deck::test);
    std::vector<Card*>::insert(this->begin(),card);
    card->setParentItem(this);
    card->setPos(5,20);
}

void Deck::pop_front()
{
    disconnect(this->front(),&Card::clicked,this,&Deck::test);
    this->front()->setParentItem(nullptr);
    std::vector<Card*>::erase(this->begin());
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

void Deck::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    std::cout<<"Deck clicked!Deck size:"<<this->size()<<std::endl;
}
