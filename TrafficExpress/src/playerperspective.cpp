#include "../headers/playerperspective.h"

#include <QDebug>
#include <roundcarddeck.h>
#include <table.h>

PlayerPerspective::PlayerPerspective(Game *game, int playerIndex, QObject *parent)
    :QGraphicsScene(parent),m_game(game),m_player((game->players())[playerIndex]),
      m_table(new Table())
{
    Train*train=m_game->wagons();
    connect(train,&Train::clickedTreasureInWagonInTrain,this,&PlayerPerspective::onClickedTreasureInWagonInTrain);
    connect(train,&Train::clickedPlayerInWagonInTrain,this,&PlayerPerspective::onClickedPlayerInWagonInTrain);
    connect(train,&Train::clickedWagonInTrain,this,&PlayerPerspective::onClickedWagonInTrain);

    for (Player* p:m_game->players()){
        m_table->push_back(new PlayerStats(p));
    }
    connect(m_table,&Table::clickedTreasureInPlayerStatsInTable,this,&PlayerPerspective::onClickedTreasureInPlayerStatsInTable);
    connect(m_player,&Player::clickedCardInHandInPlayer,this,&PlayerPerspective::onClickedCardInHandInPlayer);
    connect(m_player,&Player::clickedCardInDeckInPlayer,this,&PlayerPerspective::onClickedCardInDeckInPlayer);

}

PlayerPerspective::PlayerPerspective()
{
    for(Player*p:m_game->players())
        m_game->wagons()->getWagons()[0]->addPlayerDown(p);
    delete m_game;
}

