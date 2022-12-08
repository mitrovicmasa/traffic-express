#ifndef CARD_H
#define CARD_H

#include<string>
#include <QGraphicsObject>
#include <qpainter.h>

enum Side {
    FRONT,
    BACK
};

class Card:public QGraphicsObject
{
    Q_OBJECT
public:

    // Constructors
    Card();
    //virtual Card *Copy() const = 0;

    // Destructor
    virtual ~Card();

    // Other methods
    virtual std::string toString() const;
private:

    // QGraphicsItem interface
public:
    virtual int visina()const;
    virtual int sirina()const;

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
};

#endif // CARD_H
