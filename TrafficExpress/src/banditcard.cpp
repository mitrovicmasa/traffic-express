#include "../headers/banditcard.h"

BanditCard::BanditCard(BanditType bandit) : m_bandit(bandit)
{
}

std::string BanditCard::toString() const
{
    std::string banditName = "";
    switch (m_bandit) {
        case BanditType::PICKPOCKET:
            banditName = "Pickpocket";
        case BanditType::SEDUCTRESS:
            banditName = "Seductress";
        case BanditType::STUDENT:
            banditName = "Student";
        case BanditType::RETIREE:
            banditName = "Retiree";
        case BanditType::HOMELESS_MAN:
            banditName = "Homeless man";
        case BanditType::BUSINESS_WOMAN:
            banditName = "Business woman";
        default:
            break;
    }
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
