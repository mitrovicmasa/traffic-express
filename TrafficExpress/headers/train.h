#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <wagon.h>
#include <treasure.h>
#include <wagonarray.h>

class Train:public QGraphicsObject, public Serializable
{
    Q_OBJECT

public:
    // Constructors
    Train();
    Train(std::vector<Wagon*>);
    Train(WagonArray& wa);

    // Get methods
    WagonArray&getWagons();
    int getWagonIndex(Wagon*);

    // Other methods
    void push_back(Wagon* w);
    void push_front(Wagon*);
    Wagon* back();
    Wagon* front();
    void pop_back();
    void pop_front();
    int size();
    bool empty();
    Wagon* operator[](int i);

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Serializable interface
    QVariant toVariant() const;
    void fromVariant(const QVariant &variant);

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
