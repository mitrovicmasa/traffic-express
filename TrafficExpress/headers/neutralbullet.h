#ifndef NEUTRALBULLET_H
#define NEUTRALBULLET_H

#include <card.h>

class NeutralBullet : public Card {

public:
    NeutralBullet(const unsigned id);
    ~NeutralBullet();

    std::string toString() const override;

    const unsigned &id() const;
    void setId(const unsigned &newId);

private:
    unsigned m_id;
};

#endif // NEUTRALBULLET_H
