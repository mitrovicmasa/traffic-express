#include "hand.h"
#include <qgraphicsscene.h>
#include <iostream>

// Constructors
Hand::Hand():QGraphicsObject()
{
    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

Hand::Hand(CardColection &cc)
{
    auto cpy = CardColection(cc);
    for(Card* c: cpy){
        this->push_back(c);
    }
    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

// Get methods
CardColection &Hand::getCards()
{
    return m_cards;
}

// Other methods

void Hand::push_back(Card *card)
{
    connect(card, &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.push_back(card);
    card->setParentItem(this);
    card->setPos((m_cards.size()-1)*70+5, 20);
}

void Hand::push_front(Card *card)
{
    connect(card, &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.insert(m_cards.begin(),card);
    card->setParentItem(this);
    card->setPos((m_cards.size()-1)*70+5, 20);
}

void Hand::pop_back()
{
    disconnect(m_cards.back(), &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.back()->setParentItem(nullptr);
    m_cards.pop_back();
}

void Hand::pop_front()
{
    disconnect(m_cards.front(), &Card::clickedCard, this, &Hand::onClickedCard);
    m_cards.front()->setParentItem(nullptr);
    m_cards.erase(m_cards.begin());
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

int Hand::size()
{
    return m_cards.size();
}

Card *Hand::operator[](int ind)
{
    return m_cards[ind];
}

Card *Hand::takeCard(int indexofCard)
{
    Card* c = m_cards[indexofCard];
    disconnect(c, &Card::clickedCard, this, &Hand::onClickedCard);
    c->setParentItem(nullptr);
    m_cards.erase(m_cards.begin() + indexofCard);
    repositionCards();
    return c;
}

void Hand::repositionCards()
{
    for(int i = 0; i < m_cards.size(); i++)
    {
        m_cards[i]->setPos(i*70+5, 20);
    }
}

int Hand::getCardIndex(Card *c)
{
    for(int i = 0; i < m_cards.size(); i++) {
        if(m_cards[i] == c) {
            return i;
        }
    }
    return -1;
}

// GUI
QRectF Hand::boundingRect() const
{
    return QRectF(0,0,700,120);
}

void Hand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(210,222,230));
    painter->drawPixmap(boundingRect(), QPixmap("://hands.png"), QRectF(0,0,0,0));
}

void Hand::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
}

void Hand::onClickedCard(Card*c)
{
    emit clickedCardInHand(c,this);
}

// Serializable interface
QVariant Hand::toVariant() const
{
    QVariantMap map;
    QVariantList list;
    for (auto *card: m_cards) {
        list.append(((ActionCard*)(card))->toVariant());
    }

    map.insert("cards", list);
    return map;
}

void Hand::fromVariant(const QVariant &variant)
{
    QVariantList list = variant.toMap().value("cards").toList();
    for (auto &card: list) {
        ActionCard *newCard = new ActionCard();
        newCard->fromVariant(card);
        this->push_back(newCard);
    }
}
