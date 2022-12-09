#include "../headers/player.h"

#include <time.h>

#include <QPainter>

// Constructors


Player::Player(BanditType id)
    :QGraphicsObject(),m_id(id)
{

    //m_hand=Hand();
    //m_deck=Deck();

//    m_deck.push_back(new ActionCard(ActionType::MOVE,id));
//    m_deck.back()->setParentItem(&m_deck);
//    m_deck.push_back(new ActionCard(ActionType::MOVE,id));
//    m_deck->back()->setParentItem(m_deck);
//    m_deck.push_back(new ActionCard(ActionType::FIRE,id));
//    m_deck->back()->setParentItem(m_deck);
//    m_deck.push_back(new ActionCard(ActionType::FIRE,id));
//    m_deck->back()->setParentItem(m_deck);
//    m_deck.push_back(new ActionCard(ActionType::FLOOR_CHANGE,id));
//    m_deck->back()->setParentItem(m_deck);
//    m_deck.push_back(new ActionCard(ActionType::FLOOR_CHANGE,id));

//    m_deck.push_back(new ActionCard(ActionType::MARSHAL,id));
//    m_deck->back()->setParentItem(m_deck);
//    m_deck.push_back(new ActionCard(ActionType::PUNCH,id));
//    m_deck->back()->setParentItem(m_deck);
//    m_deck.push_back(new ActionCard(ActionType::TAKETREASURE,id));
//    m_deck->back()->setParentItem(m_deck);
//    m_deck.push_back(new ActionCard(ActionType::TAKETREASURE,id));
//    m_deck->back()->setParentItem(m_deck);

    m_bulletDeck = std::vector<BulletCard*>();
    for(unsigned i=1;i<=6;i++){
        m_bulletDeck.push_back(new BulletCard(id,i));
    }

    m_roof=false;
    m_treasure=std::vector<Treasure*>();
    m_treasure.push_back(new Treasure());

}

// Get methods



// Set methods


// QT methods

QRectF Player::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor::fromRgb(0,50,60));
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
    std::random_shuffle(this->m_deck.begin(),this->m_deck.end());
}

std::string Player::toString() const
{
    std::string positionInWagon = m_roof ? "Bandit is on the roof" : "Bandit is in the wagon";
    int currentAmountOfTreasure = countAmountOfTreasure();

    std::string cardsInDeck= " ";
    for(auto x: m_deck)
        cardsInDeck += x->toString() + "\n";


    return "Bandit: "  + ::toString(m_id) + "\n"
         + "Position in train: " + std::to_string(m_positionInTrain) + "\n"
         + "Current amount of treasure: " + std::to_string(currentAmountOfTreasure) + "\n"
         + "Current number of cards in deck: " + std::to_string(m_deck.size()) + "\n"
         + "Current number of bullets in bullet deck: " + std::to_string(m_bulletDeck.size()) + "\n"
         + positionInWagon +"\ncards In deck:\n"+cardsInDeck+ "\n";
}
