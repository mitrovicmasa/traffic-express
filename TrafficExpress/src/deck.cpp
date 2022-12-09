#include "deck.h"
#include <qgraphicsscene.h>

Deck::Deck():QGraphicsObject(),std::vector<Card*>()
{

}

//void Deck::addDeckToScene(QGraphicsScene *sc)
//{
//    for(int i=0;i<size();i++){
//        sc->addItem((*this)[i]);
//        (*this)[i]->setPos(800,400);
//    }
//}

void Deck::addCardToDeck(Card *card)
{
    this->push_back(card);
    card->setParentItem(this);
    card->setPos(10,50);
}

QRectF Deck::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void Deck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(50,150,150));
}
