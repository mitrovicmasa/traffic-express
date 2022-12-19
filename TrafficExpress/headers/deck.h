#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <cardcolection.h>
#include <vector>


class Deck:public QGraphicsObject
{
    Q_OBJECT
public:
    // Constructors
    Deck();
    Deck(const Deck&);
    //this is a copy constructor
    Deck(CardColection cc);


    //geters
    CardColection& getCards();

    // Other methods
    void push_back(Card*);
    void pop_back();
    int size();
    Card*back();
    Card*front();

    void push_front(Card*);
    void pop_front();

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
    void setAllCardsFaceDown();
    void setAllCardsFaceUp();

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    CardColection m_cards;
};

#endif // DECK_H
