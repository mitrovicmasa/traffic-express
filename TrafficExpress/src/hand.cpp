#include "hand.h"
#include <qgraphicsscene.h>
#include <iostream>
// Constructors

Hand::Hand():QGraphicsObject()
{

}

Hand::Hand(const Hand &h)
    :QGraphicsObject()
{
    for(Card*c:h.m_cards)
        this->push_back(c->Copy());
}

CardColection &Hand::getCards()
{
    return m_cards;
}

// GUI

void Hand::push_back(Card *card)
{
    connect(card, &Card::clicked, this, &Hand::test);
    connect(card, &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.push_back(card);
    card->setParentItem(this);
    card->setPos((m_cards.size()-1)*70+5,20);
}

bool Hand::empty()
{
    return m_cards.empty();
}

void Hand::repositionCards()
{
    for(int i=0;i<m_cards.size();i++){
        m_cards[i]->setPos(i*70+5,20);


    }
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
    std::cout<<"Hand clicked!Hand size:"<<m_cards.size()<<std::endl;
    for (Card*c:m_cards)
        std::cout<<"\t"<<c->toString()<<std::endl;

}
