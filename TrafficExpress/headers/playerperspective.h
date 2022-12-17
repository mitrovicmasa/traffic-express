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
private:
    bool m_myTurn;
    Player*m_player;
    Game*m_game;
};

#endif // PLAYERPERSPECTIVE_H
