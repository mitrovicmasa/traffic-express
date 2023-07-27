#include "../headers/train.h"

#include <qgraphicsscene.h>
#include <qpainter.h>

Train::Train(WagonArray &wa) : QGraphicsObject() {
  int i = 0;
  bool isLocomotive = false;
  for (Wagon *w : wa) {
    if (i == wa.size() - 1) {
      isLocomotive = true;
    }
    i++;
    this->push_back(new Wagon(w->getContentUp(), w->getContentDown(),
                              w->getPlayersUp(), w->getPlayersDown(),
                              isLocomotive));
  }
}

Train::Train() = default;

Train::Train(std::vector<Wagon *> wagons) : QGraphicsObject() {
  int i = 0;
  for (Wagon *w : wagons) {
    this->push_back(w);
    if (i == wagons.size() - 1) {
      w->setIsLocomotive(true);
    }
    i++;
  }
}

// Get methods
WagonArray &Train::getWagons() { return m_wagons; }

int Train::getWagonIndex(Wagon *w) {
  int i = 0;
  for (auto &m_wagon : m_wagons) {
    if (m_wagon == w) {
      return i;
    }
    i++;
  }
  return -1;
}

// Other methods
void Train::push_back(Wagon *w) {
  connect(w, &Wagon::clickedPlayerInWagon, this,
          &Train::onClickedPlayerInWagon);
  connect(w, &Wagon::clickedTreasureInWagon, this,
          &Train::onClickedTreasureInWagon);
  connect(w, &Wagon::clickedWagon, this, &Train::onClickedWagon);
  m_wagons.push_back(w);
  w->setParentItem(this);
  w->setPos((m_wagons.size() - 1) * 180, 10);
}

void Train::push_front(Wagon *w) {
  connect(w, &Wagon::clickedPlayerInWagon, this,
          &Train::onClickedPlayerInWagon);
  connect(w, &Wagon::clickedTreasureInWagon, this,
          &Train::onClickedTreasureInWagon);
  connect(w, &Wagon::clickedWagon, this, &Train::onClickedWagon);
  m_wagons.insert(m_wagons.begin(), w);
  w->setParentItem(this);
  w->setPos((m_wagons.size() - 1) * 180, 10);
  if (this->getWagonIndex(w) == 0) {
    w->setIsLocomotive(true);
  }
}

void Train::pop_back() {
  disconnect(m_wagons.back(), &Wagon::clickedPlayerInWagon, this,
             &Train::onClickedPlayerInWagon);
  disconnect(m_wagons.back(), &Wagon::clickedTreasureInWagon, this,
             &Train::onClickedTreasureInWagon);
  disconnect(m_wagons.back(), &Wagon::clickedWagon, this,
             &Train::onClickedWagon);
  m_wagons.back()->setParentItem(nullptr);
  m_wagons.pop_back();
}

void Train::pop_front() {
  disconnect(m_wagons.front(), &Wagon::clickedPlayerInWagon, this,
             &Train::onClickedPlayerInWagon);
  disconnect(m_wagons.front(), &Wagon::clickedTreasureInWagon, this,
             &Train::onClickedTreasureInWagon);
  disconnect(m_wagons.front(), &Wagon::clickedWagon, this,
             &Train::onClickedWagon);
  m_wagons.front()->setParentItem(nullptr);
  m_wagons.erase(m_wagons.begin());
}

Wagon *Train::back() { return m_wagons.back(); }

Wagon *Train::front() { return m_wagons.front(); }

int Train::size() { return m_wagons.size(); }

bool Train::empty() { return m_wagons.empty(); }

Wagon *Train::operator[](int i) { return m_wagons[i]; }

// GUI
QRectF Train::boundingRect() const {
  return QRectF(0, 0, (m_wagons.size() + 1) * 200, 200);
}

void Train::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  painter->drawPixmap(boundingRect(), QPixmap("://landscape.png"),
                      QRectF(0, 0, 0, 0));
}

void Train::onClickedTreasureInWagon(Treasure *t, Wagon *w) {
  emit clickedTreasureInWagonInTrain(t, w, this);
}

void Train::onClickedPlayerInWagon(Player *p, Wagon *w) {
  emit clickedPlayerInWagonInTrain(p, w, this);
}

void Train::onClickedWagon(Wagon *w) { emit clickedWagonInTrain(w, this); }

// Serializable interface
QVariant Train::toVariant() const {
  QVariantMap map;

  QVariantList wagons;
  for (auto *wagon : m_wagons) wagons.append(wagon->toVariant());

  map.insert("wagons", wagons);
  return map;
}

void Train::fromVariant(const QVariant &variant) {
  QVariantList list = variant.toMap().value("wagons").toList();

  for (auto &wagon : list) {
    auto *newWagon = new Wagon();
    newWagon->fromVariant(wagon);
    newWagon->setIsLocomotive(false);
    push_back(newWagon);
  }
  this->back()->setIsLocomotive(true);
  this->back()->addSheriffDown(new Sheriff());
}
