#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <QGraphicsPixmapItem>
#include <QGraphicsObject>
#include <string.h>
#include <QPixmap>
#include <QString>




class DialogueBox :  public QGraphicsObject
{
    Q_OBJECT

public:
    DialogueBox(QString &text);

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString m_text;

};

#endif // DIALOGUEBOX_H
