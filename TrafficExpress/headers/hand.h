#ifndef HAND_H
#define HAND_H

#include <cardcolection.h>
#include <vector>
#include "card.h"

class Hand:public QGraphicsObject
{
    Q_OBJECT
public:
    // Constructors
    Hand();
    Hand(const Hand&h);

    Hand(CardColection& cc);

    //geters
    CardColection&getCards();

    // Other methods
    void push_back(Card*);
    bool empty();

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
private:
    CardColection m_cards;
};

#endif // HAND_H
