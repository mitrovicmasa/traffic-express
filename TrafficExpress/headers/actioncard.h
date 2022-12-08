#ifndef ACTIONCARD_H
#define ACTIONCARD_H

#include <banditcard.h>

enum class ActionType {
    MOVE,
    FLOOR_CHANGE,
    MARSHAL,
    FIRE,
    PUNCH,
    ROBBERY,
    TAKETREASURE
};

class ActionCard : public BanditCard {

public:

    // Constructors
    ActionCard(ActionType action, BanditType bandit);
    //Card *Copy() const override;

    // Destructor
    ~ActionCard();

    // Get methods
    ActionType action() const;

    // Set methods
    void setAction(ActionType newAction);

    // Other methods
    std::string toString() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ActionType m_action;
};

#endif // ACTIONCARD_H
