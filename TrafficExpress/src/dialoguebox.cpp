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

DialogueBox::DialogueBox(DialogueBox &db):
    m_text(QString(db.text()))
{

}

//Getter
QString &DialogueBox::text()
{
    return m_text;
}

//Setter
void DialogueBox::setText( QString &newText)
{
    m_text = newText;
}


//GUI
QRectF DialogueBox::boundingRect() const
{
    return QRectF(0,0,590,70);
}

void DialogueBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawPixmap(boundingRect(), QPixmap("://message.png"), QRectF(0,0,0,0));
    painter->drawText(QPoint(25,35), m_text);
    painter->setFont( QFont("Magnolia Sky") );
    painter->setPen(QColor(255,255,255));

}

