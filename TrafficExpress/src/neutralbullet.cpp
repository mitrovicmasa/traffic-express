#include "../headers/neutralbullet.h"

// Constructors
NeutralBullet::NeutralBullet() = default;

NeutralBullet::NeutralBullet(BanditType id) : m_id(id) {}

Card *NeutralBullet::Copy() const { return new NeutralBullet(id()); }

// Destructor
NeutralBullet::~NeutralBullet() = default;

// Get methods
const BanditType &NeutralBullet::id() const { return m_id; }

// Set methods
void NeutralBullet::setId(const BanditType &newId) { m_id = newId; }

// Other methods
std::string NeutralBullet::toString() const {
  return "Neutral bullet id: " + ::toString(m_id);
}

CardType NeutralBullet::Type() const { return CardType::NEUTRAL_BULLET; }

// GUI
void NeutralBullet::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
  if (!this->faceUp()) {
    painter->drawPixmap(boundingRect(), QPixmap("://card_back.png"),
                        QRectF(0, 0, 0, 0));
    return;
  }

  painter->drawPixmap(boundingRect(), QPixmap("://neutralbullet.png"),
                      QRectF(0, 0, 0, 0));
}
