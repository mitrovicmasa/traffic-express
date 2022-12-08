#include "../headers/bulletcard.h"
// Constructors
BulletCard::BulletCard(BanditType bandit, unsigned numOfBullets) : BanditCard(bandit)
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

void BulletCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    switch (this->bandit()) {
        case BanditType::PICKPOCKET:
            painter->fillRect(boundingRect(),QColor::fromRgb(80,110,240));
            break;
        case BanditType::SEDUCTRESS:
            painter->fillRect(boundingRect(),QColor::fromRgb(240,80,120));
            break;
        case BanditType::STUDENT:
            painter->fillRect(boundingRect(),QColor::fromRgb(220,80,240));
            break;
        case BanditType::RETIREE:
            painter->fillRect(boundingRect(),QColor::fromRgb(50,150,100));
            break;
        case BanditType::HOMELESS_MAN:
            painter->fillRect(boundingRect(),QColor::fromRgb(240,240,80));
            break;
        case BanditType::BUSINESS_WOMAN:
            painter->fillRect(boundingRect(),QColor::fromRgb(240,150,80));
            break;
        default:
            return;
    }
}
