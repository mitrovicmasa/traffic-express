#include "../headers/miniround.h"

#include <qpainter.h>

MiniRound::MiniRound()
    :QGraphicsObject(),m_type(MiniRoundType::FACE_UP)
{
setFlags(GraphicsItemFlag::ItemIsSelectable);
}

MiniRound::MiniRound(MiniRoundType t)
    :QGraphicsObject(),m_type(t)
{
setFlags(GraphicsItemFlag::ItemIsSelectable);
}

MiniRound::MiniRound(const MiniRound &other)
    :QGraphicsObject(),m_type(other.m_type)
{
setFlags(GraphicsItemFlag::ItemIsSelectable);
}

// Other methods
std::string MiniRound::toString()
{
    switch (m_type)
        {
        case MiniRoundType::HIDDEN:
            return "Hidden!";
        case MiniRoundType::DOUBLE_CARDS:
            return "Double cards!";
        case MiniRoundType::OPPOSITE_DIRECTION:
            return "Opposite direction!";
        case MiniRoundType::FACE_UP:
            return "Face up - default!";
        default:
            return "";
        }

}


// GUI
QRectF MiniRound::boundingRect() const
{
    return QRectF(0,0,width(),height());
}

void MiniRound::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor::fromRgb(12,50,100));
    switch(m_type){
        case MiniRoundType::HIDDEN:painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, "?");break;
    case MiniRoundType::DOUBLE_CARDS:painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, "DOUBLE");break;
    case MiniRoundType::OPPOSITE_DIRECTION:painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, "REVERSE");break;
    default:break;


    }
}

int MiniRound::height() const
{
    return 75;
}

int MiniRound::width() const
{
    return 50;
}
