#include "hand.h"
#include <qgraphicsscene.h>

Hand::Hand()
{

}

void Hand::addHandToScene(QGraphicsScene *sc)
{
    for(int i=0;i<size();i++){
        sc->addItem((*this)[i]);
        (*this)[i]->setPos(i*60,400);
    }
}
