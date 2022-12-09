#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include "treasure.h"
#include <QGraphicsObject>
#include <string>
#include <vector>

class Table: public QGraphicsObject, public std::vector<Player*>
{
    Q_OBJECT

public:

    // Constructors
    Table();


    // Other methods
    void addTableToScene(QGraphicsScene *sc);
    void addTreasureInTable(Treasure* );


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
