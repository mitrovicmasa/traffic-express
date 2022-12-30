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
    ~NeutralBullet() override;

    // Get methods
    const BanditType &id() const;

    // Set methods
    void setId(const BanditType &newId);

    // Other methods
    std::string toString() const override;
    CardType Type() const override;

    // GUI
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    BanditType m_id;

};

#endif // NEUTRALBULLET_H
