#include "../headers/playerperspective.h"

#include <table.h>

PlayerPerspective::PlayerPerspective(Game *game, int playerIndex, QObject *parent)
    :QGraphicsScene(parent),m_game(game),m_player((game->players())[playerIndex])
{

}

void PlayerPerspective::addGameToScene()
{


    auto train = m_game->wagons();
    this->addItem(train);
    train->setPos(50,50);

    Table* table = new Table();
    for (Player* p:m_game->players()){
        table->push_back(new PlayerStats(p));
    }
    this->addItem(table);
    table->setPos(810,270);

    RoundCard*roundcard = m_game->rounds()[0];
    this->addItem(roundcard);
    roundcard->setPos(500,300);

    Deck*groupDeck = new Deck();
    this->addItem(groupDeck);
    groupDeck->setPos(300,300);

    Deck* playerDeck = m_player->deck();
    this->addItem(playerDeck);
    playerDeck->setPos(50,300);

    Hand*hand = m_player->hand();
    this->addItem(hand);
    hand->setPos(50,450);
}

void PlayerPerspective::removeGameFromScene()
{
    for(auto x:this->children())
        x->setParent(nullptr);
}

void PlayerPerspective::drawCards(int n)
{
    m_player->drawCards(n);
}

void PlayerPerspective::setNextPlayerToToMove()
{
    int lastIndex=m_game->getIndexOfPlayerToMove();
    int nextIndex=(lastIndex+1)%(m_game->players().size());
    m_game->setIndexOfPlayerToMove(nextIndex);

}

int PlayerPerspective::getPlayerToMoveIndex() const
{
    return m_game->getIndexOfPlayerToMove();
}
