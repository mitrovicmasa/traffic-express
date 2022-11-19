#ifndef BULLETCARD_H
#define BULLETCARD_H

#include <banditcard.h>

class BulletCard : public BanditCard {

public:
    BulletCard(BanditType bandit, unsigned numOfBullets);
    ~BulletCard();

    std::string toString() const override;

    const unsigned &numOfBullets() const;
    void setNumOfBullets(const unsigned &newNumOfBullets);

private:
    unsigned m_numOfBullets;
};

#endif // BULLETCARD_H
