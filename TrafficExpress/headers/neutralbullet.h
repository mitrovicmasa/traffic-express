#ifndef NEUTRALBULLET_H
#define NEUTRALBULLET_H

#include <card.h>
#include <banditcard.h>

class NeutralBullet : public Card {

public:

    // Constructors
    NeutralBullet();
    NeutralBullet(BanditType id);
    Card *Copy() const override;

    // Destructor
    ~NeutralBullet();

    // Get methods
    const BanditType &id() const;

    // Set methods
    void setId(const BanditType &newId);

    // Other methods

    std::string toString() const override;

private:

    BanditType m_id;
};

#endif // NEUTRALBULLET_H
