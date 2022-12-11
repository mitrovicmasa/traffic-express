#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include "treasure.h"
#include "playerstats.h"
#include <QGraphicsObject>
#include <string>
#include <vector>

class Table: public QGraphicsObject, public std::vector<PlayerStats*>
{
    Q_OBJECT

public:

    // Constructors
    Table();


    // Other methods
    void addTableToScene(QGraphicsScene *sc);
    void addTreasureInTable(Treasure* );
    void push_back(PlayerStats* p);



    int height() const;
    int width() const;

private:
    std::vector<Treasure*> m_content;


    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // TABLE_H
