#ifndef TREASURE_H
#define TREASURE_H

#include <QGraphicsObject>
#include<string>
#include <QMouseEvent>

enum class TreasureType{
   SUITCASE,DIAMOND,MONEYBAG
};

class Treasure:public QGraphicsObject
{
    Q_OBJECT
public:

    // Constructors
    Treasure();
    Treasure(int value,TreasureType type);
    Treasure(TreasureType type);
    Treasure(const Treasure&t);

    // Destructor


    // Operator overloading

    bool operator==(const Treasure&t);
    bool operator!=(const Treasure&t);

    // Get methods
    TreasureType getType();
    int getValue();

    // Set methods


    // Other methods
    int visina() const;
    int sirina() const;
    std::string toString();

signals:
    void Moved();

private:
    TreasureType m_type;
    unsigned m_value;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);




    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QGraphicsItem interface

};

#endif // TREASURE_H
