#include "../headers/actioncard.h"
#include <qpainter.h>

// Constructors
ActionCard::ActionCard(ActionType action, BanditType bandit) : m_action(action),
    BanditCard(bandit)
{}

//Card *ActionCard::Copy() const
//{
//    return new ActionCard(*this);
//}


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

void ActionCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (this->bandit()) {
        case BanditType::PICKPOCKET:
            painter->fillRect(boundingRect(),QColor::fromRgb(80,110,240));
            break;
        case BanditType::SEDUCTRESS:
            painter->fillRect(boundingRect(),QColor::fromRgb(240,80,120));
            break;
        case BanditType::STUDENT:
            painter->fillRect(boundingRect(),QColor::fromRgb(220,80,240));
            break;
        case BanditType::RETIREE:
            painter->fillRect(boundingRect(),QColor::fromRgb(50,150,100));
            break;
        case BanditType::HOMELESS_MAN:
            painter->fillRect(boundingRect(),QColor::fromRgb(240,240,80));
            break;
        case BanditType::BUSINESS_WOMAN:
            painter->fillRect(boundingRect(),QColor::fromRgb(240,150,80));
            break;
        default:
            return;
    }
}

