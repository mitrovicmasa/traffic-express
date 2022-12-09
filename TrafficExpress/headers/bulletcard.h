#ifndef BULLETCARD_H
#define BULLETCARD_H

#include <banditcard.h>

class BulletCard : public BanditCard {

public:

    // Constructors
    BulletCard(BanditType bandit, unsigned numOfBullets);
//    Card *Copy() const override;

    // Destructor
    ~BulletCard();

    // Get methods
    const unsigned &numOfBullets() const;

    // Set methods
    void setNumOfBullets(const unsigned &newNumOfBullets);

    // Other methods
    std::string toString() const override;
    CardType Type() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

    unsigned m_numOfBullets;
};

#endif // BULLETCARD_H
