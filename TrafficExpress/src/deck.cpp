#include "deck.h"

#include <qgraphicsscene.h>

#include <algorithm>
#include <iostream>
#include <random>

// Constructors
Deck::Deck() : QGraphicsObject() {
  setFlags(GraphicsItemFlag::ItemIsSelectable);
}

Deck::Deck(CardColection cc) {
  auto cpy = CardColection(cc);
  for (Card *c : cpy) {
    this->push_back(c);
  }
  setFlags(GraphicsItemFlag::ItemIsSelectable);
}

// Get methods

CardColection &Deck::getCards() { return m_cards; }

// Other methods

void Deck::push_back(Card *card) {
  connect(card, &Card::clickedCard, this, &Deck::onClickedCard);
  m_cards.push_back(card);
  card->setParentItem(this);
  card->setPos(10, 20);
}

void Deck::push_front(Card *card) {
  connect(card, &Card::clickedCard, this, &Deck::onClickedCard);
  m_cards.insert(m_cards.begin(), card);
  card->setParentItem(this);
  card->setPos(5, 20);
}

void Deck::pop_back() {
  disconnect(m_cards.back(), &Card::clickedCard, this, &Deck::onClickedCard);
  m_cards.back()->setParentItem(nullptr);
  m_cards.pop_back();
}

void Deck::pop_front() {
  disconnect(m_cards.front(), &Card::clickedCard, this, &Deck::onClickedCard);
  m_cards.front()->setParentItem(nullptr);
  m_cards.erase(m_cards.begin());
}

Card *Deck::back() { return m_cards.back(); }

Card *Deck::front() { return m_cards.front(); }

int Deck::size() { return m_cards.size(); }

bool Deck::empty() { return m_cards.empty(); }

Card *Deck::operator[](int ind) { return m_cards[ind]; }

void Deck::shuffleDeck(int seed) {
  std::shuffle(m_cards.begin(), m_cards.end(),
               std::default_random_engine(seed));
}

void Deck::setAllCardsFaceDown() {
  for (Card *x : m_cards) x->setFaceUp(false);
}

void Deck::setAllCardsFaceUp() {
  for (Card *x : m_cards) x->setFaceUp(true);
}

// GUI
QRectF Deck::boundingRect() const { return QRectF(0, 0, 100, 120); }

void Deck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
  painter->drawPixmap(boundingRect(), QPixmap("://deck.png"),
                      QRectF(0, 0, 0, 0));
}

void Deck::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsObject::mousePressEvent(event);
}

void Deck::onClickedCard(Card *c) { emit clickedCardInDeck(c, this); }

// Serializable interface
QVariant Deck::toVariant() const {
  QVariantList list;
  for (auto *card : m_cards) {
    list.append(((ActionCard *)(card))->toVariant());
  }

  QVariantMap map;
  map.insert("cards", list);

  return map;
}

void Deck::fromVariant(const QVariant &variant) {
  QVariantList list = variant.toMap().value("cards").toList();
  for (auto &card : list) {
    auto *newCard = new ActionCard();
    newCard->fromVariant(card);
    this->push_back(newCard);
  }
}
