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
    ActionCard(ActionType action, BanditType bandit);
    ~ActionCard();

    std::string toString() const override;

    ActionType action() const;
    void setAction(ActionType newAction);

private:
    ActionType m_action;
};

#endif // ACTIONCARD_H
