#ifndef WAGON_H
#define WAGON_H

#include <player.h>
#include <playergroup.h>
#include <treasure.h>
#include <treasurechest.h>
#include <vector>

class Wagon:public QGraphicsObject
{
    Q_OBJECT
public:

    // Constructors
    Wagon();
    Wagon(TreasureChest contentDown, TreasureChest contentUp);
    Wagon(const Wagon&other);
    //this is a copy constructor
    Wagon(TreasureChest&upt,TreasureChest&downt,PlayerGroup&upp,PlayerGroup&downp);

    // Destructor


    // Get methods
    TreasureChest& getContentDown();
    TreasureChest& getContentUp();
    PlayerGroup& getPlayersUp();
    PlayerGroup& getPlayersDown();

    // Set methods
    void setContentDown(TreasureChest newContentDown);

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

    void repositionTreasure();

signals:
    void clicked();
    void clickedTreasureInWagon(Treasure*t,Wagon*w);
    void clickedWagon(Wagon*w);

public slots:
    void OnCickedTreasuere(Treasure*t);
private:

    TreasureChest m_contentUp;
    TreasureChest m_contentDown;
    PlayerGroup m_playersUp;
    PlayerGroup m_playersDown;

};

#endif // WAGON_H
