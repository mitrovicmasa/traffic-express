#ifndef ROUNDCARDS_H
#define ROUNDCARDS_H

#include <iostream>
#include <string>
#include <vector>
#include <QGraphicsObject>
#include <qpainter.h>
#include<miniround.h>

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
    HOSTAGE_TACKING_OF_THE_CONDUCTOR,
    NONE

};

//enum class MiniRoundType {

//    FACE_UP,
//    HIDDEN,
//    DOUBLE_CARDS,
//    OPPOSITE_DIRECTION

//};

std::string toStringRoundCardType(const RoundCardType &card);
std::string toStringEventType(const EventType &event);
std::string toStringMiniRoundType(const MiniRoundType &miniRound);

class RoundCard:public QGraphicsObject,public std::vector<MiniRound*>
{
    Q_OBJECT
public:

    // Constructors
    RoundCard(RoundCardType type, EventType event, const std::vector<MiniRound*> &miniRound);
    RoundCard(RoundCardType type, EventType event, const std::vector<MiniRoundType> &miniRound);
    RoundCard(const RoundCard&);

    // Destructor
    ~RoundCard() = default;

    // Get methods
    RoundCardType typeOfRoundCard() const;

    EventType event() const;

    // Set methods
    void setType(RoundCardType &newType);
    void setEvent(EventType &newEvent);


    // Other methods

    void pushBackMiniRound(MiniRoundType type);
    void push_back(MiniRound*);

    std::string toString() const;

    // GUI
    int height()const;
    int width()const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    RoundCardType m_type;
    EventType m_event;
    //std::vector<MiniRoundType> m_miniRound;
};

#endif //ROUNDCARDS_H
