#ifndef HAND_H
#define HAND_H

#include <cardcolection.h>

#include <vector>

#include "card.h"

class Hand : public QGraphicsObject, public Serializable {
  Q_OBJECT
 public:
  // Constructors
  Hand();
  Hand(CardColection& cc);

  // Get methods
  CardColection& getCards();

  // Other methods
  void push_back(Card*);
  void push_front(Card*);
  void pop_back();
  void pop_front();
  Card* back();
  Card* front();
  bool empty();
  int size();
  Card* operator[](int ind);

  Card* takeCard(int indexofCard);
  void repositionCards();
  int getCardIndex(Card*);

  // GUI
  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget);
  void mousePressEvent(QGraphicsSceneMouseEvent* event);

  // Serializable interface
  QVariant toVariant() const;
  void fromVariant(const QVariant& variant);

 signals:
  void clickedCardInHand(Card* c, Hand* h);

 public slots:
  void onClickedCard(Card* c);

 private:
  CardColection m_cards;
};

#endif  // HAND_H
