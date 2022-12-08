#include "../headers/train.h"

#include <qgraphicsscene.h>
#include <qpainter.h>
#include <qpainter.h>

Train::Train()
    :QGraphicsObject(),std::vector<Wagon*>()
{

}

void Train::addTrainToScene(QGraphicsScene *sc)
{
    for(int i=0;i<size();i++){
        sc->addItem((*this)[i]);
        (*this)[i]->setPos(i*300,100);

    }
}

void Train::addWagonToTrain(Wagon *w)
{
    this->push_back(w);
    w->setParentItem(this);
    w->setPos((this->size()-1)*300,50);
}

QRectF Train::boundingRect() const
{
    return QRectF(0,0,(this->size()+1)*250,200);
}

void Train::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(50,50,50));
}


