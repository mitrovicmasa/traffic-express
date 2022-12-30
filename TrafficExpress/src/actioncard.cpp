#include "../headers/actioncard.h"
#include <qpainter.h>

// Constructors
ActionCard::ActionCard():
    BanditCard(BanditType::BUSINESS_WOMAN)
{

}

ActionCard::ActionCard(ActionType action, BanditType bandit):
    m_action(action),
    BanditCard(bandit)
{

}

Card *ActionCard::Copy() const
{
     auto tmp = new ActionCard(m_action,bandit());
     tmp->setFaceUp(this->faceUp());
     return tmp;
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
            actionName = "sheriff move";break;
        case ActionType::ROBBERY:
            actionName = "robbery";break;
        default:
            break;
    }
    return BanditCard::toString() + " played action card " + actionName + ". ";
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
        default:
            return;
    }
    QString path = "://" + action + "_" + color + ".png";
    painter->drawPixmap(boundingRect(), QPixmap(path), QRectF(0,0,0,0));
}

// Serializable interface
QVariant ActionCard::toVariant() const
{
    QVariantMap map;
    map.insert("action", (int)m_action);
    map.insert("bandit", (int)this->bandit());
    map.insert("faceUp", this->faceUp());
    return map;
}

void ActionCard::fromVariant(const QVariant &variant)
{
    QVariantMap map=variant.toMap();

    m_action = static_cast<ActionType>(map.value("action").toInt());
    this->setBandit(static_cast<BanditType>(map.value("bandit").toInt()));
    this->setFaceUp(map.value("faceUp").toBool());
}

