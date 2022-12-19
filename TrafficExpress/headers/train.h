#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <wagon.h>
#include <treasure.h>
#include <wagonarray.h>



class Train:public QGraphicsObject
{
    Q_OBJECT

public:
    // Constructors
    Train();
    Train(std::vector<Wagon*>);
    Train(const Train&);
    //this is a copy constructor
    Train(WagonArray&wa);

    // Other methods
    void addTrainToScene(QGraphicsScene*sc);
    void push_back(Wagon*w);
    int size();
    Wagon* operator[](int i);
    //geters
    WagonArray&getWagons();

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
signals:
    void clickedTreasureInWagonInTrain(Treasure*t,Wagon*w,Train*train);
    void clickedWagonInTrain(Wagon*w,Train*train);
public slots:
    void onClickedTreasureInWagon(Treasure*t,Wagon*w);
    void onClickedWagon(Wagon*);

private:
    WagonArray m_wagons;
};

#endif // TRAIN_H
