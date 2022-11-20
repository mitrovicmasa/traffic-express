#ifndef NEUTRALBULLET_H
#define NEUTRALBULLET_H

#include <card.h>

class NeutralBullet : public Card {

public:

    // Constructors
    NeutralBullet(const unsigned id);
    Card *Copy() const override;

    // Destructor
    ~NeutralBullet();

    // Get methods
    const unsigned &id() const;

    // Set methods
    void setId(const unsigned &newId);

    // Other methods

    std::string toString() const override;

private:

    unsigned m_id;
};

#endif // NEUTRALBULLET_H
