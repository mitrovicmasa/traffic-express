#include "../headers/player.h"

#include <time.h>

// Constructors
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

Player::Player(BanditType id)
    :m_id(id)
{

    m_hand=std::vector<Card*>();
    m_deck=std::vector<Card*>();
    m_deck.push_back(new ActionCard(ActionType::MOVE,id));
    m_deck.push_back(new ActionCard(ActionType::MOVE,id));

    m_deck.push_back(new ActionCard(ActionType::FIRE,id));
    m_deck.push_back(new ActionCard(ActionType::FIRE,id));

    m_deck.push_back(new ActionCard(ActionType::FLOOR_CHANGE,id));
    m_deck.push_back(new ActionCard(ActionType::FLOOR_CHANGE,id));

    m_deck.push_back(new ActionCard(ActionType::MARSHAL,id));
    m_deck.push_back(new ActionCard(ActionType::PUNCH,id));

    m_deck.push_back(new ActionCard(ActionType::TAKETREASURE,id));
    m_deck.push_back(new ActionCard(ActionType::TAKETREASURE,id));


    m_bulletDeck = std::vector<BulletCard*>();
    for(unsigned i=1;i<=6;i++){
        m_bulletDeck.push_back(new BulletCard(id,i));
    }

    m_roof=false;
    m_treasure=std::vector<Treasure>();
    m_treasure.push_back(Treasure());
}

// Get methods
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

// Set methods
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

// Other methods


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

bool Player::isBulletDeckEmpty() const
{
    return m_bulletDeck.empty();
}

int Player::countAmountOfTreasure() const
{
    return std::accumulate(m_treasure.cbegin(), m_treasure.cend(), 0, [](int acc, auto treasure) { return acc + treasure.getValue(); });
}

void Player::shuffleDeck()
{
    srand(time(0));
    std::random_shuffle(this->m_deck.begin(),this->m_deck.end());
}

std::string Player::toString() const
{
    std::string positionInWagon = m_roof ? "Bandit is on the roof" : "Bandit is in the wagon";
    int currentAmountOfTreasure = countAmountOfTreasure();

    std::string cardsInDeck="";
    for(auto x:m_deck)
        cardsInDeck+=x->toString()+"\n";


    return "Bandit: "  + ::toString(m_id) + "\n"
         + "Position in train: " + std::to_string(m_positionInTrain) + "\n"
         + "Current amount of treasure: " + std::to_string(currentAmountOfTreasure) + "\n"
         + "Current number of cards in deck: " + std::to_string(m_deck.size()) + "\n"
         + "Current number of bullets in bullet deck: " + std::to_string(m_bulletDeck.size()) + "\n"
         + positionInWagon +"\ncards In deck:\n"+cardsInDeck+ "\n";
}
