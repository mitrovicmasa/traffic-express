#include "../headers/roundcard.h"

// Constructors
RoundCard::RoundCard(RoundCardType type, EventType event, const MiniRoundCollection &miniRounds)
    :QGraphicsObject(), m_type(type),
      m_event(event),m_miniRounds(miniRounds)

{
    for(int i=0;i<m_miniRounds.size();i++){
        m_miniRounds[i]->setParentItem(this);

        m_miniRounds[i]->setPos(i*(m_miniRounds[i]->width()+10)*0.8,height()-m_miniRounds[i]->height()-10);
    }

    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

RoundCard::RoundCard(RoundCardType type, EventType event, const std::vector<MiniRoundType> &miniRound)
    :QGraphicsObject(), m_type(type),
      m_event(event)
{
    for(auto x:miniRound){
        this->push_back(new MiniRound(x));
    }
    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

RoundCard::RoundCard(RoundCardType type, EventType event, const std::vector<MiniRound *> &miniRound)
{
    for(auto x:miniRound){
        this->push_back(x);
    }
    setFlags(GraphicsItemFlag::ItemIsSelectable);
}

//RoundCard::RoundCard(const RoundCard &other)
//    :QGraphicsObject(),std::vector<MiniRound*>(),
//    m_type(other.m_type),
//    m_event(other.m_event)
//{
//    for(MiniRound*mr:other)
//        this->push_back(new MiniRound(*mr));

//setFlags(GraphicsItemFlag::ItemIsSelectable);
//}

// Get methods
RoundCardType RoundCard::typeOfRoundCard() const
{
    return m_type;
}

MiniRoundCollection &RoundCard::getMiniRounds()
{
    return m_miniRounds;
}

int RoundCard::size() const
{
    return m_miniRounds.size();
}

MiniRound *RoundCard::operator[](int i)
{
    return m_miniRounds[i];
}

MiniRound *RoundCard::back()
{
    return m_miniRounds.back();
}

MiniRound *RoundCard::front()
{
    return m_miniRounds.front();
}

EventType RoundCard::event() const
{
    return m_event;
}



// Set methods
void RoundCard::setType(RoundCardType &newType)
{
    m_type = newType;
}

void RoundCard::setEvent(EventType &newEvent)
{
    m_event = newEvent;
}

void RoundCard::push_back(MiniRound*mr)
{

    m_miniRounds.push_back(mr);
    mr->setParentItem(this);
    mr->setPos((size()-1)*(mr->width()+10),height()-mr->height());
}



// Other methods


std::string toStringRoundCardType(const RoundCardType &card)
{
    switch (card) {
        case RoundCardType::THREE_TO_FOUR_PLAYERS:
            return "Three to four players";
        case RoundCardType::FIVE_TO_SIX_PLAYERS:
            return "Five to six players";
        case RoundCardType::TRAIN_STATION:
            return "Train station";
        default:
            return "";
    }

}

std::string toStringEventType(const EventType &event) 
{
    switch (event)
    {
    case EventType::ANGRY_MARSHAL:
        return "Angry Marshal";
    case EventType::SWIVEL_ARM:
        return "Swivel Arm";
    case EventType::BRACKING:
        return "Bracking";
    case EventType::TAKE_IT_ALL:
        return "Take it all!";
    case EventType::PASSENGERS_REBELLION:
        return "Passengers'Rebellion";
    case EventType::PICKPOCKETING:
        return "Pickpocketing";
    case EventType::MARSHALS_REVENGE:
        return "Marshal's Revenge";
    case EventType::HOSTAGE_TACKING_OF_THE_CONDUCTOR:
        return "Hostage-Taking of the Conductor";
    case EventType::NONE:
        return "No event";
    default:
        return "";
    }

}

std::string toStringMiniRoundType(const MiniRoundType &miniRound) 
{
    switch (miniRound)
    {
    case MiniRoundType::HIDDEN:
        return "Hidden!";
    case MiniRoundType::DOUBLE_CARDS:
        return "Double cards!";
    case MiniRoundType::OPPOSITE_DIRECTION:
        return "Opposite direction!";
    case MiniRoundType::FACE_UP:
        return "Face up - default!";
    default:
        return "";
    }

}

std::string RoundCard::toString() const
{
    std::string output = "";
    output += toStringEventType(m_event);
    output += "\n--------------------------\n";
    for (unsigned i = 0; i <size(); ++i) {
        output += m_miniRounds[i]->toString();
        output += "\n";
    }
    output += "--------------------------\n";

    return output;
}
// GUI

int RoundCard::height() const
{
    return 100;
}

int RoundCard::width() const
{
    return 300;
}

QRectF RoundCard::boundingRect() const
{
    return QRectF(0,0,width(),height());
}

void RoundCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor::fromRgb(200,200,170));
    painter->drawText(boundingRect(), "ROUND CARD:");
}
