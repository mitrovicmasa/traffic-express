#include "../headers/train.h"

#include <qgraphicsscene.h>
#include <qpainter.h>
#include <qpainter.h>

Train::Train()
    :QGraphicsObject()
{

}

Train::Train(std::vector<Wagon *>wagons)
    :QGraphicsObject()
{
    for(Wagon*w :wagons){
        this->push_back(w);
    }
}

Train::Train(const Train &other)
    :QGraphicsObject()
{
    //TODO
    for(Wagon*w:other.m_wagons){
        this->push_back(new Wagon(*w));
    }

}

// Other methods
void Train::addTrainToScene(QGraphicsScene *sc)
{
    for(int i=0;i<m_wagons.size();i++){
        sc->addItem(m_wagons[i]);
        m_wagons[i]->setPos(i*300,100);

    }
}

void Train::push_back(Wagon*w)
{
    connect(w, &Wagon::clicked, this, &Train::test);
    connect(w, &Wagon::clickedTreasureInWagon, this, &Train::onClickedTreasureInWagon);
    connect(w,&Wagon::clickedWagon,this,&Train::onClickedWagon);
    m_wagons.push_back(w);
    w->setParentItem(this);
    w->setPos((m_wagons.size()-1)*200,10);
}

int Train::size()
{
    return m_wagons.size();
}

Wagon *Train::operator[](int i)
{
    return m_wagons[i];
}

WagonArray &Train::getWagons()
{
    return m_wagons;
}

// GUI
QRectF Train::boundingRect() const
{
    return QRectF(0,0,(m_wagons.size()+1)*200,200);
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

void Train::onClickedTreasureInWagon(Treasure *t, Wagon *w)
{
    emit clickedTreasureInWagonInTrain(t,w,this);
}

void Train::onClickedWagon(Wagon *w)
{
    std::cout<<"signal recieved in train from wagon!"<<std::endl;
    emit clickedWagonInTrain(w,this);
}


