#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>


class Deck:public QGraphicsObject,public std::vector<Card*>
{
    Q_OBJECT
public:
    // Constructors
    Deck();
    Deck(const Deck&);

    // Other methods
    void push_back(Card*);

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
};

#endif // DECK_H
