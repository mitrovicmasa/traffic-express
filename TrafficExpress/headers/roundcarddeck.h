#ifndef ROUNDCARDDECK_H
#define ROUNDCARDDECK_H

#include <QGraphicsObject>
#include <QObject>
#include <roundcardcollection.h>

class RoundCardDeck : public QGraphicsObject
{
    Q_OBJECT
public:
    RoundCardDeck();
    RoundCardDeck(std::vector<RoundCard*>);

    RoundCardDeck(const RoundCardCollection&);

    RoundCard*operator[](int);
    RoundCard*back();
    RoundCard*front();
    int size();

    void push_front(RoundCard*);
    void pop_front();


    void setRoundOnScene(int i);


    RoundCardCollection& getRoundCads();

    int width()const;
    int height()const;
private:
    RoundCardCollection m_rounds;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // ROUNDCARDDECK_H
