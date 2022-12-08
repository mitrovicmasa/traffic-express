#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>


class Deck:public std::vector<Card*>
{
public:
    Deck();

    void addDeckToScene(QGraphicsScene*sc);
};

#endif // DECK_H
