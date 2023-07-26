#include "headers/sheriff.h"
#include <QPainter>

// Constructors
Sheriff::Sheriff()
= default;

Sheriff::Sheriff(int positionInTrain)
{
    m_positionInTrain = positionInTrain;
}

// Get methods
int Sheriff::positionInTrain() const
{
    return m_positionInTrain;
}

// Set methods
void Sheriff::setPositionInTrain(int newPositionInTrain)
{
    m_positionInTrain = newPositionInTrain;
}

// GUI
int Sheriff::width() const
{
    return 50;
}

int Sheriff::height() const
{
    return 50;
}

QRectF Sheriff::boundingRect() const
{
    return QRectF(0, 0, width(), height());
}

void Sheriff::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(), QPixmap("://marshal.png"), QRectF(0,0,0,0));
}
