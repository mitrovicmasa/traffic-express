#include "../headers/banditcard.h"

BanditCard::BanditCard(BanditType bandit) : m_bandit(bandit)
{
}

std::string BanditCard::toString() const
{
    std::string banditName = ::toString(m_bandit);
    return banditName + "'s bandit card ";
}

void BanditCard::setBandit(BanditType newBandit)
{
    m_bandit = newBandit;
}

BanditType BanditCard::bandit() const
{
    return m_bandit;
}


BanditCard::~BanditCard()
{

}

std::string toString(BanditType bandit)
{
    switch (bandit) {
        case BanditType::PICKPOCKET:
            return "Pickpocket";
        case BanditType::SEDUCTRESS:
            return "Seductress";
        case BanditType::STUDENT:
            return "Student";
        case BanditType::RETIREE:
            return "Retiree";
        case BanditType::HOMELESS_MAN:
            return "Homeless man";
        case BanditType::BUSINESS_WOMAN:
            return "Business woman";
        default:
            return "";
    }
}
