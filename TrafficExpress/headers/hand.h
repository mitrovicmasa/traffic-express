#ifndef HAND_H
#define HAND_H

#include <cardcolection.h>
#include <vector>
#include "card.h"

class Hand:public QGraphicsObject
{
    Q_OBJECT
public:
    // Constructors
    Hand();
    //this is not safe
    //Hand(const Hand&h);

    //this is a safe copy constructor
    Hand(CardColection& cc);

    //geters
    CardColection&getCards();

    // Other methods
    void push_back(Card*);
    void pop_back();
    Card*back();
    Card*front();
    bool empty();
    void push_front(Card*);
    void pop_front();

    Card* takeCard(Card*);

    void repositionCards();

    Card* operator[] (int ind) {return m_cards[ind];}

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
private:

signals:
    void clickedCardInHand(Card*c,Hand*h);

public slots:
    void onClickedCard(Card*c);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    CardColection m_cards;
};

#endif // HAND_H
