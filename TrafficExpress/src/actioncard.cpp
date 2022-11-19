#include "../headers/actioncard.h"

ActionCard::ActionCard(ActionType action, BanditType bandit) : BanditCard(bandit),
    m_action(action)
{}

//najgluplji toString ikad vidjen
std::string ActionCard::toString() const
{
    std::string actionName = "";
    switch (m_action) {
        case ActionType::MOVE:
            actionName = "move";
        case ActionType::FLOOR_CHANGE:
            actionName = "floor change";
        case ActionType::FIRE:
            actionName = "fire";
        case ActionType::PUNCH:
            actionName = "punch";
        case ActionType::MARSHAL:
            actionName = "move marshal";
        case ActionType::ROBBERY:
            actionName = "robbery";
        default:
            break;
    }
    return BanditCard::toString() + "doing action: " + actionName;
}


ActionType ActionCard::action() const
{
    return m_action;
}

void ActionCard::setAction(ActionType newAction)
{
    m_action = newAction;
}

ActionCard::~ActionCard()
{

}
