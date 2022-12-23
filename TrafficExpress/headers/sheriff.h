#ifndef SHERIFF_H
#define SHERIFF_H

#include <QGraphicsObject>

class Sheriff: public QGraphicsObject
{
    Q_OBJECT
public:
    Sheriff();
    Sheriff(int);

    int positionInTrain() const;
    void setPositionInTrain(int newPositionInTrain);

    // GUI
    int width()const;
    int height()const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int m_positionInTrain;
};

#endif // SHERIFF_H
