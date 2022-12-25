#include "../headers/playerperspective.h"


#include <QDebug>
#include <roundcarddeck.h>
#include <table.h>

PlayerPerspective::PlayerPerspective(Game *game, int playerIndex, QObject *parent)
    :QGraphicsScene(parent),m_game(game),m_player((game->players())[playerIndex]),
      m_table(new Table())
{
    Train*train=m_game->wagons();
    connect(train,&Train::clickedTreasureInWagonInTrain,this,&PlayerPerspective::onClickedTreasureInWagonInTrainInTran);
    connect(train,&Train::clickedPlayerInWagonInTrain,this,&PlayerPerspective::onClickedPlayerInWagonInTrain);
    connect(train,&Train::clickedWagonInTrain,this,&PlayerPerspective::onClickedWagonInTrain);
    //m_table= new Table();
    for (Player* p:m_game->players()){
        m_table->push_back(new PlayerStats(p));

    }
    connect(m_table,&Table::clickedTreasureInPlayerStatsnTable,this,&PlayerPerspective::onClickedTreasureInPlayerStatsInTable);
    connect(m_player,&Player::clickedCardInHandInPlayer,this,&PlayerPerspective::onClickedCardInHandInPlayer);
    connect(m_player,&Player::clickedCardInDeckInPlayer,this,&PlayerPerspective::onClickedCardInDeckInPlayer);

}

void PlayerPerspective::addGameToScene()
{

    auto train = m_game->wagons();
    this->addItem(train);
    train->setPos(50,50);

    this->addItem(m_table);
    m_table->setPos(850,300);

//    RoundCard*roundcard = m_game->rounds()[0];
//    this->addItem(roundcard);
//    roundcard->setPos(400,300);

    RoundCardDeck*rdc=m_game->rounds();
    this->addItem(rdc);
    rdc->setPos(400,300);

    Deck*groupDeck = m_game->getCardsPlayed();
    this->addItem(groupDeck);
    groupDeck->setPos(200,300);

    Deck* playerDeck = m_player->deck();
    //m_player->deck()->setAllCardsFaceDown();
    this->addItem(playerDeck);
    playerDeck->setPos(50,300);

//    Deck* bulletDeck = m_player->bulletDeck();
//    this->addItem(bulletDeck);
//    bulletDeck->setPos(300,300);

    Hand*hand = m_player->hand();
    this->addItem(hand);
    hand->setPos(50,450);

    DialogueBox *db = m_player->dialog();
    this->addItem(db);
    db->setPos(890,20);

    Sheriff *s = new Sheriff();
    this->addItem(s);
    s->setPos(740,130);
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
    //return 0;
}

int PlayerPerspective::getPlayerSize()
{
    return m_game->players().size();
}

void PlayerPerspective::onClickedTreasureInWagonInTrainInTran(Treasure *t, Wagon *w, Train *train)
{
//ToDO
    std::cout<<"Treasure t from wagon w from train train signaled player perspective"<<std::endl;
    //std::cout<<<<std::endl;

    if(m_player->isItMyMove()){
        std::cout<<"It is my move"<<std::endl;
       Treasure* selectedTreasure=w->takeContentDown(t);

       //disconnect(selectedTreasure,&Treasure::clickedTreasure,w,&Wagon::OnCickedTreasuere);
       //m_player->treasure().push_back(selectedTreasure);


       (*m_table)[m_game->getIndexOfPlayerToMove()]->addTreasureToPlayer(selectedTreasure);
        w->repositionTreasure();
    }
}

void PlayerPerspective::onClickedCardInHandInPlayer(Card *c, Hand *h, Player *p)
{
    std::cout<<"Player perspective recieved signal"<<std::endl;
    if(!p->isItMyMove())
        qDebug()<<"not my move";

    if(p->isItMyMove() && c->Type()==CardType::ACTION_CARD &&
            m_game->phase()==Phase::PHASE_1){
        std::cout<<"It is my move!"<<std::endl;
//        ActionCard*ac=static_cast<ActionCard*>(c);

        int playerIndex=m_game->findPlayerById(m_player->id());
        int cardIndex=(h->getCardIndex(c));


        emit playerPlayedCard(playerIndex,cardIndex);
        emit movePlayed(this);
        return;
    }
}

