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
    //Constructor
    DialogueBox(QString &text);
    DialogueBox(DialogueBox&db);

    //Get methods
    QString &text();

    //Set methods
    void setText(QString &newText);

    // GUI
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QString m_text;
};

#endif // DIALOGUEBOX_H
