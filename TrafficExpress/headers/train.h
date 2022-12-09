#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <wagon.h>



class Train:public QGraphicsObject,public std::vector<Wagon*>
{
    Q_OBJECT

public:
    Train();

    void addTrainToScene(QGraphicsScene*sc);
    void addWagonToTrain(Wagon*);
    void push_back(Wagon*w);
    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TRAIN_H
