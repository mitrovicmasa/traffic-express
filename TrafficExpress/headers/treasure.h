#ifndef TREASURE_H
#define TREASURE_H

#include <QGraphicsObject>
#include<string>
enum class TreasureType{
   SUITCASE,DIAMOND,MONEYBAG
};

class Treasure:public QGraphicsObject
{
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

private:
    TreasureType m_type;
    unsigned m_value;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TREASURE_H
