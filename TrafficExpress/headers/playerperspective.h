#ifndef PLAYERPERSPECTIVE_H
#define PLAYERPERSPECTIVE_H

#include <game.h>
#include <qgraphicsscene.h>
#include <table.h>
#include <dialoguebox.h>



class PlayerPerspective:public QGraphicsScene
{
    Q_OBJECT
public:
    PlayerPerspective(Game*game,int playerIndex,QObject*parent=nullptr);
    void addGameToScene();
    void removeGameFromScene();

    void drawCards(int n);
    void setNextPlayerToToMove();

    int getPlayerToMoveIndex()const;
    int getPlayerSize();

public slots:
    //reacting to internal signals
    void onClickedTreasureInWagonInTrainInTran(Treasure*t,Wagon*w,Train*train);
    void onClickedCardInHandInPlayer(Card*c,Hand*h,Player*p);//*
    void onClickedCardInDeckInPlayer(Card*c,Deck*d,Player*p);
    void onClickedTreasureInPlayerStatsInTable(Treasure*,PlayerStats*,Table*);
    void onClickedPlayerInWagonInTrain(Player*,Wagon*,Train*);
    void onClickedWagonInTrain(Wagon*w,Train*train);//*

    //reacting to external signals
    void onPlayerChoseWagon(int playerIndex,int wagonIndex);
    void onPlayerPlayedCard(int playerIndex,int CardIndex);
    void onPlayerDrawCards(int playerIndex);

signals:
    void playerChoseWagon(int playerIndex,int wagonIndex);
    void playerPlayedCard(int playerIndex,int CardIndex);
    void movePlayed(PlayerPerspective*);
    void playerDrawCards(int playerIndex);

private:
    void setMyMove(bool);

    Player*m_player;
    Game*m_game;
    Table*m_table;
};

#endif // PLAYERPERSPECTIVE_H
