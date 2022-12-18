#ifndef PLAYERPERSPECTIVE_H
#define PLAYERPERSPECTIVE_H

#include <game.h>
#include <qgraphicsscene.h>



class PlayerPerspective:public QGraphicsScene
{
public:
    PlayerPerspective(Game*game,int playerIndex,QObject*parent=nullptr);
    void addGameToScene();
    void removeGameFromScene();
    void drawCards(int n);
    void setNextPlayerToToMove();
    int getPlayerToMoveIndex()const;
private:
    void setMyMove(bool);
    Player*m_player;
    Game*m_game;
};

#endif // PLAYERPERSPECTIVE_H
