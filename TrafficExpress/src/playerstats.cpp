#include "../headers/playerstats.h"

#include <QPainter>

// Constructors
PlayerStats::PlayerStats()
    :QGraphicsObject(), m_player(new Player(BanditType::BUSINESS_WOMAN))
{

    // Treasure in table
    int i=0;
    for(Treasure *t :m_player->treasure()){
        t->setParentItem(this);
        t->setPos(i*30+80, 20);
        i++;
        connect(t, &Treasure::Moved, this, &PlayerStats::test);
       }


}

PlayerStats::PlayerStats(Player *t)
    :QGraphicsObject(), m_player(t)
{
    int i=0;
    for(Treasure *t :m_player->treasure()){
        t->setParentItem(this);
        t->setPos(i*30+80, 20);
        i++;
       }


}

// Other methods
QRectF PlayerStats::boundingRect() const
{
    return QRectF(0,0,300,70);
}

void PlayerStats::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(boundingRect(),QColor(210,222,230));

    int num;
    for (BulletCard *b :m_player->bulletDeck()){
        num = b->numOfBullets();
        //painter->drawText(boundingRect(), "Player " + QString::number(i) + "- Number of bullets: " + QString::number(num));
    }
    painter->drawText(boundingRect(), "Player - Number of bullets: " + QString::number(num));
}

// Test moveEevent and pressEvent
void PlayerStats::test()
{
    std::cout<<"Moved treasure!"<<std::endl;
}
