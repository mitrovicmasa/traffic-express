#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <player.h>
#include <bulletcard.h>
#include <QGraphicsItem>


class PlayerStats: public QGraphicsObject
{
    Q_OBJECT
public:
    // Constructors
    PlayerStats();
    PlayerStats(Player*);

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();

private:
    Player *m_player;
};



#endif // PLAYERSTATS_H
