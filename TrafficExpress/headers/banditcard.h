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

    // Constructors
    BanditCard(BanditType bandit);

    // Destructor
    virtual ~BanditCard();

    // Get methods
    BanditType bandit() const;

    // Set methods
    void setBandit(BanditType newBandit);

    // Other methods
    virtual std::string toString() const override;

private:
    BanditType m_bandit;
};

#endif // BANDITCARD_H
