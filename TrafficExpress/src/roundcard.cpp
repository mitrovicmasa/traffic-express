#include "../headers/roundcard.h"

// Constructors
RoundCard::RoundCard(RoundCardType type, EventType event, const std::vector<MiniRoundType> &miniRound)
    : m_type(type), 
      m_event(event),
      m_miniRound(miniRound)
{}

RoundCard::RoundCard(const RoundCard &r)
    :
    m_type(r.m_type), 
    m_event(r.m_event),
    m_miniRound(r.m_miniRound)
{}

// Get methods
RoundCardType RoundCard::type() const
{
    return m_type;
}

EventType RoundCard::event() const
{
    return m_event;
}

const std::vector<MiniRoundType> &RoundCard::miniRound() const
{
    return m_miniRound;
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

void RoundCard::setMiniRound(const std::vector<MiniRoundType> &newMiniRound)
{
    m_miniRound = newMiniRound;
}

// Other methods
void RoundCard::pushBackMiniRound(MiniRoundType type)
{
    m_miniRound.push_back(type);

}

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
    for (unsigned i = 0; i < m_miniRound.size(); ++i) {
        output += toStringMiniRoundType(m_miniRound[i]);
        output += "\n";
    }
    output += "--------------------------\n";

    return output;
}
