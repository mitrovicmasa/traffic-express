#include "../headers/bulletcard.h"
// Constructors
BulletCard::BulletCard(BanditType bandit, unsigned numOfBullets):
    BanditCard(bandit),
    m_numOfBullets(numOfBullets)
{}

//Card *BulletCard::Copy() const
//{
//    return new BulletCard(*this);
//}

// Destructor
BulletCard::~BulletCard()
{

}

// Get methods
const unsigned &BulletCard::numOfBullets() const
{
    return m_numOfBullets;
}

// Set methods
void BulletCard::setNumOfBullets(const unsigned &newNumOfBullets)
{
    m_numOfBullets = newNumOfBullets;
}

// Other methods
std::string BulletCard::toString() const
{
    return BanditCard::toString() + " ima jos " + std::to_string(m_numOfBullets);
}

CardType BulletCard::Type() const
{
    return CardType::BULLET_CARD;
}

// GUI
void BulletCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(!this->faceUp()) {
        painter->drawPixmap(boundingRect(), QPixmap("://card_back.png"), QRectF(0,0,0,0));
        return ;
    }

    QString number = QString::number(this->numOfBullets());
    QString color;
    switch (this->bandit()) {
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
    QString path = "://bullet_" + color + "_" + number + ".png";
    painter->drawPixmap(boundingRect(), QPixmap(path), QRectF(0,0,0,0));
}

Card *BulletCard::Copy() const
{
    return new BulletCard(bandit(),m_numOfBullets);
}
