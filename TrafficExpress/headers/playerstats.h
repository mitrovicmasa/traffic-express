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
    PlayerStats(Player*,bool deepCopy=false);

    // Get methods
    Player* getPlayer();

    // Other methods
    void addTreasureToPlayer(Treasure*);
    Treasure* takeTreasureFromPlayer(Treasure*);

    // GUI
    void repositionTreasure();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void onTreasureClicked(Treasure*);

signals:
    void clickedTreasueInPlayeStats(Treasure*,PlayerStats*);

private:
    Player *m_player;
};

#endif // PLAYERSTATS_H
