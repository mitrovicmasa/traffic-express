#include "../headers/table.h"


#include <QPainter>
#include <QGraphicsScene>


Table::Table()
   :QGraphicsObject(){

}

void Table::addTableToScene(QGraphicsScene *sc)
{
    sc->addItem(this);
    (this)->setPos(800,800);
}


void Table::push_back(PlayerStats *p)
{
    m_playerStats.push_back(p);
    p->setParentItem(this);
    p->setPos(0,(this->size()-1)*70+1);
    connect(p,&PlayerStats::clickedTreasueInPlayeStats,this,&Table::onClickedTreasureInPlayerStats);
}

int Table::size()
{
    return m_playerStats.size();
}

PlayerStats *Table::operator[](int i)
{
    return m_playerStats[i];
}

PlayerStatsCollection &Table::getPlayerStats()
{
    return m_playerStats;
}


// GUI

int Table::height() const
{
    return 450;
}

int Table::width() const
{
    return 300;
}

QRectF Table::boundingRect() const
{
    return QRectF(0,0,width(),height());
}

void Table::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(boundingRect(),QColor::fromRgb(204,229,255));
}

void Table::onClickedTreasureInPlayerStats(Treasure *t, PlayerStats *ps)
{
    //std::cout<<"signal recieved in Table"<<std::endl;
    emit clickedTreasureInPlayerStatsnTable(t,ps,this);
}
