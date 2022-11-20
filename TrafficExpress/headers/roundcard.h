#ifndef ROUNDCARDS_H
#define ROUNDCARDS_H

#include <iostream>
#include <string>
#include <vector>

#include "card.h"

enum class RoundCardType {
    
    THREE_TO_FOUR_PLAYERS,
    FIVE_TO_SIX_PLAYERS,
    TRAIN_STATION

}; 

enum class EventType {

    ANGRY_MARSHAL,
    SWIVEL_ARM,
    BRACKING,
    TAKE_IT_ALL,
    PASSENGERS_REBELLION,
    PICKPOCKETING,
    MARSHALS_REVENGE,
    HOSTAGE_TACKING_OF_THE_CONDUCTOR

};

enum class MiniRoundType {

    FACE_UP,
    HIDDEN,
    DOUBLE_CARDS,
    OPPOSITE_DIRECTION

};

std::string toStringRoundCardType(const RoundCardType &card);
std::string toStringEventType(const EventType &event);
std::string toStringMiniRoundType(const MiniRoundType &miniRound);

class RoundCard {

public:

    // Constructors
    RoundCard(RoundCardType type, EventType event, const std::vector<MiniRoundType> &miniRound);
    RoundCard(const RoundCard&);

    // Destructor
    ~RoundCard() = default;

    // Get methods
    RoundCardType type() const;
    const std::vector<MiniRoundType> &miniRound() const;
    EventType event() const;

    // Set methods
    void setType(RoundCardType &newType);
    void setEvent(EventType &newEvent);
    void setMiniRound(const std::vector<MiniRoundType> &newMiniRound);

    // Other methods

    void pushBackMiniRound(MiniRoundType type);

    std::string toString() const;

private:

    RoundCardType m_type;
    EventType m_event;
    std::vector<MiniRoundType> m_miniRound;

};



#endif //ROUNDCARDS_H
