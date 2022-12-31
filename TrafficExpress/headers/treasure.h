#ifndef TREASURE_H
#define TREASURE_H

#include <QGraphicsObject>
#include<string>
#include <QMouseEvent>
#include <serializable.h>

enum class TreasureType{
   SUITCASE,
   DIAMOND,
   MONEYBAG
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

    // Get methods
    TreasureType getType();
    int getValue();

    // Other methods
    bool operator==(const Treasure&t);
    bool operator!=(const Treasure&t);
    std::string toString();

    // GUI
    int height() const;
    int width() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // Serializable interface
    QVariant toVariant() const;
    void fromVariant(const QVariant &variant);

signals:
    void clicked();
    void clickedTreasure(Treasure*t);

private:
    TreasureType m_type;
    unsigned m_value;
};

#endif // TREASURE_H