void PlayerPerspective::onClickedCardInDeckInPlayer(Card *c, Deck *d, Player *p)
{
//    std::cout<<"Player perspective recieved signal in onClickedCardInDeckInPlayer "<<std::endl;

    if(!p->isItMyMove()){
        qDebug()<<"not my move";
        int playerThatClicked =m_game->findPlayerById(p->id());
        int indexOfPlayer=m_game->getIndexOfPlayerToMove();
        qDebug()<<"Player to move:"<<indexOfPlayer;
        qDebug()<<"Player that clicked:"<<indexOfPlayer;

    }
    if(p->isItMyMove() && m_game->phase()==Phase::PHASE_1 && d->size() >= 3)
    {

        int indexOfPlayer=m_game->findPlayerById(m_player->id());
        emit playerDrawCards(indexOfPlayer);
        emit movePlayed(this);
    }

}

void PlayerPerspective::onClickedTreasureInPlayerStatsInTable(Treasure *t, PlayerStats *ps, Table *p)
{
    std::cout<<"signal recieved in player perspective"<<std::endl;

    for(PlayerStats*tmp:m_table->getPlayerStats()){

        if(m_player==tmp->getPlayer() && tmp!=ps)
            tmp->addTreasureToPlayer(ps->takeTreasureFromPlayer(t));

//        if(ps->takeTreasureFromPlayer(t))
//            qDebug()<<"notNull";
    }

}

void PlayerPerspective::onClickedPlayerInWagonInTrain(Player *p, Wagon *w, Train *t)
{
    std::cout<<"Player is clicked"<<std::endl;
    (*t)[0]->addPlayerDown(w->takePlayerDown(p));


}

void PlayerPerspective::onClickedWagonInTrain(Wagon *w, Train *train)
{

    if(m_player->isItMyMove() && m_game->phase()==Phase::WAGON_SELECTION
            && (train->getWagonIndex(w)==0 || train->getWagonIndex(w)==1) ){

        emit playerChoseWagon(m_game->findPlayerById(m_player->id()),train->getWagonIndex(w));

        emit movePlayed(this);
        return;
    }

//    if(m_game->phase()==Phase::PHASE_1){
//        ...
//    }


}

void PlayerPerspective::onPlayerChoseWagon(int playerIndex, int wagonIndex)
{
    qDebug()<<"onPlayerChoseWagon";
    Player* playerToSet=m_game->players()[playerIndex];
    Wagon* wagonToPutPlayer=(*m_game->wagons())[wagonIndex];
    wagonToPutPlayer->addPlayerDown(playerToSet);
    m_game->setNextPlayerToMove();
    if(m_game->findPlayerById(playerToSet->id())==m_game->players().size()-1)
        m_game->setPhase(Phase::PHASE_1);



}

void PlayerPerspective::onPlayerPlayedCard(int playerIndex, int cardIndex)
{
//    qDebug()<<"recieved signal when card clicked";
    Hand* h=m_game->players()[playerIndex]->hand();
    Card*c=h->takeCard(cardIndex);
    Deck*d=m_game->getCardsPlayed();
    d->push_back(c);
    RoundCardDeck*rcd=m_game->rounds();
    //Test
    int iMiniRound=m_game->indexOfMiniround();
    int iRound=m_game->indexOfRound();
    qDebug()<<"Round"<<iRound;
    qDebug()<<"MiniRound:"<<iMiniRound;
    if(iMiniRound==((*rcd)[iRound]->getMiniRounds()).size()-1){
        m_game->setIndexOfMiniround(0);
        m_game->setPhase(Phase::PHASE_2);


        m_game->setNextPlayerToMove();
        if(rcd->size()-1==iRound){
            //Game gotov
            return;
        }

         m_game->setIndexOfRound(iRound+1);
        return;
    }
    if(playerIndex==m_game->players().size()-1)
        m_game->setIndexOfMiniround(iMiniRound+1);
    //End of test
    m_game->setNextPlayerToMove();
}

void PlayerPerspective::onPlayerDrawCards(int playerIndex)
{
    PlayerGroup pg;
    pg=m_game->players();
    Player*playerToMove=pg[playerIndex];
    //qDebug()<<playerToMove;



    Deck*d=playerToMove->deck();
    for(unsigned i = 0; i < 3; i++ )
    {
        Card* takenCard = d->back();
        takenCard->setFaceUp(true);
        d->pop_back();
        playerToMove->hand()->push_back(takenCard);
    }


    m_game->setNextPlayerToMove();

}
