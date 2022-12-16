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

class Player : public QGraphicsObject
{
    Q_OBJECT

public:

    // Constructors

    Player(BanditType id);

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
    std::vector<Treasure*> treasure();

    // Set methods
    void setPositionInTrain(int newPositionInTrain);
    void setRoof(bool newRoof);

    // Other methods
    bool isBulletDeckEmpty() const;
    int countAmountOfTreasure() const;
    void returnCardsToDeck();
    void shuffleDeck();
    void drawStartingCards();

    std::string toString() const;
    int width()const;
    int height()const;

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();

private:

    BanditType m_id;
    Hand *m_hand;
    Deck *m_deck;
    std::vector<BulletCard*> m_bulletDeck;
    int m_positionInTrain;
    bool m_roof;
    std::vector<Treasure*> m_treasure;
};
#endif // PLAYER_H
