#include "../headers/treasure.h"

#include <QPainter>

// Constructors
Treasure::Treasure()
    :QGraphicsObject(),m_type(TreasureType::MONEYBAG),m_value(250)
{
    setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
}

Treasure::Treasure(int value, TreasureType type)
    :QGraphicsObject(),m_type(type),m_value(value)
{

}

Treasure::Treasure(TreasureType type)
    :QGraphicsObject(),m_type(type)
{

}

Treasure::Treasure(const Treasure &t)
    :QGraphicsObject(),m_type(t.m_type),m_value(t.m_value)
{

}

// Get methods
TreasureType Treasure::getType()
{
    return m_type;
}

int Treasure::getValue()
{
    return m_value;
}

int Treasure::visina() const
{
    return 25;
}

int Treasure::sirina() const
{
    return 25;
}

// Other methods


bool Treasure::operator==(const Treasure &t)
{
    return m_type==t.m_type && m_value==t.m_value;
}

bool Treasure::operator!=(const Treasure &t)
{
    return !(m_type==t.m_type && m_value==t.m_value);
}

std::string Treasure::toString()
{
    switch(m_type){
                case TreasureType::MONEYBAG:return "MONEYBAG:"+std::to_string(m_value);
                case TreasureType::DIAMOND:return "DIAMOND:"+std::to_string(m_value);;
                case TreasureType::SUITCASE:return "SUITCASE:"+std::to_string(m_value);;
                default:return "UNKNOWN TREASURE TYPE";

    }
}


QRectF Treasure::boundingRect() const
{
    return QRectF(0,0,25,25);
}

void Treasure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    Q_UNUSED(option)
//    Q_UNUSED(widget)

    QString type;
    switch(this->getType()){
        case TreasureType::MONEYBAG:
            type = "moneybag";
            break;
        case TreasureType::DIAMOND:
            type = "diamond";
            break;
        case TreasureType::SUITCASE:
            type = "suitcase";
            break;
        default:return ;
    }

    QString path = "://" + type + ".png";
    painter->drawPixmap(boundingRect(), QPixmap(path), QRectF(0,0,0,0));

}

void Treasure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    emit Moved();

}

void Treasure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit Moved();
}





