#include "../headers/actioncard.h"
#include <qpainter.h>

// Constructors
ActionCard::ActionCard(ActionType action, BanditType bandit) : m_action(action),
    BanditCard(bandit)
{}

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
            actionName = "floor_change";break;
        case ActionType::FIRE:
            actionName = "fire";break;
        case ActionType::PUNCH:
            actionName = "punch";break;
        case ActionType::MARSHAL:
            actionName = "marshal";break;
        case ActionType::ROBBERY:
            actionName = "robbery";break;
        case ActionType::TAKETREASURE:
            actionName="take treasure";break;
        default:
            break;
    }
    return BanditCard::toString() + " doing action: " + actionName;
}

CardType ActionCard::Type() const
{
    return CardType::ACTION_CARD;
}

// GUI
void ActionCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->faceUp()) {
        painter->drawPixmap(boundingRect(), QPixmap("://card_back.png"), QRectF(0,0,0,0));
        return ;
    }

    QString color;
    switch (this->bandit()) {
        case BanditType::PICKPOCKET:
            color = "green";
            break;
        case BanditType::SEDUCTRESS:
            color = "yellow";
            break;
        case BanditType::STUDENT:
            color = "blue";
            break;
        case BanditType::RETIREE:
            color = "red";
            break;
        case BanditType::HOMELESS_MAN:
            color = "orange";
            break;
        case BanditType::BUSINESS_WOMAN:
            color = "purple";
            break;
        default:
            return;
    }

    QString action;
    switch (this->m_action) {
        case ActionType::FIRE:
            action = "fire";
            break;
        case ActionType::FLOOR_CHANGE:
            action = "floor_change";
            break;
        case ActionType::MARSHAL:
            action = "marshal";
            break;
        case ActionType::MOVE:
            action = "move";
            break;
        case ActionType::PUNCH:
            action = "punch";
            break;
        case ActionType::ROBBERY:
            action = "robbery";
            break;
        case ActionType::TAKETREASURE:
            action="robbery";break;
        default:
            return;
    }
    QString path = "://" + action + "_" + color + ".png";
    painter->drawPixmap(boundingRect(), QPixmap(path), QRectF(0,0,0,0));
}

Card *ActionCard::Copy() const
{
     auto tmp=new ActionCard(m_action,bandit());
     tmp->setFaceUp(this->faceUp());
     return tmp;
}

