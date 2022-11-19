#ifndef BANDITCARD_H
#define BANDITCARD_H

#include <card.h>

enum class BanditType {
    PICKPOCKET,
    SEDUCTRESS,
    STUDENT,
    RETIREE,
    HOMELESS_MAN,
    BUSINESS_WOMAN
};

std::string toString(BanditType bandit);

class BanditCard : public Card {

public:
    BanditCard(BanditType bandit);
    virtual ~BanditCard();

    virtual std::string toString() const override;

    void setBandit(BanditType newBandit);
    BanditType bandit() const;

private:
    BanditType m_bandit;
};

#endif // BANDITCARD_H
