#include "deck.h"
#include <qgraphicsscene.h>

Deck::Deck():QGraphicsObject(),std::vector<Card*>()
{

}

// GUI

void Deck::addCardToDeck(Card *card)
{
    this->push_back(card);
    card->setParentItem(this);
    card->setPos(10,10);
}

void Deck::push_back(Card *card)
{
    std::vector<Card*>::push_back(card);
    card->setParentItem(this);
    card->setPos(10,10);
}

QRectF Deck::boundingRect() const
{
    return QRectF(0,0,80,120);
}

void Deck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(50,150,150));
}
