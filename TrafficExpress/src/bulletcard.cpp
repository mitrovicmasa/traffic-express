#include "../headers/bulletcard.h"

// Constructors
BulletCard::BulletCard(BanditType bandit, unsigned numOfBullets) : BanditCard(bandit)
{}

Card *BulletCard::Copy() const
{
    return new BulletCard(*this);
}

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
