#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>


class Deck:public QGraphicsObject,public std::vector<Card*>
{
    Q_OBJECT
public:
    Deck();

    // GUI
    void addCardToDeck(Card* card);
    void push_back(Card*);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
};

#endif // DECK_H
