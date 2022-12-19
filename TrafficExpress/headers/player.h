#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <functional>
#include <random>
#include <chrono>
#include <card.h>
#include <treasure.h>
#include <actioncard.h>
#include <banditcard.h>
#include <bulletcard.h>
#include <deck.h>
#include <hand.h>
#include <treasurechest.h>

class Player : public QGraphicsObject
{
    Q_OBJECT

public:

    // Constructors

    Player(BanditType id);
    Player(const Player&);

    //this is a copy constructor

    Player(bool isItMyMove,BanditType id,Hand*h,Deck*d,std::vector<BulletCard*> bcd,int pos,bool roof,TreasureChest tc);

    // Destructor
    ~Player() = default;

    // Operator overloading
    Player &operator=(const Player &player);

    // Get methods
    BanditType id() const;
    Hand *hand() const;
    Deck *deck() const;
    const std::vector<BulletCard*> &bulletDeck() const;
    int positionInTrain() const;
    bool roof() const;
    TreasureChest& treasure();
    bool isItMyMove()const;

    // Set methods
    void setPositionInTrain(int newPositionInTrain);
    void setRoof(bool newRoof);
    void setMyMove(bool);

    // Other methods
    bool isBulletDeckEmpty() const;
    int countAmountOfTreasure() const;
    void returnCardsToDeck();
    void shuffleDeck();
    void drawCards(unsigned n);


    std::string toString() const;
    int width()const;
    int height()const;

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();
    void clickedCardInHandInPlayer(Card*c,Hand*h,Player*p);
public slots:
    void onClickedCardInHand(Card*c,Hand*h);

private:
    bool m_isItMyMove;
    BanditType m_id;
    Hand *m_hand;
    Deck *m_deck;
    std::vector<BulletCard*> m_bulletDeck;
    int m_positionInTrain;
    bool m_roof;
    TreasureChest m_treasure;
};
#endif // PLAYER_H
