#include "deck.h"
#include <qgraphicsscene.h>
#include <iostream>
#include <random>
#include <algorithm>
Deck::Deck():QGraphicsObject()
{
setFlags(GraphicsItemFlag::ItemIsSelectable);
}

//Deck::Deck(const Deck &d)
//    :QGraphicsObject()
//{
//    //TODO
//    for(Card* c:d.m_cards)
//        this->push_back(c->Copy());
//}

Deck::Deck(CardColection cc)
{
    auto cpy=CardColection(cc);
    for(Card*c:cpy){
        this->push_back(c);

    }
setFlags(GraphicsItemFlag::ItemIsSelectable);
}

CardColection &Deck::getCards()
{
    return m_cards;
}

// GUI

void Deck::push_back(Card *card)
{
    connect(card, &Card::clickedCard, this, &Deck::onClickedCard);
    m_cards.push_back(card);
    card->setParentItem(this);
    card->setPos(10,20);
}

void Deck::pop_back()
{
    disconnect(m_cards.back(),&Card::clickedCard,this,&Deck::onClickedCard);
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
    connect(card, &Card::clickedCard, this, &Deck::onClickedCard);
    m_cards.insert(m_cards.begin(),card);
    card->setParentItem(this);
    card->setPos(5,20);
}

void Deck::pop_front()
{
    disconnect(m_cards.front(),&Card::clickedCard,this,&Deck::onClickedCard);
    m_cards.front()->setParentItem(nullptr);
    m_cards.erase(m_cards.begin());
}

void Deck::schufleDeck(int seed)
{
    //TODO
        //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle (m_cards.begin(),m_cards.end(), std::default_random_engine(seed));
}

QVariant Deck::toVariant() const
{
    QVariantList list;
    for (auto *card : m_cards) {
        list.append(((ActionCard*)(card))->toVariant());
    }

    QVariantMap map;
    map.insert("cards", list);

    return map;
}

void Deck::fromVariant(const QVariant &variant)
{
    QVariantList list = variant.toMap().value("cards").toList();
    for (auto &card : list) {
        ActionCard *newCard=new ActionCard();
        newCard->fromVariant(card);
        this->push_back(newCard);
    }
}


void Deck::repositionCards()
{
    for(Card*c:m_cards)
        c->setPos(10,20);
}


QRectF Deck::boundingRect() const
{
    return QRectF(0,0,100,120);
}

void Deck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->fillRect(boundingRect(),QColor(210,222,230));
//    painter->drawText(boundingRect(), "DECK:");
      painter->drawPixmap(boundingRect(), QPixmap("://deck.png"), QRectF(0,0,0,0));
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

void Deck::onClickedCard(Card *c)
{
    //std::cout<<"Card clicked from deck! signal"<<std::endl;
    emit clickedCardInDeck(c,this);

}

void Deck::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    std::cout<<"Deck clicked!Deck size:"<<m_cards.size()<<std::endl;
}