void PlayerPerspective::addGameToScene()
{

    auto train = m_game->wagons();
    this->addItem(train);
    train->setPos(50,50);

    this->addItem(m_table);
    m_table->setPos(770,300);

    RoundCardDeck*rdc=m_game->rounds();
    this->addItem(rdc);
    rdc->setPos(400,300);

    Deck*groupDeck = m_game->getCardsPlayed();
    this->addItem(groupDeck);
    groupDeck->setPos(200,300);

    Deck* playerDeck = m_player->deck();
    this->addItem(playerDeck);
    playerDeck->setPos(50,300);

    Hand*hand = m_player->hand();
    this->addItem(hand);
    hand->setPos(50,450);

    DialogueBox *db = m_game->dialogueBox();
    this->addItem(db);
    db->setPos(300,10);
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

int PlayerPerspective::getPlayerSize()
{
    return m_game->players().size();
}

void PlayerPerspective::onClickedTreasureInWagonInTrain(Treasure *t, Wagon *w, Train *train)
{
    if (m_game->currentAction() == ActionType::ROBBERY && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2
            && m_player->positionInTrain() == train->getWagonIndex(w))
    {
            emit actionRobberySignal(w->getTreasureIndex(t, m_player->roof()),train->getWagonIndex(w));
            return;
    }

}

void PlayerPerspective::onClickedCardInHandInPlayer(Card *c, Hand *h, Player *p)
{

    if(p->isItMyMove() && c->Type()==CardType::ACTION_CARD &&
            m_game->phase()==Phase::PHASE_1){

        int playerIndex=m_game->findPlayerById(m_player->id());
        int cardIndex=(h->getCardIndex(c));

        emit playerPlayedCard(playerIndex,cardIndex);

        if(m_game->phase() != Phase::PHASE_2)
            emit movePlayed(this,-1);
        else
            emit movePlayed(this, m_game->getIndexOfPlayerToMove());

        return;
    }
}

void PlayerPerspective::onClickedCardInDeckInPlayer(Card *c, Deck *d, Player *p)
{

    if(p->isItMyMove() && m_game->phase()==Phase::PHASE_1 && d->size() >= 3 && p->hand()->size() <= 6)
    {
        int indexOfPlayer=m_game->findPlayerById(m_player->id());
        emit playerDrawCards(indexOfPlayer);
        emit movePlayed(this,-1);
    }

}

void PlayerPerspective::onClickedTreasureInPlayerStatsInTable(Treasure *t, PlayerStats *ps, Table *p)
{
    if (m_game->currentAction() == ActionType::PUNCH && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2 &&
        m_game->actionPending() && m_game->playerClicked() == m_game->findPlayerById(ps->getPlayer()->id())) {

        m_game->setActionPending(false);
        unsigned playerIndex = m_game->findPlayerById(ps->getPlayer()->id());
        unsigned wagonIndex = m_player->positionInTrain();

        emit actionPunchSignal(m_game->findPlayersTreasureIndex(t, playerIndex), playerIndex, wagonIndex);
        return;
   }

}

void PlayerPerspective::onClickedPlayerInWagonInTrain(Player *p, Wagon *w, Train *t)
{


    if(m_game->currentAction() == ActionType::FIRE && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2) {

        emit actionFireSignal(m_game->findPlayerById(p->id()));
    }

    if (m_game->currentAction() == ActionType::PUNCH && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2 &&
        p->positionInTrain() == m_player->positionInTrain() && p->id() != m_player->id() && p->roof() == m_player->roof()) {

        m_game->setActionPending(true);
        m_game->setPlayerClicked(m_game->findPlayerById(p->id()));
    }

    return;

}

void PlayerPerspective::onClickedWagonInTrain(Wagon *w, Train *train)
{

    if(m_player->isItMyMove() && m_game->phase()==Phase::WAGON_SELECTION
            && (train->getWagonIndex(w)==0 || train->getWagonIndex(w)==1) ){

        emit playerChoseWagon(m_game->findPlayerById(m_player->id()),train->getWagonIndex(w));

        emit movePlayed(this,-1);
        return;
    }


    if(m_game->currentAction() == ActionType::FLOOR_CHANGE && m_player->isItMyMove() && m_game->phase()==Phase::PHASE_2)
    {

        emit actionChangeFloorSignal(train->getWagonIndex(w));

    }

    if(m_game->currentAction() == ActionType::MOVE && m_player->isItMyMove() && m_game->phase()==Phase::PHASE_2)
    {

        emit actionChangeWagonSignal(train->getWagonIndex(w));

    }

    if(m_game->currentAction() == ActionType::MARSHAL && m_player->isItMyMove() && m_game->phase()==Phase::PHASE_2)
    {

        emit actionSheriffSignal(train->getWagonIndex(w));
    }
}


// PHASE WAGON SELECTION:

void PlayerPerspective::onPlayerChoseWagon(int playerIndex, int wagonIndex)
{
    Player* playerToSet=m_game->players()[playerIndex];
    Wagon* wagonToPutPlayer=(*m_game->wagons())[wagonIndex];
    wagonToPutPlayer->addPlayerDown(playerToSet);
    m_game->players()[playerIndex]->setPositionInTrain(wagonIndex);
    m_game->setNextPlayerToMove();
    if(m_game->findPlayerById(playerToSet->id())==m_game->players().size()-1) {
        m_game->setPhase(Phase::PHASE_1);
        QString text = "PHASE 1: PICK A CARD FROM YOUR HAND OR DRAW 3 FROM DECK. ";
        m_game->dialogueBox()->setText(text);
    }

}

// PHASE 1:

void PlayerPerspective::onPlayerPlayedCard(int playerIndex, int cardIndex)
{


    // Taking Card from the hand and putting it in the group deck
    Hand* h=m_game->players()[playerIndex]->hand();
    Card*c=h->takeCard(cardIndex);
    Deck*d=m_game->getCardsPlayed();

    RoundCard * rc = m_game->rounds()->getRoundCards()[m_game->indexOfRound()];
    MiniRound * mr = rc->getMiniRounds()[m_game->indexOfMiniround()];
    if(mr->getMiniRoundType() == MiniRoundType::HIDDEN) {
        c->setFaceUp(false);
    }

    d->push_back(c);

    // Putting message in dialogue box

//    QString text = QString::fromStdString(((ActionCard*)c)->toString());
//    m_game->dialogueBox()->setText(text);

    if(mr->getMiniRoundType() == MiniRoundType::DOUBLE_CARDS) {
        if(mr->firstDoubleCardPlayed()) {
            mr->setFirstDoubleCardPlayed(false);
        } else {
            mr->setFirstDoubleCardPlayed(true);
            return;
        }
    }
    // Checking the rounds and minirounds
    m_game->updateRounds();

    // Setting next player to move
    if(m_game->phase() != Phase::PHASE_2)
        m_game->setNextPlayerToMove();
}

void PlayerPerspective::onPlayerDrawCards(int playerIndex)
{
    // Taking 3 cards from the deck and putting it in the hand.
    PlayerGroup pg;
    pg=m_game->players();
    Player*playerToMove=pg[playerIndex];

    Deck*d=playerToMove->deck();
    for(unsigned i = 0; i < 3; i++ )
    {
        Card* takenCard = d->back();
        takenCard->setFaceUp(true);
        d->pop_back();
        playerToMove->hand()->push_back(takenCard);
    }
    // Putting message in dialogue box
//    QString text = QString::fromStdString(::toString(playerToMove->id()));
//    text.append(" draw 3 cards from his deck. ");
//    m_game->dialogueBox()->setText(text);

    // Checking the rounds and minirounds
    m_game->updateRounds();

    // Setting next player to move
    if(m_game->phase() != Phase::PHASE_2)
        m_game->setNextPlayerToMove();


}

// PHASE 2:

void PlayerPerspective::onActionFireSignal(int playerIndex)
{
    if(!m_game->actionFire(playerIndex)) {

        QString text = "Can't shoot that player!";
        m_game->dialogueBox()->setText(text);

    }
    else {
        // Putting message in dialogue box
        QString text = QString::fromStdString(::toString(m_game->players()[playerIndex]->id()));
        text.append(" 's been shot by ");
        text.append(QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id())));
        m_game->dialogueBox()->setText(text);

        m_game->checkNextActionCard();
        emit movePlayed(this, m_game->getIndexOfPlayerToMove());
    }
}

