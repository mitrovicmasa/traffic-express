#ifndef TREASURE_H
#define TREASURE_H

#include <QGraphicsObject>
#include<string>
#include <QMouseEvent>
#include <serializable.h>

enum class TreasureType{
   SUITCASE,DIAMOND,MONEYBAG
};

class Treasure:public QGraphicsObject,public Serializable
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

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();
    void clickedTreasure(Treasure*t);

private:
    TreasureType m_type;
    unsigned m_value;


    // Serializable interface
public:
    QVariant toVariant() const;
    void fromVariant(const QVariant &variant);
};

#endif // TREASURE_H
