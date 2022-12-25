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

//    //m_currentText = new QGraphicsTextItem();
//    m_currentText->setPlainText(text);
//    m_currentText->setFont(QFont("Adventure", 11));

//    //setPixmap(QPixmap("://messageBox.png"));
//    m_currentText->setTextWidth(280);
//    m_currentText->setPos(5, 15); //from top left of the pixmap

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

    painter->drawPixmap(boundingRect(), QPixmap("://messageBox.png"), QRectF(0,0,0,0));
    painter->drawText(QPoint(60,130), "MessageBox!");
    painter->setFont( QFont("Arial") );
    painter->setPen(QColor(255,5,255));

}
