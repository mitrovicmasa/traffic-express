#include "hand.h"
#include <qgraphicsscene.h>
#include <iostream>
// Constructors

Hand::Hand():QGraphicsObject()
{

}

//Hand::Hand(const Hand &h)
//    :QGraphicsObject()
//{
//    for(Card*c:h.m_cards)
//        this->push_back(c->Copy());
//}

Hand::Hand(CardColection &cc)
{
    auto cpy=CardColection(cc);
    for(Card*c:cpy){

        this->push_back(c);
    }
}

CardColection &Hand::getCards()
{
    return m_cards;
}

// GUI

void Hand::push_back(Card *card)
{
    //connect(card, &Card::clicked, this, &Hand::test);
    connect(card, &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.push_back(card);
    card->setParentItem(this);
    card->setPos((m_cards.size()-1)*70+5,20);
}

void Hand::pop_back()
{
    //disconnect(m_cards.back(), &Card::clicked, this, &Hand::test);
    disconnect(m_cards.back(), &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.back()->setParentItem(nullptr);
    m_cards.pop_back();

}

Card *Hand::back()
{
    return m_cards.back();
}

Card *Hand::front()
{
    return m_cards.front();
}

bool Hand::empty()
{
    return m_cards.empty();
}

void Hand::push_front(Card *card)
{

    //connect(card, &Card::clicked, this, &Hand::test);
    connect(card, &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.insert(m_cards.begin(),card);
    card->setParentItem(this);
    card->setPos((m_cards.size()-1)*70+5,20);
}

void Hand::pop_front()
{
    //disconnect(m_cards.front(), &Card::clicked, this, &Hand::test);
    disconnect(m_cards.front(), &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.front()->setParentItem(nullptr);
    m_cards.erase(m_cards.begin());


}

Card *Hand::takeCard(Card *c)
{
    for(auto it=m_cards.begin();it!=m_cards.end();it++){
        if(c==*it){
            disconnect(c, &Card::clickedCard, this, &Hand::onClickedCard);
            c->setParentItem(nullptr);
            m_cards.erase(it);
            repositionCards();
            return c;
        }

    }
    return nullptr;
}

Card *Hand::takeCard(int indexofCard)
{
//    qDebug()<<"indexofCard"<<indexofCard;
//    qDebug()<<"size of hand"<<m_cards.size();
    Card* c=m_cards[indexofCard];
    disconnect(c, &Card::clickedCard, this, &Hand::onClickedCard);
    c->setParentItem(nullptr);
    m_cards.erase(m_cards.begin()+indexofCard);
    repositionCards();
    return c;

}

void Hand::repositionCards()
{
    for(int i=0;i<m_cards.size();i++){
        m_cards[i]->setPos(i*70+5,20);


    }
}

int Hand::getCardIndex(Card *c)
{
    for(int i=0;i<m_cards.size();i++){
        if(m_cards[i]==c){
            return i;

        }
    }
    return -1;
}

QRectF Hand::boundingRect() const
{
    return QRectF(0,0,700,120);
}

void Hand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(210,222,230));
    painter->drawPixmap(boundingRect(), QPixmap("://hands.png"), QRectF(0,0,0,0));
}

void Hand::test()
{
    std::cout<<"Card clicked from hand!"<<std::endl;
}

void Hand::onClickedCard(Card*c)
{
    //std::cout<<"Card clicked from hand! signal"<<std::endl;
    emit clickedCardInHand(c,this);
}

void Hand::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    std::cout<<"Hand clicked!Hand size:"<<m_cards.size()<<std::endl;
    for (Card*c:m_cards)
        std::cout<<"\t"<<c->toString()<<std::endl;

}
