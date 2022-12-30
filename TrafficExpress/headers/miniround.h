#ifndef MINIROUND_H
#define MINIROUND_H

#include <qgraphicsitem.h>

enum class MiniRoundType {
    FACE_UP,
    HIDDEN,
    DOUBLE_CARDS,
    OPPOSITE_DIRECTION
};

class MiniRound:public QGraphicsObject
{
    Q_OBJECT

public:
    // Constructors
    MiniRound();
    MiniRound(MiniRoundType);
    MiniRound(const MiniRound&);

    // Get methods
    MiniRoundType getMiniRoundType();

    // Other methods
    std::string toString();

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int height() const;
    int width() const;

private:
    MiniRoundType m_type;
};

#endif // MINIROUND_H
