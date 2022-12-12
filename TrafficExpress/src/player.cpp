#include "../headers/player.h"

#include <time.h>

#include <QPainter>

// Constructors
Player::Player(BanditType id)
    : QGraphicsObject(), m_id(id)
{

    m_hand = new Hand();
    m_deck = new Deck();

    m_deck->push_back(new ActionCard(ActionType::MOVE, id));
    m_deck->push_back(new ActionCard(ActionType::MOVE, id));
    m_deck->push_back(new ActionCard(ActionType::FIRE, id));
    m_deck->push_back(new ActionCard(ActionType::FIRE, id));
    m_deck->push_back(new ActionCard(ActionType::FLOOR_CHANGE, id));
    m_deck->push_back(new ActionCard(ActionType::FLOOR_CHANGE, id));
    m_deck->push_back(new ActionCard(ActionType::MARSHAL, id));
    m_deck->push_back(new ActionCard(ActionType::PUNCH, id));
    m_deck->push_back(new ActionCard(ActionType::TAKETREASURE, id));
    m_deck->push_back(new ActionCard(ActionType::TAKETREASURE, id));


    m_bulletDeck = std::vector<BulletCard*>();
    for(unsigned i = 1; i <= 6; i++){
        m_bulletDeck.push_back(new BulletCard(id, i));
    }

    m_roof = false;
    m_treasure = std::vector<Treasure*>();
    m_treasure.push_back(new Treasure());
}



// Get methods

BanditType Player::id() const
{
    return m_id;
}

Hand *Player::hand() const
{
    return m_hand;
}

Deck *Player::deck() const
{
    return m_deck;
}

const std::vector<BulletCard*> &Player::bulletDeck() const
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

const std::vector<Treasure*> &Player::treasure()
{
    return m_treasure;
}

// Set methods
void Player::setPositionInTrain(int newPositionInTrain)
{
    m_positionInTrain = newPositionInTrain;
}

// QT methods

QRectF Player::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString color;
    switch (this->m_id) {
        case BanditType::PICKPOCKET:
            color = "green";
            break;
        case BanditType::SEDUCTRESS:
            color = "yellow";
            break;
        case BanditType::STUDENT:
            color = "blue";
            break;
        case BanditType::RETIREE:
            color = "red";
            break;
        case BanditType::HOMELESS_MAN:
            color = "orange";
            break;
        case BanditType::BUSINESS_WOMAN:
            color = "purple";
            break;
        default:
            return;
    }
    QString path = "://player_" + color + ".png";
    painter->drawPixmap(boundingRect(), QPixmap(path), QRectF(0,0,0,0));
}

// Other methods

bool Player::isBulletDeckEmpty() const
{
    return m_bulletDeck.empty();
}

int Player::countAmountOfTreasure() const
{
    return std::accumulate(m_treasure.cbegin(), m_treasure.cend(), 0, [](int acc, auto treasure) { return acc + treasure->getValue(); });
}

void Player::shuffleDeck()
{
    srand(time(0));
    std::random_shuffle(this->m_deck->begin(),this->m_deck->end());
}

std::string Player::toString() const
{
    std::string positionInWagon = m_roof ? "Bandit is on the roof" : "Bandit is in the wagon";
    int currentAmountOfTreasure = countAmountOfTreasure();

    std::string cardsInDeck= " ";
    for(auto x: *m_deck)
        cardsInDeck += x->toString() + "\n";


    return "Bandit: "  + ::toString(m_id) + "\n"
         + "Position in train: " + std::to_string(m_positionInTrain) + "\n"
         + "Current amount of treasure: " + std::to_string(currentAmountOfTreasure) + "\n"
         + "Current number of cards in deck: " + std::to_string(m_deck->size()) + "\n"
         + "Current number of bullets in bullet deck: " + std::to_string(m_bulletDeck.size()) + "\n"
            + positionInWagon +"\ncards In deck:\n"+cardsInDeck+ "\n";
}

int Player::width() const
{
    return 25;
}

int Player::height() const
{
    return 35;
}
