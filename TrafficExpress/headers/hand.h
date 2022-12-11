#ifndef HAND_H
#define HAND_H

#include <vector>
#include "card.h"

class Hand:public QGraphicsObject, public std::vector<Card*>
{
    Q_OBJECT
public:
    Hand();

    // GUI
    void addCardToHand(Card* card);
    void push_back(Card*);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
};

#endif // HAND_H
