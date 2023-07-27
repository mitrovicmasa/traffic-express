#include "../headers/table.h"

#include <QGraphicsScene>
#include <QPainter>

// Constructors
Table::Table() : QGraphicsObject() {
  setFlags(GraphicsItemFlag::ItemIsSelectable);
}

// Get methods
PlayerStatsCollection &Table::getPlayerStats() { return m_playerStats; }

// Other methods
void Table::push_back(PlayerStats *p) {
  m_playerStats.push_back(p);
  p->setParentItem(this);
  p->setPos(0, (this->size() - 1) * 70 + 1);
  connect(p, &PlayerStats::clickedTreasueInPlayeStats, this,
          &Table::onClickedTreasureInPlayerStats);
}

int Table::size() { return m_playerStats.size(); }

PlayerStats *Table::operator[](int i) { return m_playerStats[i]; }

// GUI
int Table::height() const { return 350; }

int Table::width() const { return 300; }

QRectF Table::boundingRect() const { return QRectF(0, 0, width(), height()); }

void Table::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

void Table::onClickedTreasureInPlayerStats(Treasure *t, PlayerStats *ps) {
  emit clickedTreasureInPlayerStatsInTable(t, ps, this);
}
