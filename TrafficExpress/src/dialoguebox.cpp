#include "../headers/dialoguebox.h"

#include <QFont>
#include <QPainter>
#include <QGraphicsScene>
#include <iostream>

//Constructors
DialogueBox::DialogueBox(QString &text)
    :QGraphicsObject()
{
    m_text = text;

}


//GUI
QRectF DialogueBox::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void DialogueBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawPixmap(boundingRect(), QPixmap("://blue_db.png"), QRectF(0,0,0,0));
    painter->drawText(QPoint(50,90), "MessageBox");
    painter->setFont( QFont("Magnolia Sky") );
    painter->setPen(QColor(255,255,255));
    //painter->setPen(Qt::white);

}
