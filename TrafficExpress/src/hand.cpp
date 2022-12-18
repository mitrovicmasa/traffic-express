#include "hand.h"
#include <qgraphicsscene.h>
#include <iostream>
// Constructors

Hand::Hand():QGraphicsObject(),std::vector<Card*>()
{

}

Hand::Hand(const Hand &h)
    :QGraphicsObject(),std::vector<Card*>()
{
    for(Card*c:h)
        this->push_back(c->Copy());
}

// GUI

void Hand::push_back(Card *card)
{
    connect(card, &Card::clicked, this, &Hand::test);
    connect(card, &Card::clickedCard, this, &Hand::onClickedCard);
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

void Hand::test()
{
    std::cout<<"Card clicked from hand!"<<std::endl;
}

void Hand::onClickedCard(Card*c)
{
    std::cout<<"Card clicked from hand! signal"<<std::endl;
    emit clickedCardInHand(c,this);
}

void Hand::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    std::cout<<"Hand clicked!Hand size:"<<this->size()<<std::endl;
    for (Card*c:(*this))
        std::cout<<"\t"<<c->toString()<<std::endl;

}