void PlayerPerspective::onActionChangeFloorSignal(int wagonIndex)
{
    m_game->actionFloorChange();

    // Putting message in dialogue box
    QString text = QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id()));
    text.append(" changed floor!");
    m_game->dialogueBox()->setText(text);

    m_game->checkNextActionCard();
    emit movePlayed(this, m_game->getIndexOfPlayerToMove());
}

void PlayerPerspective::onActionChangeWagonSignal(int wagonIndex)
{
    if (!m_game->actionChangeWagon(wagonIndex))
    {
        QString text = "Can't move there!";
        m_game->dialogueBox()->setText(text);

    }
    else
    {
        // Putting message in dialogue box
        QString text = QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id()));
        text.append(" changed wagon!");
        m_game->dialogueBox()->setText(text);

        m_game->checkNextActionCard();
        emit movePlayed(this, m_game->getIndexOfPlayerToMove());

    }

}

void PlayerPerspective::onActionSheriffSignal(int wagonIndex)
{
    m_game->actionSheriffMove(m_game->wagons()->getWagons()[wagonIndex]);

    // Putting message in dialogue box
    QString text = QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id()));
    text.append(" moved sheriff!");
    m_game->dialogueBox()->setText(text);

    m_game->checkNextActionCard();
    emit movePlayed(this, m_game->getIndexOfPlayerToMove());

}

void PlayerPerspective::onActionRobberySignal(int treasureIndex, int wagonIndex)
{
    PlayerStats *ps = m_table->getPlayerStats()[m_game->getIndexOfPlayerToMove()];
    auto[wagonToTakeTreasure, treasureToTake] = m_game->actionRobbery(treasureIndex, wagonIndex);


    if (m_game->players()[m_game->getIndexOfPlayerToMove()]->roof()) {
        ps->addTreasureToPlayer(wagonToTakeTreasure->takeContentUp(treasureToTake));
    } else {
        ps->addTreasureToPlayer(wagonToTakeTreasure->takeContentDown(treasureToTake));
    }

    // Putting message in dialogue box
    QString text = QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id()));
    text.append(" took treasure!");
    m_game->dialogueBox()->setText(text);

    m_game->checkNextActionCard();
    emit movePlayed(this, m_game->getIndexOfPlayerToMove());
}

void PlayerPerspective::onActionPunchSignal(int treasureIndex, int playerIndex, int wagonIndex)
{

    PlayerStats *ps = m_table->getPlayerStats()[playerIndex];
    auto[wagonToUpdate, treasure] = m_game->actionPunch(treasureIndex, wagonIndex, playerIndex);

    if (m_game->players()[m_game->getIndexOfPlayerToMove()]->roof())
        wagonToUpdate->addContentUp(ps->takeTreasureFromPlayer(treasure));
    else
        wagonToUpdate->addContentDown(ps->takeTreasureFromPlayer(treasure));

    // Putting message in dialogue box
    QString text = QString::fromStdString(::toString(m_game->players()[playerIndex]->id()));
    text.append(" 's been punched by ");
    text.append(QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id())));
    m_game->dialogueBox()->setText(text);

    m_game->checkNextActionCard();
    emit movePlayed(this, m_game->getIndexOfPlayerToMove());
}
