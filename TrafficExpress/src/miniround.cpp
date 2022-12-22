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

MiniRoundType MiniRound::getMiniRoundType()
{
    return m_type;
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
    switch(m_type){
        case MiniRoundType::FACE_UP:
            painter->drawPixmap(boundingRect(), QPixmap("://faceup.png"), QRectF(0,0,0,0));break;
        case MiniRoundType::HIDDEN:
            painter->drawPixmap(boundingRect(), QPixmap("://card_back.png"), QRectF(0,0,0,0));break;
        case MiniRoundType::DOUBLE_CARDS:
            painter->drawPixmap(boundingRect(), QPixmap("://double.png"), QRectF(0,0,0,0));break;
        case MiniRoundType::OPPOSITE_DIRECTION:
            painter->drawPixmap(boundingRect(), QPixmap("://opposite.png"), QRectF(0,0,0,0));break;
        default:break;
    }
}

int MiniRound::height() const
{
    return 60;
}

int MiniRound::width() const
{
    return 60;
}
