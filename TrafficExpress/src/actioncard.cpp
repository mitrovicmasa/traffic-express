#include "../headers/actioncard.h"

// Constructors
ActionCard::ActionCard(ActionType action, BanditType bandit) : BanditCard(bandit),
    m_action(action)
{}

Card *ActionCard::Copy() const
{
    return new ActionCard(*this);
}


// Destructor
ActionCard::~ActionCard()
{

}

// Get methods
ActionType ActionCard::action() const
{
    return m_action;
}

// Set methods
void ActionCard::setAction(ActionType newAction)
{
    m_action = newAction;
}

// Other methods
std::string ActionCard::toString() const
{
    std::string actionName = "";
    switch (m_action) {
        case ActionType::MOVE:
            actionName = "move";break;
        case ActionType::FLOOR_CHANGE:
            actionName = "floor change";break;
        case ActionType::FIRE:
            actionName = "fire";break;
        case ActionType::PUNCH:
            actionName = "punch";break;
        case ActionType::MARSHAL:
            actionName = "move marshal";break;
        case ActionType::ROBBERY:
            actionName = "robbery";break;
        case ActionType::TAKETREASURE:
            actionName="take treasure";break;
        default:
            break;
    }
    return BanditCard::toString() + "doing action: " + actionName;
}
