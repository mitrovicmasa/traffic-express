#include "../headers/train.h"

#include <qgraphicsscene.h>
#include <qpainter.h>
#include <qpainter.h>

Train::Train()
    :QGraphicsObject(),std::vector<Wagon*>()
{

}

Train::Train(std::vector<Wagon *>wagons)
    :QGraphicsObject(),std::vector<Wagon*>()
{
    for(Wagon*w :wagons)
        this->push_back(w);
}

// Other methods
void Train::addTrainToScene(QGraphicsScene *sc)
{
    for(int i=0;i<size();i++){
        sc->addItem((*this)[i]);
        (*this)[i]->setPos(i*300,100);

    }
}

void Train::push_back(Wagon*w)
{
    connect(w, &Wagon::clicked, this, &Train::test);
    std::vector<Wagon*>::push_back(w);
    w->setParentItem(this);
    w->setPos((this->size()-1)*200,10);
}

// GUI
QRectF Train::boundingRect() const
{
    return QRectF(0,0,(this->size()+1)*200,200);
}

void Train::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(100,100,100));
    painter->drawText(boundingRect(), "TRAIN:");
}

void Train::test()
{
    std::cout<<"Wagon clicked!"<<std::endl;
}


