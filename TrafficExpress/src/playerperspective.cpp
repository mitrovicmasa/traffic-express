#include "../headers/playerperspective.h"

#include <table.h>

PlayerPerspective::PlayerPerspective(Game *game, int playerIndex, QObject *parent)
    :QGraphicsScene(parent),m_game(game),m_player((game->players())[playerIndex]),
      m_table(new Table())
{
    Train*train=m_game->wagons();
    connect(train,&Train::clickedTreasureInWagonInTrain,this,&PlayerPerspective::onClickedTreasureInWagonInTrainInTran);
    connect(train,&Train::clickedWagonInTrain,this,&PlayerPerspective::onClickedWagonInTrain);
    //m_table= new Table();
    for (Player* p:m_game->players()){
        m_table->push_back(new PlayerStats(p));
    }
    connect(m_player,&Player::clickedCardInHandInPlayer,this,&PlayerPerspective::onClickedCardInHandInPlayer);
}

void PlayerPerspective::addGameToScene()
{

    auto train = m_game->wagons();
    this->addItem(train);
    train->setPos(50,50);


    this->addItem(m_table);
    m_table->setPos(810,270);

    RoundCard*roundcard = m_game->rounds()[0];
    this->addItem(roundcard);
    roundcard->setPos(500,300);

    Deck*groupDeck = m_game->getCardsPlayed();
    this->addItem(groupDeck);
    groupDeck->setPos(300,300);

    Deck* playerDeck = m_player->deck();
    //m_player->deck()->setAllCardsFaceDown();
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

void PlayerPerspective::onClickedTreasureInWagonInTrainInTran(Treasure *t, Wagon *w, Train *train)
{
//ToDO
    std::cout<<"Treasure t from wagon w from train train signaled player perspective"<<std::endl;
    //std::cout<<<<std::endl;

    if(m_player->isItMyMove()){
        std::cout<<"It is my move"<<std::endl;
       Treasure* selectedTreasure=w->takeContentDown(t->getType());

       disconnect(selectedTreasure,&Treasure::clickedTreasure,w,&Wagon::OnCickedTreasuere);
       //m_player->treasure().push_back(selectedTreasure);


       (*m_table)[m_game->getIndexOfPlayerToMove()]->addTreasureToPlayer(selectedTreasure);
        w->repositionTreasure();
    }
}

void PlayerPerspective::onClickedCardInHandInPlayer(Card *c, Hand *h, Player *p)
{
    std::cout<<"Player perspective recieved signal"<<std::endl;

    if(p->isItMyMove() && c->Type()==CardType::ACTION_CARD){
        std::cout<<"It is my move!"<<std::endl;
        ActionCard*ac=static_cast<ActionCard*>(c);
        for(auto it=h->begin();it!=h->end();it++){
            Card*tmp=*it;
            if(tmp->Type()==CardType::ACTION_CARD){

                ActionCard* tmpac=static_cast<ActionCard*>(tmp);
                if(ac->action()==tmpac->action()){
                    h->erase(it);
                    m_game->getCardsPlayed()->push_back(tmp);
                    break;
                }
            }



        }
        h->repositionCards();


    }
}

void PlayerPerspective::onClickedWagonInTrain(Wagon *w, Train *train)
{
    std::cout<<"Wagon clicked in train n player perspective!"<<std::endl;
    if(m_player->isItMyMove()){
        w->addPlayerDown(m_player);



    }

}
