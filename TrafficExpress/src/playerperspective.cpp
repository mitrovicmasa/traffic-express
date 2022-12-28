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
    m_table->setPos(770,300);

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

//    Deck* bulletDeck = m_player->bullet_deck();
//    this->addItem(bulletDeck);
//    bulletDeck->setPos(300,300);

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

//    if(m_player->isItMyMove()){
//        std::cout<<"It is my move"<<std::endl;
//       Treasure* selectedTreasure=w->takeContentDown(t);

//       //disconnect(selectedTreasure,&Treasure::clickedTreasure,w,&Wagon::OnCickedTreasuere);
//       //m_player->treasure().push_back(selectedTreasure);


//       (*m_table)[m_game->getIndexOfPlayerToMove()]->addTreasureToPlayer(selectedTreasure);
//        w->repositionTreasure();
//    }


    if (m_game->currentAction() == ActionType::TAKETREASURE && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2 && m_player->positionInTrain() == train->getWagonIndex(w))
    {
        emit actionRobberySignal(w->getTreasureIndex(t, m_player->roof()),train->getWagonIndex(w));
        //emit movePlayed(this);
            return;
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
        emit movePlayed(this,-1);
        return;
    }
}

void PlayerPerspective::onClickedCardInDeckInPlayer(Card *c, Deck *d, Player *p)
{
//    std::cout<<"Player perspective recieved signal in onClickedCardInDeckInPlayer "<<std::endl;

    if(!p->isItMyMove()){
        qDebug()<<"not my move";
        int indexOfPlayer=m_game->getIndexOfPlayerToMove();
        qDebug()<<"Player to move:"<<indexOfPlayer;
        qDebug()<<"Player that clicked:"<<indexOfPlayer;

    }

    if(p->isItMyMove() && m_game->phase()==Phase::PHASE_1 && d->size() >= 3)
    {

        int indexOfPlayer=m_game->findPlayerById(m_player->id());
        emit playerDrawCards(indexOfPlayer);
        emit movePlayed(this,-1);
    }


}

void PlayerPerspective::onClickedTreasureInPlayerStatsInTable(Treasure *t, PlayerStats *ps, Table *p)
{
    std::cout<<"signal recieved in player perspective"<<std::endl;

//    for(PlayerStats*tmp:m_table->getPlayerStats()){

//        if(m_player==tmp->getPlayer() && tmp!=ps)
//            tmp->addTreasureToPlayer(ps->takeTreasureFromPlayer(t));

//        if(ps->takeTreasureFromPlayer(t))
//            qDebug()<<"notNull";
//    }

    if (m_game->currentAction() == ActionType::PUNCH && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2 && m_game->actionPending()) {

        m_game->setActionPending(false);
        unsigned playerIndex = m_game->findPlayerById(ps->getPlayer()->id());
        unsigned wagonIndex = m_player->positionInTrain();

        emit actionPunchSignal(m_game->findPlayersTreasureIndex(t, playerIndex), playerIndex, wagonIndex);
        //emit movePlayed(this);
        return;
   }

}

void PlayerPerspective::onClickedPlayerInWagonInTrain(Player *p, Wagon *w, Train *t)
{

    std::cout<< ::toString(p->id()) + " is clicked" <<std::endl;

    // Ovde posle dodati uslov da je odigrana kartica Fire :)
    if(m_game->currentAction() == ActionType::FIRE && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2) {

        qDebug() << "we are in onClickedPlayerInWagonInTrain and it's phase_2 and my move";

        emit actionFireSignal(m_game->findPlayerById(p->id()));
        //emit movePlayed(this);
    }

    if (m_game->currentAction() == ActionType::PUNCH && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2 &&
        m_player->positionInTrain() == p->positionInTrain() && m_player->roof() == p->roof() && !p->treasure().empty())
    {
        m_game->setActionPending(true);
        return;
    } else if (m_game->currentAction() == ActionType::PUNCH && m_player->isItMyMove() && m_game->phase() == Phase::PHASE_2 &&
               m_player->positionInTrain() == p->positionInTrain() && m_player->roof() == p->roof() && p->treasure().empty()) {
        qDebug() << "Choose another player!";
        return;
    } else {
        m_game->setNextPlayerToMove();
        return;
    }
}

