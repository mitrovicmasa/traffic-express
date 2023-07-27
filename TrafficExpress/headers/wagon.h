#ifndef WAGON_H
#define WAGON_H

#include <player.h>
#include <playergroup.h>
#include <sheriff.h>
#include <treasure.h>
#include <treasurechest.h>

#include <vector>

class Wagon : public QGraphicsObject, public Serializable {
  Q_OBJECT
 public:
  // Constructors
  Wagon();
  Wagon(TreasureChest& contentDown, TreasureChest& contentUp);
  Wagon(TreasureChest& upt, TreasureChest& downt, PlayerGroup& upp,
        PlayerGroup& downp, bool isLocomotive);

  // Get methods
  TreasureChest& getContentDown();
  TreasureChest& getContentUp();
  PlayerGroup& getPlayersUp();
  PlayerGroup& getPlayersDown();
  bool isLocomotive() const;

  // Set methods
  void setContentDown(TreasureChest newContentDown);
  void setContentUp(TreasureChest newContentUp);
  void setIsLocomotive(bool newIsLocomotive);

  // Other methods
  void addContentUp(Treasure*);
  void addContentDown(Treasure*);
  void addPlayerUp(Player*);
  void addPlayerDown(Player*);
  void addSheriffDown(Sheriff*);

  Sheriff* takeSheriffDown();
  Treasure* takeContentUp(TreasureType);
  Treasure* takeContentDown(TreasureType);
  Player* takePlayerUp(BanditType);
  Player* takePlayerDown(BanditType);

  Treasure* takeContentUp(Treasure*);
  Treasure* takeContentDown(Treasure*);
  Player* takePlayerUp(Player*);
  Player* takePlayerDown(Player*);

  int numberOfTreasureInWagonDown(TreasureType) const;
  int getTreasureIndex(Treasure*, bool) const;

  std::string toString();

  // GUI
  int height() const;
  int width() const;
  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget);
  void mousePressEvent(QGraphicsSceneMouseEvent* event);
  void repositionTreasure();
  void repositionPlayers();

  // Serializable interface
  QVariant toVariant() const;
  void fromVariant(const QVariant& variant);

 signals:
  void clickedTreasureInWagon(Treasure* t, Wagon* w);
  void clickedPlayerInWagon(Player*, Wagon*);
  void clickedWagon(Wagon* w);

 public slots:
  void onCickedTreasure(Treasure* t);
  void onClickedPlayer(Player*);

 private:
  bool m_isLocomotive = false;
  TreasureChest m_contentUp;
  TreasureChest m_contentDown;
  PlayerGroup m_playersUp;
  PlayerGroup m_playersDown;
  Sheriff* m_sheriff;
};

#endif  // WAGON_H
