#include "../headers/neutralbullet.h"

// Constructors
NeutralBullet::NeutralBullet()
{

}

NeutralBullet::NeutralBullet(BanditType id) : m_id(id)
{

}

//Card *NeutralBullet::Copy() const
//{
//    return new NeutralBullet(*this);
//}

// Destructor
NeutralBullet::~NeutralBullet()
{

}

// Get methods
const BanditType &NeutralBullet::id() const
{
    return m_id;
}

// Set methods
void NeutralBullet::setId(const BanditType &newId)
{
    m_id = newId;
}

// Other methods

std::string NeutralBullet::toString() const
{
    return "Neutral bullet id: " + ::toString(m_id);
}

CardType NeutralBullet::Type() const
{
    return CardType::NEUTRAL_BULLET;
}

void NeutralBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->faceUp()) {
        painter->fillRect(boundingRect(),QColor::fromRgb(200,200,200));
        painter->drawText(boundingRect(), "?");
        return ;
    }

    painter->fillRect(boundingRect(),QColor::fromRgb(200,200,150));
    painter->drawText(boundingRect(), "NEUTRALL\nBULLET");
}
