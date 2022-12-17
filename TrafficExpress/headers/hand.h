#ifndef HAND_H
#define HAND_H

#include <vector>
#include "card.h"

class Hand:public QGraphicsObject, public std::vector<Card*>
{
    Q_OBJECT
public:
    // Constructors
    Hand();
    Hand(const Hand&h);

    // Other methods
    void push_back(Card*);

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
private:

};

#endif // HAND_H
