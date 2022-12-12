#include "hand.h"
#include <qgraphicsscene.h>

// Constructors

Hand::Hand():QGraphicsObject(),std::vector<Card*>()
{

}

// GUI

void Hand::addCardToHand(Card *card)
{
    this->push_back(card);
    card->setParentItem(this);
    card->setPos((this->size()-1)*70+5,20);
}

void Hand::push_back(Card *card)
{
    std::vector<Card*>::push_back(card);
    card->setParentItem(this);
    card->setPos((this->size()-1)*70+5,20);
}

QRectF Hand::boundingRect() const
{
    return QRectF(0,0,520,120);
}

void Hand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(210,222,230));
    painter->drawText(boundingRect(), "HAND:");
}
