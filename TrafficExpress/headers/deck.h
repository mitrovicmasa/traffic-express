#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>


class Deck:public QGraphicsObject,public std::vector<Card*>
{
    Q_OBJECT
public:
    Deck();

    //void addDeckToScene(QGraphicsScene*sc);
    void addCardToDeck(Card* card);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DECK_H
