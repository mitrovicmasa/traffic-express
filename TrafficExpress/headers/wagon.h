#ifndef WAGON_H
#define WAGON_H

#include <treasure.h>
#include <vector>

class Wagon:public QGraphicsObject
{
    Q_OBJECT
public:

    // Constructors
    Wagon();
    Wagon(const std::vector<Treasure*> &contentDown, const std::vector<Treasure*> &contentUp);

    // Destructor


    // Get methods
    // Set methods


    // Other methods

    void addContentUp(  Treasure* );
    void addContentDown(Treasure*);

    Treasure* takeContentUp(TreasureType);
    Treasure* takeContentDown(TreasureType);
    int numberOfTreasureInWagonDown(TreasureType) const;

    std::string toString();
    int visina()const;
    int sirina()const;

private:

std::vector<Treasure*>m_contentUp;
std::vector<Treasure*>m_contentDown;

// QGraphicsItem interface
public:
QRectF boundingRect() const;
void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // WAGON_H
