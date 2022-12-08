#include "deck.h"
#include <qgraphicsscene.h>

Deck::Deck()
{

}

void Deck::addDeckToScene(QGraphicsScene *sc)
{
    for(int i=0;i<size();i++){
        sc->addItem((*this)[i]);
        (*this)[i]->setPos(800,400);
    }
}
