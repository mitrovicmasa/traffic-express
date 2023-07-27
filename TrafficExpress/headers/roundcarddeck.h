#ifndef ROUNDCARDDECK_H
#define ROUNDCARDDECK_H

#include <roundcardcollection.h>

#include <QGraphicsObject>
#include <QObject>

class RoundCardDeck : public QGraphicsObject, public Serializable {
  Q_OBJECT

 public:
  // Constructors
  RoundCardDeck();
  RoundCardDeck(std::vector<RoundCard *>);
  RoundCardDeck(const RoundCardCollection &);

  // Get methods
  RoundCardCollection &getRoundCards();

  // Other methods
  void push_front(RoundCard *);
  void pop_front();
  RoundCard *operator[](int);
  RoundCard *back();
  RoundCard *front();
  int size();

  // GUI
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  int width() const;
  int height() const;

  // Serializable interface
  QVariant toVariant() const;
  void fromVariant(const QVariant &variant);

 private:
  RoundCardCollection m_rounds;
};

#endif  // ROUNDCARDDECK_H
