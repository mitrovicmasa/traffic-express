#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <player.h>
#include <bulletcard.h>
#include <QGraphicsItem>


class PlayerStats: public QGraphicsObject
{
    Q_OBJECT
public:
    PlayerStats();

    PlayerStats(Player*);

private:
    Player *m_player;

    //QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
};



#endif // PLAYERSTATS_H
