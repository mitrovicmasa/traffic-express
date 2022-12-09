#include "hand.h"
#include <qgraphicsscene.h>

//Hand::Hand()
//{

//}

Hand::Hand():QGraphicsObject(),std::vector<Card*>()
{

}

//void Hand::addHandToScene(QGraphicsScene *sc)
//{
//    for(int i=0;i<size();i++){
//        sc->addItem((*this)[i]);
//        (*this)[i]->setPos(i*60,400);
//    }
//}

void Hand::addCardToHand(Card *card)
{
    this->push_back(card);
    card->setParentItem(this);
    card->setPos((this->size()-1)*60,50);
}

void Hand::push_back(Card *card)
{
    std::vector<Card*>::push_back(card);
    card->setParentItem(this);
    card->setPos((this->size()-1)*60,50);
}

QRectF Hand::boundingRect() const
{
    return QRectF(0,0,(this->size()+1)*100,200);
}

void Hand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(150,150,150));
}
