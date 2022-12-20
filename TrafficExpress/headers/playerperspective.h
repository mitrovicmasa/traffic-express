#ifndef PLAYERPERSPECTIVE_H
#define PLAYERPERSPECTIVE_H

#include <game.h>
#include <qgraphicsscene.h>
#include <table.h>



class PlayerPerspective:public QGraphicsScene
{
public:
    PlayerPerspective(Game*game,int playerIndex,QObject*parent=nullptr);
    void addGameToScene();
    void removeGameFromScene();

    void drawCards(int n);
    void setNextPlayerToToMove();

    int getPlayerToMoveIndex()const;
    int getPlayerSize();

public slots:
    void onClickedTreasureInWagonInTrainInTran(Treasure*t,Wagon*w,Train*train);
    void onClickedCardInHandInPlayer(Card*c,Hand*h,Player*p);
    void onClickedWagonInTrain(Wagon*w,Train*train);

private:
    void setMyMove(bool);
    Player*m_player;
    Game*m_game;
    Table*m_table;
};

#endif // PLAYERPERSPECTIVE_H
