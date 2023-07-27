#include "../headers/treasure.h"

#include <QPainter>

// Constructors
Treasure::Treasure()
    : QGraphicsObject(), m_type(TreasureType::MONEYBAG), m_value(250) {
  setFlags(GraphicsItemFlag::ItemIsSelectable);
}

Treasure::Treasure(int value, TreasureType type)
    : QGraphicsObject(), m_type(type), m_value(value) {
  setFlags(GraphicsItemFlag::ItemIsSelectable);
}

Treasure::Treasure(TreasureType type) : QGraphicsObject(), m_type(type) {
  setFlags(GraphicsItemFlag::ItemIsSelectable);
}

Treasure::Treasure(const Treasure &t)
    : QGraphicsObject(), m_type(t.m_type), m_value(t.m_value) {
  setFlags(GraphicsItemFlag::ItemIsSelectable);
}

// Get methods
TreasureType Treasure::getType() { return m_type; }

int Treasure::getValue() { return m_value; }

// Other methods

bool Treasure::operator==(const Treasure &t) {
  return m_type == t.m_type && m_value == t.m_value;
}

bool Treasure::operator!=(const Treasure &t) {
  return !(m_type == t.m_type && m_value == t.m_value);
}

std::string Treasure::toString() {
  switch (m_type) {
    case TreasureType::MONEYBAG:
      return "MONEYBAG:" + std::to_string(m_value);
    case TreasureType::DIAMOND:
      return "DIAMOND:" + std::to_string(m_value);
      ;
    case TreasureType::SUITCASE:
      return "SUITCASE:" + std::to_string(m_value);
      ;
    default:
      return "UNKNOWN TREASURE TYPE";
  }
}

// GUI

int Treasure::height() const { return 25; }

int Treasure::width() const { return 25; }

QRectF Treasure::boundingRect() const {
  return QRectF(0, 0, width(), height());
}

void Treasure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  QString type;
  switch (this->getType()) {
    case TreasureType::MONEYBAG:
      type = "moneybag";
      break;
    case TreasureType::DIAMOND:
      type = "diamond";
      break;
    case TreasureType::SUITCASE:
      type = "suitcase";
      break;
    default:
      return;
  }

  QString path = "://" + type + ".png";
  painter->drawPixmap(boundingRect(), QPixmap(path), QRectF(0, 0, 0, 0));
}

void Treasure::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsObject::mousePressEvent(event);
  emit clicked();
  emit clickedTreasure(this);
}

// Serializable interface
QVariant Treasure::toVariant() const {
  QVariantMap map;
  map.insert("type", (int)m_type);
  map.insert("value", m_value);
  return map;
}

void Treasure::fromVariant(const QVariant &variant) {
  QVariantMap map = variant.toMap();
  m_type = static_cast<TreasureType>(map.value("type").toInt());
  m_value = map.value("value").toInt();
}
