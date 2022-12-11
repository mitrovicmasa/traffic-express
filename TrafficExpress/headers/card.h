#ifndef CARD_H
#define CARD_H

#include<string>
#include <QGraphicsObject>
#include <qpainter.h>

enum CardType {
    ACTION_CARD,
    BULLET_CARD,
    NEUTRAL_BULLET
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
    virtual CardType Type() const=0;

    // GUI
    virtual int height()const;
    virtual int width()const;

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;

    void setFaceUp(bool newFaceUp);

    bool faceUp() const;

private:
    bool m_faceUp = true;
};

#endif // CARD_H
