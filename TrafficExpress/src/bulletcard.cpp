#include "../headers/bulletcard.h"

BulletCard::BulletCard(BanditType bandit, unsigned numOfBullets) : BanditCard(bandit)
{}

std::string BulletCard::toString() const
{
    return BanditCard::toString() + " ima jos " + std::to_string(m_numOfBullets);
}


const unsigned &BulletCard::numOfBullets() const
{
    return m_numOfBullets;
}

void BulletCard::setNumOfBullets(const unsigned &newNumOfBullets)
{
    m_numOfBullets = newNumOfBullets;
}

BulletCard::~BulletCard()
{

}
