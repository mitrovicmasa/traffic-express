#ifndef DECK_H
#define DECK_H

#include <cardcolection.h>
#include <serializable.h>

#include <vector>

#include "card.h"

class Deck : public QGraphicsObject, public Serializable {
  Q_OBJECT
 public:
  // Constructors
  Deck();
  Deck(CardColection cc);

  // Get methods
  CardColection &getCards();

  // Other methods
  void push_back(Card *);
  void push_front(Card *);
  void pop_back();
  void pop_front();
  Card *back();
  Card *front();
  Card *operator[](int ind);
  int size();
  bool empty();

  void shuffleDeck(int seed);
  void setAllCardsFaceDown();
  void setAllCardsFaceUp();

  // GUI
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

  // Serializable interface
  QVariant toVariant() const;
  void fromVariant(const QVariant &variant);

 signals:
  void clickedCardInDeck(Card *c, Deck *d);

 public slots:
  void onClickedCard(Card *c);

 private:
  CardColection m_cards;
};

#endif  // DECK_H
