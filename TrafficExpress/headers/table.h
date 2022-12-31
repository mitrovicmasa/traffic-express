#ifndef TABLE_H
#define TABLE_H
#include "treasure.h"
#include "playerstats.h"
#include <QGraphicsObject>
#include <string>
#include <vector>
#include <signal.h>
#include <playerstatscollection.h>

class Table: public QGraphicsObject
{
    Q_OBJECT

public:
    // Constructors
    Table();

    // Get methods
    PlayerStatsCollection& getPlayerStats();

    // Other methods
    void addTableToScene(QGraphicsScene *sc);
    void push_back(PlayerStats* p);
    int size();
    PlayerStats*operator[](int);

    // GUI
    int height() const;
    int width() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void onClickedTreasureInPlayerStats(Treasure*,PlayerStats*);

signals:
    void clickedTreasureInPlayerStatsInTable(Treasure*,PlayerStats*,Table*);

private:
    std::vector<Treasure*> m_content;
    PlayerStatsCollection m_playerStats;
};

#endif // TABLE_H
