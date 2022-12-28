#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <cardcolection.h>
#include <serializable.h>
#include <vector>


class Deck : public QGraphicsObject, public Serializable
{
    Q_OBJECT
public:
    // Constructors
    Deck();
    //copy constructor dangerous
    //Deck(const Deck&);

    //this is a safe copy constructor
    Deck(CardColection cc);


    //geters
    CardColection& getCards();

    // Other methods
    void push_back(Card*);
    void pop_back();
    int size();
    bool empty();
    Card*back();
    Card*front();
    Card* operator[] (int ind);
    void push_front(Card*);
    void pop_front();
    void schufleDeck();
    void repositionCards();
    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
    void setAllCardsFaceDown();
    void setAllCardsFaceUp();

signals:
    void clickedCardInDeck(Card*c,Deck*d);

public slots:
    void onClickedCard(Card*c);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    CardColection m_cards;

public:
    QVariant toVariant() const;
    void fromVariant(const QVariant &variant);
};

#endif // DECK_H
