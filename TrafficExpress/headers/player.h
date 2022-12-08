#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <functional>

#include <card.h>
#include <treasure.h>
#include <actioncard.h>
#include <banditcard.h>
#include <bulletcard.h>
#include <deck.h>
#include <hand.h>

class Player:public QGraphicsObject
{
    Q_OBJECT

public:

    // Constructors
    Player();
    Player(BanditType id);
    Player(const Player &player);

    // Destructor
    ~Player() = default;

    // Operator overloading
    Player &operator=(const Player &player);

    // Get methods


    // Set methods


    // QT methods

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    // Other methods
    bool isBulletDeckEmpty() const;
    int countAmountOfTreasure() const;
    void shuffleDeck();

    std::string toString() const;

private:

    BanditType m_id;
    Hand m_hand;
    Deck m_deck;
    std::vector<BulletCard*> m_bulletDeck;
    int m_positionInTrain;
    bool m_roof;
    std::vector<Treasure*> m_treasure;
};
#endif // PLAYER_H
