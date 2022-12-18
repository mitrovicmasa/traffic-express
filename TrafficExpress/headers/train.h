#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <wagon.h>
#include <treasure.h>



class Train:public QGraphicsObject,public std::vector<Wagon*>
{
    Q_OBJECT

public:
    // Constructors
    Train();
    Train(std::vector<Wagon*>);
    Train(const Train&);

    // Other methods
    void addTrainToScene(QGraphicsScene*sc);
    void push_back(Wagon*w);

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
signals:
    void clickedTreasureInWagonInTrain(Treasure*t,Wagon*w,Train*train);
public slots:
    void onClickedTreasureInWagon(Treasure*t,Wagon*w);
};

#endif // TRAIN_H
