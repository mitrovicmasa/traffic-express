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
    //this is not safe
//    Train(const Train&);

    //this is a safe copy constructor
    Train(WagonArray&wa);

    // Other methods
    void addTrainToScene(QGraphicsScene*sc);
    void push_back(Wagon*w);
    Wagon*back();
    Wagon*front();
    void pop_back();
    int size();
    bool empty();
    void push_front(Wagon*);
    void pop_front();
    Wagon* operator[](int i);
    //geters
    WagonArray&getWagons();

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
signals:
    void clickedTreasureInWagonInTrain(Treasure*t,Wagon*w,Train*train);
    void clickedPlayerInWagonInTrain(Player*,Wagon*,Train*);
    void clickedWagonInTrain(Wagon*w,Train*train);
public slots:
    void onClickedTreasureInWagon(Treasure*t,Wagon*w);
    void onClickedPlayerInWagon(Player*,Wagon*);
    void onClickedWagon(Wagon*);

private:
    WagonArray m_wagons;
};

#endif // TRAIN_H