void PlayerPerspective::onClickedWagonInTrain(Wagon *w, Train *train)
{

    qDebug() << (m_game->phase() == Phase::PHASE_2 ? "PHASE 2 ACTIVE" : "NOT PHASE 2");
    qDebug() << (m_game->phase() == Phase::PHASE_1 ? "PHASE 1 ACTIVE" : "NOT PHASE 1");
    qDebug() << (m_game->phase() == Phase::WAGON_SELECTION ? "WS ACTIVE" : "NOT WS");

    qDebug() << (m_game->currentAction() == ActionType::FLOOR_CHANGE ? "FLOOR CHANGE" : ".");
    qDebug() << (m_game->currentAction() == ActionType::MOVE ? "MOVE" : ".");
    qDebug() << (m_game->currentAction() == ActionType::MARSHAL ? "MARSHALL" : ".");


    qDebug() << m_game->getIndexOfPlayerToMove();



    if(m_player->isItMyMove() && m_game->phase()==Phase::WAGON_SELECTION
            && (train->getWagonIndex(w)==0 || train->getWagonIndex(w)==1) ){

        emit playerChoseWagon(m_game->findPlayerById(m_player->id()),train->getWagonIndex(w));

        emit movePlayed(this,-1);
        return;
    }


    if(m_game->currentAction() == ActionType::FLOOR_CHANGE && m_player->isItMyMove() && m_game->phase()==Phase::PHASE_2)
    {

        qDebug() << "Floor Change time";


        emit actionChangeFloorSignal(train->getWagonIndex(w));

    }

    if(m_game->currentAction() == ActionType::MOVE && m_player->isItMyMove() && m_game->phase()==Phase::PHASE_2)
    {

        qDebug() << "Wagon changetime";

        emit actionChangeWagonSignal(train->getWagonIndex(w));


    }

    if(m_game->currentAction() == ActionType::MARSHAL && m_player->isItMyMove() && m_game->phase()==Phase::PHASE_2)
    {

        qDebug() << "Marshall time";

        emit actionSheriffSignal(train->getWagonIndex(w));


    }



}


// PHASE WAGON SELECTION:

void PlayerPerspective::onPlayerChoseWagon(int playerIndex, int wagonIndex)
{
    qDebug()<<"onPlayerChoseWagon";
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
    d->push_back(c);

    // Putting message in dialogue box
    QString text = QString::fromStdString(((ActionCard*)c)->toString());
    m_game->dialogueBox()->setText(text);

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
    QString text = QString::fromStdString(::toString(playerToMove->id()));
    text.append(" draw 3 cards from his deck. ");
    m_game->dialogueBox()->setText(text);

    // Checking the rounds and minirounds
    m_game->updateRounds();

    // Setting next player to move
    if(m_game->phase() != Phase::PHASE_2)
        m_game->setNextPlayerToMove();


}



// PHASE 2:

void PlayerPerspective::onActionFireSignal(int playerIndex)
{
    qDebug() << "we are in onActionFireSignal";

    if(!m_game->actionFire(playerIndex)) {
        qDebug() << "You can't shoot him!";
    } else {
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
    //m_game->setNextPlayerToMove();

    // Putting message in dialogue box
    QString text = QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id()));
    text.append(" changed floor!");
    m_game->dialogueBox()->setText(text);

    m_game->checkNextActionCard();
    emit movePlayed(this, m_game->getIndexOfPlayerToMove());
}

void PlayerPerspective::onActionChangeWagonSignal(int wagonIndex)
{
    m_game->actionChangeWagon(wagonIndex);
    //m_game->setNextPlayerToMove();

    // Putting message in dialogue box
    QString text = QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id()));
    text.append(" changed wagon!");
    m_game->dialogueBox()->setText(text);


    m_game->checkNextActionCard();
    emit movePlayed(this, m_game->getIndexOfPlayerToMove());

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

    qDebug() << "Player index:" << m_game->getIndexOfPlayerToMove();
    qDebug() << "Wagon: " << wagonIndex;
    qDebug() << "Is on roof: " << m_player->roof();

    if (m_player->roof()) {
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

//    if (!m_game->players()[m_game->getIndexOfPlayerToMove()]->roof()) {

//        if (wagonToTakeTreasure->getContentDown().empty()) {

//            qDebug() << "You can't take treasure from this wagon!";
//            //m_game->setNextPlayerToMove();
//            return;
//        }

//        qDebug() << "Down!";
//        Treasure* treasureToTake = wagonToTakeTreasure->getContentDown()[treasureIndex];

//        ps->addTreasureToPlayer(wagonToTakeTreasure->takeContentDown(treasureToTake));
//    } else {
//        if (wagonToTakeTreasure->getContentUp().empty()) {
//            qDebug() << "You can't take treasure from this wagon!";
//            //->setNextPlayerToMove();
//            return;
//        }

//        qDebug() << "Up!";
//        Treasure* treasureToTake = wagonToTakeTreasure->getContentUp()[treasureIndex];

//        ps->addTreasureToPlayer(wagonToTakeTreasure->takeContentUp(treasureToTake));
//    }

    //m_game->setNextPlayerToMove(); // NE KORISTI SE OVO VISE U AKCIJAMA
}

void PlayerPerspective::onActionPunchSignal(int treasureIndex, int playerIndex, int wagonIndex)
{
    qDebug() << "we are in onActionPunchSignal";

    PlayerStats *ps = m_table->getPlayerStats()[playerIndex];
    auto[wagonToUpdate, treasure] = m_game->actionPunch(treasureIndex, wagonIndex, playerIndex);

    if (m_player->roof())
        wagonToUpdate->addContentUp(ps->takeTreasureFromPlayer(treasure));
    else
        wagonToUpdate->addContentDown(ps->takeTreasureFromPlayer(treasure));

    // Putting message in dialogue box
    QString text = QString::fromStdString(::toString(m_game->players()[playerIndex]->id()));
    text.append(" 's been punched by ");
    text.append(QString::fromStdString(::toString(m_game->players()[m_game->getIndexOfPlayerToMove()]->id())));
    m_game->dialogueBox()->setText(text);

    m_game->setNextPlayerToMove();
    emit movePlayed(this, m_game->getIndexOfPlayerToMove());
}
