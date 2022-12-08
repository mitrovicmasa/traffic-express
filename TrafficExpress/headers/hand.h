#ifndef HAND_H
#define HAND_H

#include <vector>
#include "card.h"

class Hand:public std::vector<Card*>
{
public:
    Hand();

    void addHandToScene(QGraphicsScene*sc);
private:
};

#endif // HAND_H
