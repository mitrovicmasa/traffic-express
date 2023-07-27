#ifndef PLAYER_H
#define PLAYER_H

#include <actioncard.h>
#include <banditcard.h>
#include <bulletcard.h>
#include <card.h>
#include <deck.h>
#include <dialoguebox.h>
#include <hand.h>
#include <treasure.h>
#include <treasurechest.h>

#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

class Player : public QGraphicsObject, public Serializable {
  Q_OBJECT

 public:
  // Constructors
  Player();
  Player(BanditType id);
  Player(bool isItMyMove, BanditType id, Hand *h, Deck *d, Deck *bcd, int pos,
         bool roof, TreasureChest tc);

  // Destructor
  ~Player() = default;

  // Operator overloading
  Player &operator=(const Player &player);

  // Get methods
  BanditType id() const;
  Hand *hand();
  Deck *deck();
  Deck *bullet_deck();
  int positionInTrain() const;
  bool roof() const;
  TreasureChest &treasure();
  bool isItMyMove() const;

  // Set methods
  void setPositionInTrain(int newPositionInTrain);
  void setRoof(bool newRoof);
  void setMyMove(bool);

  // Other methods
  bool isBulletDeckEmpty() const;
  int countAmountOfTreasure() const;
  void returnCardsToDeck();
  void shuffleDeck(int);
  void drawCards(unsigned n);
  std::string toString() const;

  // GUI
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  int width() const;
  int height() const;

  QVariant toVariant() const;
  void fromVariant(const QVariant &variant);

 signals:
  void clicked();
  void clickedCardInHandInPlayer(Card *c, Hand *h, Player *p);
  void clickedCardInDeckInPlayer(Card *c, Deck *d, Player *p);
  void clickedPlayer(Player *);

 public slots:
  void onClickedCardInHand(Card *c, Hand *h);
  void onClickedCardInDeck(Card *c, Deck *d);

 private:
  bool m_isItMyMove;
  BanditType m_id;
  Hand *m_hand;
  Deck *m_deck;
  Deck *m_bulletDeck;
  int m_positionInTrain;
  bool m_roof;
  TreasureChest m_treasure;

 public:
};
#endif  // PLAYER_H
