#include "../headers/banditcard.h"

// Constructors
BanditCard::BanditCard(BanditType bandit) : m_bandit(bandit)
{

}

// Destructor
BanditCard::~BanditCard()
{

}

// Get methods
BanditType BanditCard::bandit() const
{
    return m_bandit;
}

// Set methods
void BanditCard::setBandit(BanditType newBandit)
{
    m_bandit = newBandit;
}

// Other methods
std::string BanditCard::toString() const
{
    std::string banditName = ::toString(m_bandit);
    return banditName;
}

std::string toString(BanditType bandit)
{
    switch (bandit) {
    case BanditType::PICKPOCKET:
        return "Green player";
        break;
    case BanditType::SEDUCTRESS:
        return "Yellow player";
        break;
    case BanditType::STUDENT:
        return "Blue player";
        break;
    case BanditType::RETIREE:
        return "Red player";
        break;
    case BanditType::HOMELESS_MAN:
        return "Orange player";
        break;
    case BanditType::BUSINESS_WOMAN:
        return "Purple player";
        break;
        default:
            return "";
    }
}
