#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include "treasure.h"
#include "playerstats.h"
#include <QGraphicsObject>
#include <string>
#include <vector>
#include <signal.h>

class Table: public QGraphicsObject, public std::vector<PlayerStats*>
{
    Q_OBJECT

public:

    // Constructors
    Table();


    // Other methods
    void addTableToScene(QGraphicsScene *sc);
    void push_back(PlayerStats* p);


    // GUI
    int height() const;
    int width() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void test();
public slots:
    void onClickedTreasureInPlayerStats(Treasure*,PlayerStats*);
signals:
    void clickedTreasureInPlayerStatsnTable(Treasure*,PlayerStats*,Table*);
private:
    std::vector<Treasure*> m_content;

};

#endif // TABLE_H
