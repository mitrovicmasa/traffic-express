#include "../headers/train.h"

#include <qgraphicsscene.h>
#include <qpainter.h>

Train::Train()
    :std::vector<Wagon*>()
{

}

void Train::addTrainToScene(QGraphicsScene *sc)
{
    for(int i=0;i<size();i++){
        sc->addItem((*this)[i]);
        (*this)[i]->setPos(i*300,100);

    }
}


