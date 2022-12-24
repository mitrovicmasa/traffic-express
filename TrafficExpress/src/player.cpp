#include "../headers/player.h"

#include <time.h>

#include <QPainter>

// Constructors
Player::Player(BanditType id)
    : QGraphicsObject(), m_id(id),m_isItMyMove(false)
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
    m_deck->setAllCardsFaceDown();


    m_bulletDeck = std::vector<BulletCard*>();
    for(unsigned i = 1; i <= 6; i++){
        m_bulletDeck.push_back(new BulletCard(id, i));
    }

    m_roof = false;
    m_treasure = std::vector<Treasure*>();
    m_treasure.push_back(new Treasure());

    setFlags(GraphicsItemFlag::ItemIsSelectable);
    connect(m_hand,&Hand::clickedCardInHand,this,&Player::onClickedCardInHand);
    connect(m_deck,&Deck::clickedCardInDeck,this,&Player::onClickedCardInDeck);
}

//Player::Player(const Player &other)
//    :QGraphicsObject(),
//      m_id(other.m_id),
//      m_hand(new Hand(*(other.m_hand))),
//      m_deck(new Deck(*(other.m_deck))),
//      m_bulletDeck(std::vector<BulletCard*>()),
//      m_positionInTrain(other.m_positionInTrain),
//      m_roof(other.m_roof),
//      m_treasure(std::vector<Treasure*>()),
//      m_isItMyMove(other.m_isItMyMove)
//{

//    for(BulletCard*bc:other.m_bulletDeck)
//        m_bulletDeck.push_back((BulletCard*)bc->Copy());


//    for(Treasure*t:other.m_treasure)
//        m_treasure.push_back(new Treasure(*t));
//    connect(m_hand,&Hand::clickedCardInHand,this,&Player::onClickedCardInHand);
//}

Player::Player(bool isItMyMove, BanditType id, Hand *h, Deck *d, std::vector<BulletCard *> bcd, int pos, bool roof, TreasureChest tc)
    :m_isItMyMove(isItMyMove),m_id(id),m_hand(new Hand(h->getCards())),m_deck(new Deck(d->getCards())),
      m_bulletDeck(std::vector<BulletCard*>()),m_positionInTrain(pos),m_roof(roof),m_treasure(TreasureChest(tc))
{

//Todo bulletCardDeck
    connect(m_hand,&Hand::clickedCardInHand,this,&Player::onClickedCardInHand);
    connect(m_deck,&Deck::clickedCardInDeck,this,&Player::onClickedCardInDeck);
    for(BulletCard*bc:bcd)
        m_bulletDeck.push_back((BulletCard*)bc->Copy());



    setFlags(GraphicsItemFlag::ItemIsSelectable);
}



// Get methods

BanditType Player::id() const
{
    return m_id;
}

Hand *Player::hand()
{
    return m_hand;
}

Deck *Player::deck()
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

TreasureChest& Player::treasure()
{
    return m_treasure;
}

bool Player::isItMyMove() const
{
    return m_isItMyMove;
}

// Set methods
void Player::setPositionInTrain(int newPositionInTrain)
{
    m_positionInTrain = newPositionInTrain;
}

void Player::setRoof(bool newRoof)
{
    m_roof = newRoof;
}

void Player::setMyMove(bool v)
{
    m_isItMyMove=v;
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

void Player::returnCardsToDeck()
{
//    while(!m_hand->empty())
//    {
//        m_deck->push_back((m_hand->getCards());
//        m_hand->erase(m_hand->begin());
//    }
}

void Player::shuffleDeck()
{
    m_deck->schufleDeck();

}

void Player::drawCards(unsigned n)
{
    int originalDeckSize=m_deck->size();
    for(unsigned i=0; i<originalDeckSize && i<n; i++)
    {
        Card* front=m_deck->back();
        m_deck->pop_back();
        front->setFaceUp(true);
        m_hand->push_back(front);

    }

}

std::string Player::toString() const
{
    std::string positionInWagon = m_roof ? "Bandit is on the roof" : "Bandit is in the wagon";
    int currentAmountOfTreasure = countAmountOfTreasure();

    std::string cardsInDeck= "";
    for(auto x: (m_deck->getCards()))
        cardsInDeck += x->toString() + "\n";

    std::string cardsInHand= "";
    for(auto x: m_hand->getCards())
        cardsInHand += x->toString() + "\n";


    return "Bandit: "  + ::toString(m_id) + "\n"
         + "Position in train: " + std::to_string(m_positionInTrain) + "\n"
         + "Current amount of treasure: " + std::to_string(currentAmountOfTreasure) + "\n"
         + "Current number of cards in deck: " + std::to_string(m_deck->size()) + "\n"
         + "Current number of bullets in bullet deck: " + std::to_string(m_bulletDeck.size()) + "\n"
            + positionInWagon +"\nCards in deck:\n"+cardsInDeck+ "\n"+"\nCards in hand:\n"+cardsInHand+ "\n";
}

// GUI

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

int Player::width() const
{
    return 25;
}

int Player::height() const
{
    return 35;
}


void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    emit clickedPlayer(this);
}

void Player::onClickedCardInHand(Card *c, Hand *h)
{
    //std::cout<<"signal recieved in player from card!"<<std::endl;
    emit clickedCardInHandInPlayer(c,h,this);
}

void Player::onClickedCardInDeck(Card *c, Deck *d)
{

    emit clickedCardInDeckInPlayer(c,d,this);
}
