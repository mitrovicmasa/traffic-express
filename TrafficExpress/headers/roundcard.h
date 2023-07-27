#ifndef ROUNDCARDS_H
#define ROUNDCARDS_H

#include <miniround.h>
#include <miniroundcollection.h>
#include <qpainter.h>
#include <serializable.h>

#include <QGraphicsObject>
#include <iostream>
#include <string>
#include <vector>

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

std::string toStringRoundCardType(const RoundCardType &card);
std::string toStringEventType(const EventType &event);
std::string toStringMiniRoundType(const MiniRoundType &miniRound);

class RoundCard : public QGraphicsObject, public Serializable {
  Q_OBJECT

 public:
  // Constructors
  RoundCard();
  RoundCard(RoundCardType type, EventType event,
            const std::vector<MiniRoundType> &miniRound);
  RoundCard(RoundCardType type, EventType event,
            const MiniRoundCollection &miniRound);

  // Destructor
  ~RoundCard() = default;

  // Get methods
  RoundCardType typeOfRoundCard() const;
  MiniRoundCollection &getMiniRounds();
  EventType event() const;

  // Set methods
  void setType(RoundCardType &newType);
  void setEvent(EventType &newEvent);

  // Other methods
  void push_back(MiniRound *);
  MiniRound *back();
  MiniRound *front();
  int size() const;
  MiniRound *operator[](int);
  std::string toString() const;

  // GUI
  int height() const;
  int width() const;
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

  // Serializable interface
  QVariant toVariant() const;
  void fromVariant(const QVariant &variant);

 private:
  RoundCardType m_type;
  EventType m_event;
  MiniRoundCollection m_miniRounds;
};

#endif  // ROUNDCARDS_H
