#ifndef WAGON_H
#define WAGON_H

#include <sheriff.h>
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
    //this is not safe
    //Wagon(const Wagon&other);

    //this is a safe copy constructor
    Wagon(TreasureChest&upt,TreasureChest&downt,PlayerGroup&upp,PlayerGroup&downp, bool isLocomotive);

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

    void addSheriffDown();
    void takeSheriffDown();

    Treasure* takeContentUp(TreasureType);
    Treasure* takeContentDown(TreasureType);
    Player* takePlayerUp(BanditType );
    Player *takePlayerDown(BanditType );

    Treasure* takeContentUp(Treasure*);
    Treasure* takeContentDown(Treasure*);
    Player* takePlayerUp(Player* );
    Player* takePlayerDown(Player* );
    Sheriff* sheriffActions(Sheriff*);




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
    void repositionPlayers();

    bool isLocomotive() const;
    void setIsLocomotive(bool newIsLocomotive);

    Sheriff *sheriff() const;
    void setSheriff(Sheriff *newSheriff);

signals:
    void clicked();
    void clickedTreasureInWagon(Treasure*t,Wagon*w);
    void clickedPlayerInWagon(Player*,Wagon*);
    void clickedWagon(Wagon*w);

public slots:
    void OnCickedTreasuere(Treasure*t);
    void onClickedPlayer(Player*);

private:
    bool m_isLocomotive = false;
    TreasureChest m_contentUp;
    TreasureChest m_contentDown;
    PlayerGroup m_playersUp;
    PlayerGroup m_playersDown;
    Sheriff* m_sheriff;
};

#endif // WAGON_H
