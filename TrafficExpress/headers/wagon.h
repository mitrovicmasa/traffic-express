#ifndef WAGON_H
#define WAGON_H

#include <player.h>
#include <treasure.h>
#include <vector>

class Wagon:public QGraphicsObject
{
    Q_OBJECT
public:

    // Constructors
    Wagon();
    Wagon(const std::vector<Treasure*> &contentDown, const std::vector<Treasure*> &contentUp);
    Wagon(const Wagon&other);

    // Destructor


    // Get methods
    std::vector<Treasure*> contentDown();
    std::vector<Treasure*> contentUp();

    // Set methods
    void setContentDown(std::vector<Treasure*> newContentDown);

    // Other methods

    void addContentUp(  Treasure* );
    void addContentDown(Treasure*);
    void addPlayerUp(Player*);
    void addPlayerDown(Player*);

    Treasure* takeContentUp(TreasureType);
    Treasure* takeContentDown(TreasureType);
    Player* takePlayerUp(BanditType );
    Player* takePlayerDown(BanditType );

    int numberOfTreasureInWagonDown(TreasureType) const;

    std::string toString();

    // GUI
    int height()const;
    int width()const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void testTreasure();
    void testPlayers();

signals:
    void clicked();

private:

    std::vector<Treasure*>m_contentUp;
    std::vector<Treasure*>m_contentDown;
    std::vector<Player*>m_playersUp;
    std::vector<Player*>m_playersDown;

};

#endif // WAGON_H
