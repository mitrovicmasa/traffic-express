#include "deck.h"
#include <qgraphicsscene.h>
#include <iostream>

Deck::Deck():QGraphicsObject(),std::vector<Card*>()
{

}

// GUI

void Deck::addCardToDeck(Card *card)
{
    //connect(card, &Card::Moved, this, &Deck::test);
    this->push_back(card);
    card->setParentItem(this);
    card->setPos(10,10);
}

void Deck::push_back(Card *card)
{
    connect(card, &Card::Moved, this, &Deck::test);
    std::vector<Card*>::push_back(card);
    card->setParentItem(this);
    card->setPos(5,20);
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

// Test moveEevent and pressEvent
void Deck::test()
{
    std::cout<<"Moved in deck!"<<std::endl;
}
