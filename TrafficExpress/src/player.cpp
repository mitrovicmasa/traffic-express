#include "../headers/player.h"

Player::Player()
{}

Player::Player(BanditType id, const std::vector<Card*> &hand, const std::vector<Card*> &deck,
               const std::vector<BulletCard*> &bulletDeck, int positionInTrain, bool roof, const std::vector<Treasure> treasure)
    : m_id(id),
      m_hand(hand),
      m_deck(deck),
      m_bulletDeck(bulletDeck),
      m_positionInTrain(positionInTrain),
      m_roof(roof),
      m_treasure(treasure)
{}

Player::Player(const Player &player)
    : m_id(player.m_id),
      m_hand(player.m_hand),
      m_deck(player.m_deck),
      m_bulletDeck(player.m_bulletDeck),
      m_positionInTrain(player.m_positionInTrain),
      m_roof(player.m_roof),
      m_treasure(player.m_treasure)
{}


Player &Player::operator=(const Player &player)
{
    auto tmp = Player(player);
    std::swap(m_id, tmp.m_id);
    std::swap(m_hand, tmp.m_hand);
    std::swap(m_deck, tmp.m_deck);
    std::swap(m_bulletDeck, tmp.m_bulletDeck);
    std::swap(m_positionInTrain, tmp.m_positionInTrain);
    std::swap(m_roof, tmp.m_roof);
    std::swap(m_treasure, tmp.m_treasure);

    return *this;
}

BanditType Player::id() const
{
    return m_id;
}

const std::vector<Card*> &Player::hand() const
{
    return m_hand;
}

const std::vector<Card*> &Player::deck() const
{
    return m_deck;
}

const std::vector<BulletCard*> &Player::bulletCard() const
{
    return m_bulletDeck;
}

int Player::positionInTrain() const
{
    return m_positionInTrain;
}

bool Player::roof() const
{
    return m_roof;
}

const std::vector<Treasure> &Player::treasure() const
{
    return m_treasure;
}

void Player::setId(BanditType &newId)
{
    m_id = newId;
}

void Player::setHand(const std::vector<Card*> &newHand)
{
    m_hand = newHand;
}

void Player::setDeck(const std::vector<Card*> &newDeck)
{
    m_deck = newDeck;
}

void Player::setBulletDeck(const std::vector<BulletCard*> &newBulletDeck)
{
    m_bulletDeck = newBulletDeck;
}

void Player::setPositionInTrain(int &newPositionInTrain)
{
    m_positionInTrain = newPositionInTrain;
}

void Player::setRoof(bool &newRoof)
{
    m_roof = newRoof;
}

void Player::setTreasure(std::vector<Treasure> newTreasure)
{
    m_treasure = newTreasure;
}

bool Player::isBulletDeckEmpty() const
{
    return m_bulletDeck.empty();
}

int Player::countAmountOfTreasure() const
{
    return std::accumulate(m_treasure.cbegin(), m_treasure.cend(), 0, [](int acc, auto treasure) { return acc + treasure.getValue(); });
}

std::string Player::toString() const
{
    std::string positionInWagon = m_roof ? "Bandit is on the roof" : "Bandit is in the wagon";
    int currentAmountOfTreasure = countAmountOfTreasure();

    return "Bandit: "  + ::toString(m_id) + "\n"
         + "Position in train: " + std::to_string(m_positionInTrain) + "\n"
         + "Current amount of treasure: " + std::to_string(currentAmountOfTreasure) + "\n"
         + "Current number of cards in deck: " + std::to_string(m_deck.size()) + "\n"
         + "Current number of bullets in bullet deck: " + std::to_string(m_bulletDeck.size()) + "\n"
         + positionInWagon + "\n";
}
