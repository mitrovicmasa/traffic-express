#ifndef HAND_H
#define HAND_H

#include <vector>
#include "card.h"

class Hand:public QGraphicsObject, public std::vector<Card*>
{
    Q_OBJECT
public:
    // Constructors
    Hand();
    Hand(const Hand&h);

    // Other methods
    void push_back(Card*);

    void repositionCards();


    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
private:

signals:
    void clickedCardInHand(Card*c,Hand*h);

public slots:
    void onClickedCard(Card*c);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // HAND_H
