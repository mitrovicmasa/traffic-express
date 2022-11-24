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

class Player
{
public:

    // Constructors
    Player();
    Player(BanditType id, const std::vector<Card*> &hand, const std::vector<Card*> &deck,
           const std::vector<BulletCard*> &bulletDeck, int positionInTrain, bool roof, const std::vector<Treasure> treasure);
    Player(BanditType id);
    Player(const Player &player);

    // Destructor
    ~Player() = default;

    // Operator overloading
    Player &operator=(const Player &player);

    // Get methods
    BanditType id() const;
    const std::vector<Card*> &hand() const;
    const std::vector<Card*> &deck() const;
    const std::vector<BulletCard*> &bulletCard() const;
    int positionInTrain() const;
    bool roof() const;
    const std::vector<Treasure> &treasure() const;

    // Set methods
    void setId(BanditType &newId);
    void setHand(const std::vector<Card*> &newHand);
    void setDeck(const std::vector<Card*> &newDeck);
    void setBulletDeck(const std::vector<BulletCard*> &newBulletDeck);
    void setPositionInTrain(int &newPositionInTrain);
    void setRoof(bool &newRoof);
    void setTreasure(std::vector<Treasure> newTreasure);

    // Other methods
    bool isBulletDeckEmpty() const;
    int countAmountOfTreasure() const;
    void shuffleDeck();

    std::string toString() const;

private:

    BanditType m_id;
    std::vector<Card*> m_hand;
    std::vector<Card*> m_deck;
    std::vector<BulletCard*> m_bulletDeck;
    int m_positionInTrain;
    bool m_roof;
    std::vector<Treasure> m_treasure;
};
#endif // PLAYER_H
