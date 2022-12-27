#include "../headers/game.h"

//// Constructors
//Game::Game()
//{

//}

Game::Game( std::vector<Player*> &players)
    : m_players(players),m_indexOfPlayerToMove(0),m_indexOfRound(0), m_indexOfMiniround(0)
{
    m_players[m_indexOfPlayerToMove]->setMyMove(true);
}

Game::Game(const Game &other)
    :m_players(PlayerGroup(other.m_players)),
      m_wagons(new Train(other.wagons()->getWagons())),
      m_sheriffPosition(other.m_sheriffPosition),
      m_rounds(new RoundCardDeck(other.m_rounds->getRoundCads())),
      //m_cardsPlayed(std::vector<ActionCard*>()),
      m_neutralBulletDeck(std::vector<NeutralBullet*>()),
      m_unusedTreasure(other.m_unusedTreasure),
      m_mostBulletsShot(other.m_mostBulletsShot),
      m_richestPlayer(other.m_richestPlayer),
      m_indexOfPlayerToMove(other.m_indexOfPlayerToMove),
      m_indexOfRound(other.m_indexOfRound),
      m_indexOfMiniround(other.m_indexOfMiniround),
      m_phase(other.m_phase),
      m_cardsPlayed(new Deck((other.m_cardsPlayed->getCards()))),
      m_currentAction(other.currentAction()),
      m_dialogueBox(new DialogueBox(other.m_dialogueBox->text()))
{
    //Danger players in train and in game are different
    //Only use when train has no players inside
//    for(Player*p:other.m_players)
//        m_players.push_back(new Player(*p));

//    for(RoundCard*rc:other.m_rounds)
//        m_rounds.push_back(new RoundCard(*rc));


//    for(ActionCard*ac:other.m_cardsPlayed)
//        m_cardsPlayed.push_back((ActionCard*)ac->Copy());

    for(NeutralBullet*nb:other.m_neutralBulletDeck)
        m_neutralBulletDeck.push_back((NeutralBullet*)nb->Copy());

//    for(Treasure*t:other.m_unusedTreasure)
//        m_unusedTreasure.push_back(new Treasure(*t));



}

//// Get methods
PlayerGroup &Game::players()
{
    return m_players;
}

Train* Game::wagons() const
{
    return m_wagons;
}

RoundCardDeck* Game::rounds()
{
    return m_rounds;
}



std::vector<NeutralBullet*> Game::neutralBulletDeck() const
{
    return m_neutralBulletDeck;
}

//const std::vector<Treasure> &Game::unusedTreasure() const
//{
//    return m_unusedTreasure;
//}

BanditType Game::mostBulletsShot() const
{
    return m_mostBulletsShot;
}

BanditType Game::richestPlayer() const
{
    return m_richestPlayer;
}

unsigned Game::sheriffPosition() const
{
    return m_sheriffPosition;
}

int Game::getIndexOfPlayerToMove() const
{
    return m_indexOfPlayerToMove;
}

Deck *Game::getCardsPlayed()
{
    return m_cardsPlayed;
}
int Game::indexOfRound() const
{
    return m_indexOfRound;
}

int Game::indexOfMiniround() const
{
    return m_indexOfMiniround;
}

Phase Game::phase() const
{
    return m_phase;
}

bool Game::actionPending() const
{
    return m_actionPending;
}

//// Set methods
//void Game::setPlayers(const std::vector<Player> &newPlayers)
//{
//    m_players = newPlayers;
//}

void Game::setWagons(Train* newWagons)
{
    m_wagons = newWagons;
    //connect(m_wagons,&Train::clickedTreasureInWagonInTrain,this,&Game::onClickedTreasureInWagonInTrainInTran);
}

void Game::setRounds( std::vector<RoundCard*> &newRounds)
{
    m_rounds = new RoundCardDeck(newRounds);
}

//void Game::setCardsPlayed(std::vector<ActionCard*> newCardsPlayed)
//{
//    m_cardsPlayed = newCardsPlayed;
//}

void Game::setNeutralBulletDeck(const std::vector<NeutralBullet*> &newNeutralBulletDeck)
{
    m_neutralBulletDeck = newNeutralBulletDeck;
}

//void Game::setUnusedTreasure(const std::vector<Treasure> &newUnusedTreasure)
//{
//    m_unusedTreasure = newUnusedTreasure;
//}

void Game::setMostBulletsShot(BanditType newMostBulletsShot)
{
    m_mostBulletsShot = newMostBulletsShot;
}

void Game::setRichestPlayer(BanditType newRichestPlayer)
{
    m_richestPlayer = newRichestPlayer;
}

void Game::setSeriffPosition(unsigned newSheriffPosition)
{
    m_sheriffPosition = newSheriffPosition;
}

void Game::setIndexOfPlayerToMove(int nextPlayerIndex)
{
    m_players[m_indexOfPlayerToMove]->setMyMove(false);
    m_indexOfPlayerToMove=nextPlayerIndex;
    m_players[m_indexOfPlayerToMove]->setMyMove(true);
}

void Game::setActionPending(bool newActionPending)
{
    m_actionPending = newActionPending;
}

//// Initialization methods

Train* Game::selectWagons(std::vector<Wagon*> allPossibleWagons, unsigned numberOfPlayers) const
{
    std::vector<Wagon*> selectedWagons ;
    std::sample(allPossibleWagons.begin(), allPossibleWagons.end(), std::back_inserter(selectedWagons),
               numberOfPlayers, std::mt19937_64{std::random_device{}()});
    return new Train(selectedWagons);
}

std::vector<RoundCard*> Game::selectRoundCards(RoundCardType cardType, std::vector<RoundCard*> &allRoundCards) const
{
    std::vector<RoundCard*> cards, result = {};
    std::copy_if(allRoundCards.cbegin(), allRoundCards.cend(),
                 std::back_inserter(cards),
                 [cardType](RoundCard *card) { return card->typeOfRoundCard() == cardType; });

    std::sample(cards.cbegin(), cards.cend(), std::back_inserter(result), 4, std::mt19937_64{std::random_device{}()});

    return result;
}

RoundCard* Game::selectOneTrainStationCard(std::vector<RoundCard*> &allRoundCards)
{
    std::vector<RoundCard*> trainStationCards = {};
    std::copy_if(allRoundCards.cbegin(), allRoundCards.cend(),
                 std::back_inserter(trainStationCards),
                 [](RoundCard *card) { return card->typeOfRoundCard() == RoundCardType::TRAIN_STATION; });

    srand(time(0));
    return trainStationCards[rand() % trainStationCards.size()];
}

std::vector<unsigned> getMoneybags(std::vector<unsigned>& remainingMoneybags, unsigned numberOfMoneybags)
{

    std::vector<unsigned> selectedMoneybags = {};

    for(unsigned i = 0; i < numberOfMoneybags; i++)
    {
        srand(time(0));
        int randomIndex = rand() % remainingMoneybags.size();
        selectedMoneybags.push_back(remainingMoneybags[randomIndex]);
        remainingMoneybags.erase(remainingMoneybags.begin() + randomIndex);
    }

    return selectedMoneybags;
}

std::vector<RoundCard*> generateRoundCards(std::vector<EventType> &events, std::vector<std::vector<MiniRoundType>> &miniRounds)
{
    std::vector<RoundCard*> roundCards = {};
    unsigned numberOfMiniRounds = miniRounds.size();
    unsigned numberOfEvents = events.size();

    for (unsigned i = 0; i < 7; ++i) {
        roundCards.push_back(new RoundCard(RoundCardType::THREE_TO_FOUR_PLAYERS, events[i], miniRounds[i]));
        roundCards.push_back(new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, events[i], miniRounds[i + 7]));
    }

    for (unsigned i = 7; i < numberOfEvents; ++i)
        roundCards.push_back(new RoundCard(RoundCardType::TRAIN_STATION, events[i], miniRounds[numberOfMiniRounds - 1]));

    return roundCards;
}

//std::vector<Treasure*> remainingTreasure(std::vector<unsigned> &remainingMoneybags, unsigned remainingDiamonds, unsigned remainingSuitcases)
//{
//    std::map<unsigned, unsigned> mappedMoneybagValues = {
//        {0, 250},
//        {1, 300},
//        {2, 350},
//        {3, 400},
//        {4, 450},
//        {5, 500}
//    };

//    std::vector<Treasure*> treasure = {};
//    for (unsigned i = 0; i < remainingMoneybags.size(); ++i)
//        treasure.push_back(new Treasure(mappedMoneybagValues[remainingMoneybags[i]], TreasureType::MONEYBAG));

//    treasure.insert(treasure.end(), remainingDiamonds, new Treasure(500, TreasureType::DIAMOND));
//    treasure.insert(treasure.end(), remainingSuitcases, new Treasure(1000, TreasureType::SUITCASE));

//    return treasure;
//}

std::vector<NeutralBullet*> Game::generateNeutralBullets(unsigned numberOfNeutralBullets) const
{
    std::vector<NeutralBullet*> bulletDeck = {};
    for (unsigned i = 0; i < numberOfNeutralBullets; ++i)
        bulletDeck.push_back(new NeutralBullet());
    return bulletDeck;
}

void Game::initialize()
{
    m_cardsPlayed=new Deck();
    unsigned numberOfPlayers = m_players.size();
    shuffleDecks();

    // Treasure
    std::vector<Treasure> allPossibleTreasure;
    allPossibleTreasure.push_back( Treasure(250, TreasureType::MONEYBAG)); //0
    allPossibleTreasure.push_back( Treasure(300, TreasureType::MONEYBAG)); //1
    allPossibleTreasure.push_back( Treasure(350, TreasureType::MONEYBAG)); //2
    allPossibleTreasure.push_back( Treasure(400, TreasureType::MONEYBAG)); //3
    allPossibleTreasure.push_back( Treasure(450, TreasureType::MONEYBAG)); //4
    allPossibleTreasure.push_back( Treasure(500, TreasureType::MONEYBAG)); //5
    //allPossibleTreasure.insert(allPossibleTreasure.end(), 6, new Treasure(500,TreasureType::DIAMOND));
    //allPossibleTreasure.insert(allPossibleTreasure.end(), 2, new Treasure(1000,TreasureType::SUITCASE));

    // Wagons
    std::vector<Wagon*> allPossibleWagons = std::vector<Wagon*>();
    allPossibleWagons.push_back(new Wagon(TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::DIAMOND)}), TreasureChest()));
    allPossibleWagons.push_back(new Wagon(TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::DIAMOND)}), TreasureChest()));
    allPossibleWagons.push_back(new Wagon(TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG)}), TreasureChest()));
    allPossibleWagons.push_back(new Wagon(TreasureChest({new Treasure(TreasureType::MONEYBAG)}), TreasureChest()));
    allPossibleWagons.push_back(new Wagon(TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::DIAMOND)}), TreasureChest()));
    allPossibleWagons.push_back(new Wagon(TreasureChest({new Treasure(TreasureType::DIAMOND), new Treasure(TreasureType::DIAMOND), new Treasure(TreasureType::DIAMOND)}), TreasureChest()));

    Train* selectedWagons = selectWagons(allPossibleWagons, numberOfPlayers);

    // Random value Loot order
    unsigned remainingSuitcases = 2;
    std::vector<unsigned> remainingMoneybags = {0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,5,5};
    std::vector<unsigned> selectedMoneybagsIndexes;
    std::vector<Treasure*> contentDown = {};

    for (unsigned i = 0; i < numberOfPlayers; ++i) {


        int numberOfMoneybags = (*selectedWagons)[i]->numberOfTreasureInWagonDown(TreasureType::MONEYBAG);
        int numberOfDiamonds = (*selectedWagons)[i]->numberOfTreasureInWagonDown(TreasureType::DIAMOND);

//        (*selectedWagons)[i]->clearContentDown();

        selectedMoneybagsIndexes = ::getMoneybags(remainingMoneybags,numberOfMoneybags);

        for (unsigned i = 0; i < numberOfMoneybags; ++i)
            contentDown.push_back(new Treasure(allPossibleTreasure[selectedMoneybagsIndexes[i]]));

        for (unsigned i = 0; i < numberOfDiamonds; ++i)
            contentDown.push_back(new Treasure(500, TreasureType::DIAMOND));

        (*selectedWagons)[i]->setContentDown(contentDown);
        contentDown.clear();
        selectedMoneybagsIndexes.clear();
    }

    // Place Marshal and suitcase in Locomotive
    selectedWagons->push_back(new Wagon(TreasureChest({new Treasure(1000, TreasureType::SUITCASE)}),TreasureChest()));
    m_sheriffPosition = selectedWagons->size() - 1;

    // Set wagons for current game
    setWagons(selectedWagons);

    //Treasure test
    (*m_wagons)[0]->setContentUp(std::vector<Treasure*>());
    (*m_wagons)[0]->addContentUp(new Treasure(250, TreasureType::MONEYBAG));

    // Unused treasure init??
    //setUnusedTreasure(::remainingTreasure(remainingMoneybags, remainingDiamonds, remainingSuitcases));

    // RoundCards
    std::vector<EventType> events = {
        EventType::NONE,
        EventType::ANGRY_MARSHAL,
        EventType::PASSENGERS_REBELLION,
        EventType::BRACKING,
        EventType::TAKE_IT_ALL,
        EventType::SWIVEL_ARM,
        EventType::NONE,
        EventType::PICKPOCKETING,
        EventType::HOSTAGE_TACKING_OF_THE_CONDUCTOR,
        EventType::MARSHALS_REVENGE
    };

    std::vector<std::vector<MiniRoundType>> miniRounds = {
        {MiniRoundType::FACE_UP, MiniRoundType::DOUBLE_CARDS, MiniRoundType::FACE_UP},
        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::OPPOSITE_DIRECTION},
        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::DOUBLE_CARDS, MiniRoundType::FACE_UP},
        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP},

        {MiniRoundType::FACE_UP, MiniRoundType::DOUBLE_CARDS},
        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::OPPOSITE_DIRECTION},
        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::OPPOSITE_DIRECTION},
        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
        {MiniRoundType::FACE_UP, MiniRoundType::DOUBLE_CARDS, MiniRoundType::OPPOSITE_DIRECTION},
        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP},
        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN},

        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP}
    };

    std::vector<RoundCard*> allRoundCards = ::generateRoundCards(events, miniRounds);

    // Random round cards selection
    std::vector<RoundCard*> roundCards = {};
    if (numberOfPlayers >= 3 && numberOfPlayers < 5) {
        roundCards = selectRoundCards(RoundCardType::THREE_TO_FOUR_PLAYERS, allRoundCards);
    } else {
        roundCards = selectRoundCards(RoundCardType::FIVE_TO_SIX_PLAYERS, allRoundCards);
    }

    srand(time(0));
    std::random_shuffle(roundCards.begin(), roundCards.end());
    roundCards.push_back(selectOneTrainStationCard(allRoundCards));

    setRounds(roundCards);

    // Neutral Bullets
    setNeutralBulletDeck(generateNeutralBullets(13));

//    Player*tmp=m_players[0];
//    auto p=new Player(tmp->isItMyMove(),tmp->id(),tmp->hand(),
//                      tmp->deck(),std::vector<BulletCard*>(),tmp->positionInTrain(),tmp->roof(),tmp->treasure());
    //m_wagons->getWagons()[0]->addPlayerDown(p);
    m_indexOfPlayerToMove=0;

    QString text = "WAGON SELECTION PHASE!";
    m_dialogueBox = new DialogueBox(text);
}

void Game::setIndexOfRound(int newIndexOfRound)
{
    m_indexOfRound = newIndexOfRound;
}

void Game::setIndexOfMiniround(int newIndexOfMiniround)
{
    m_indexOfMiniround = newIndexOfMiniround;
}


void Game::setPhase(Phase newPhase)
{
    m_phase = newPhase;
}

void Game::setNextPlayerToMove()
{
    int nextPlayer=(m_indexOfPlayerToMove+1)%m_players.size();
    setIndexOfPlayerToMove(nextPlayer);
}

void Game::allPlayersDrawCards(int n)
{
    for(Player*p:m_players){
        p->drawCards(n);
    }
}



//// Other methods

void Game::shuffleDecks() const
{
    for (Player *player : m_players)
        player->shuffleDeck();
}

void Game::selectBanditPositions()
{
    int position;
    for(auto *player: m_players)
    {
        std::cout << "Choose wagon 0 or 1 for player " << ::toString(player->id())<< "\n";
        while(std::cin >> position)
        {
        if(position == 0 || position == 1)
        {
            player->setPositionInTrain(position);
            break;
        }
        else
            std::cout << "Choose one of the first two wagons!" << "\n";
        }
    }
}

unsigned Game::findPlayerById(BanditType banditId)
{
    unsigned position=0;
    for (unsigned i = 0; i < m_players.size(); ++i)
        if (m_players[i]->id() == banditId)
            position = i;

    return position;
}


int Game::findPlayersTreasureIndex(Treasure *t, unsigned playerIndex)
{
    int treasureIndex = -1;
    for (auto it = m_players[playerIndex]->treasure().cbegin(); it != m_players[playerIndex]->treasure().end(); ++it) {
        if (*it == t) {
            treasureIndex = std::distance(m_players[playerIndex]->treasure().cbegin(), it);
            break;
        }
    }

    return treasureIndex;
}

void Game::checkNextActionCard()
{
    if(this->getCardsPlayed()->empty())
    {
        QString msg = "No more ActionCards to play";
        this->m_dialogueBox->setText(msg);

        RoundCardDeck*rcd=this->rounds();

        // If this was the last round, then the game is over.
        if(rcd->size() - 1 == indexOfRound()) {

            QString msg = "GAME OVER";
            this->m_dialogueBox->setText(msg);

        } else { // If this wasn't the last round, we are moving to the next round.

            this->setIndexOfMiniround(0);
            this->setIndexOfRound(this->indexOfRound() +1);
            RoundCard *rc = rounds()->getRoundCads()[m_indexOfRound];
            //this->rounds()->pop_front();
            delete rc;
            rc = nullptr;
            //this->rounds()->setRoundOnScene(m_indexOfRound);

            QString msg = "Now it's PHASE 1";
            this->m_dialogueBox->setText(msg);

            for(Player* p : this->m_players)
            {
                p->returnCardsToDeck();
                //p->shuffleDeck(); THIS IS NOT WORKING !!!!!!!!!!!!!!!!!!!
                p->drawCards(6);
            }

            this->setIndexOfPlayerToMove(0);

            this->setPhase(Phase::PHASE_1);

        }
        return;
    }

    Card* nextCardForAction = this->getCardsPlayed()->front();
    this->getCardsPlayed()->pop_front();

    QString msg = "Next card for actions is ";
    msg.append(QString::fromStdString(nextCardForAction->toString()));
    this->m_dialogueBox->setText(msg);

    BanditType nextBandit = ((ActionCard*)nextCardForAction)->bandit();
    ActionType nextAction = ((ActionCard*)nextCardForAction)->action();

    this->setIndexOfPlayerToMove(this->findPlayerById(nextBandit));
    this->setCurrentAction(nextAction);

    this->players()[this->m_indexOfPlayerToMove]->deck()->push_back(nextCardForAction);
    nextCardForAction->setFaceUp(false);
}

void Game::setCardsPlayed(Deck *newCardsPlayed)
{
    m_cardsPlayed = newCardsPlayed;
}

void Game::updateRounds()
{
    RoundCardDeck*rcd=this->rounds();

    int iMiniRound=this->indexOfMiniround();
    int iRound=this->indexOfRound();

    qDebug()<<"Round"<<iRound;
    qDebug()<<"MiniRound:"<<iMiniRound;

    // If this is the last miniround and the last player, then the round is over.
    if(iMiniRound==((*rcd)[iRound]->getMiniRounds()).size()-1 &&
            m_indexOfPlayerToMove==this->players().size()-1){

        // Now it's phase 2.
        this->setPhase(Phase::PHASE_2);

        this->checkNextActionCard();


    } else { // If this isn't the last miniround and the last player

        // If this is the last player, then the miniround is over. Moving to the next miniround.
        if(m_indexOfPlayerToMove==this->players().size()-1)
            this->setIndexOfMiniround(iMiniRound+1);
    }
}

void Game::actionChangeWagon(int wagonIndex)
{
    bool isPlayerOnTheRoof = m_players[m_indexOfPlayerToMove]->roof();
    unsigned positionInWagon = m_players[m_indexOfPlayerToMove]->positionInTrain();

    //std::cout << "RELATIVNA UDALJENOST OD PLAYERA: " << std::abs(int(wagonIndex - positionInWagon)) <<"\n";

    if (!isPlayerOnTheRoof && std::abs(int(wagonIndex - positionInWagon)) == 1 )
    {

        m_wagons->getWagons()[positionInWagon]->takePlayerDown(m_players[m_indexOfPlayerToMove]);
        m_wagons->getWagons()[wagonIndex]->addPlayerDown(m_players[m_indexOfPlayerToMove]);

        m_players[m_indexOfPlayerToMove]->setPositionInTrain(wagonIndex);

        return;
    }

    if (isPlayerOnTheRoof && std::abs(int(wagonIndex - positionInWagon)) > 0 && std::abs(int(wagonIndex - positionInWagon)) < 4)
    {
        m_wagons->getWagons()[positionInWagon]->takePlayerUp(m_players[m_indexOfPlayerToMove]);
        m_wagons->getWagons()[wagonIndex]->addPlayerUp(m_players[m_indexOfPlayerToMove]);

        m_players[m_indexOfPlayerToMove]->setPositionInTrain(wagonIndex);

        return;
    }


}

void Game::actionFloorChange()
{
    bool isPlayerOnTheRoof = m_players[m_indexOfPlayerToMove]->roof();
    unsigned positionInWagon = m_players[m_indexOfPlayerToMove]->positionInTrain();

    if (!isPlayerOnTheRoof) {
        m_players[m_indexOfPlayerToMove]->setRoof(!isPlayerOnTheRoof);       
        m_wagons->getWagons()[positionInWagon]->takePlayerDown(m_players[m_indexOfPlayerToMove]);
        m_wagons->getWagons()[positionInWagon]->addPlayerUp(m_players[m_indexOfPlayerToMove]);
    } else {
        if (m_sheriffPosition != m_players[m_indexOfPlayerToMove]->positionInTrain()) {
            m_players[m_indexOfPlayerToMove]->setRoof(!isPlayerOnTheRoof);          
            m_wagons->getWagons()[positionInWagon]->takePlayerUp(m_players[m_indexOfPlayerToMove]);
            m_wagons->getWagons()[positionInWagon]->addPlayerDown(m_players[m_indexOfPlayerToMove]);
        } else {
            NeutralBullet *nb = m_neutralBulletDeck.back();
            m_neutralBulletDeck.pop_back();
            nb->setFaceUp(false);
            m_players[m_indexOfPlayerToMove]->deck()->push_back(nb);
        }
    }
}

void Game::actionSheriffMove(Wagon* w)
{
   // Taking sheriff off of wagon with m_sheriffPosition index
   Wagon *w0 = m_wagons->getWagons()[m_sheriffPosition];
   qDebug() << "Sheriff before moving:";
   qDebug() << m_sheriffPosition;
   Sheriff* s = w0->takeSheriffDown();

   // Adding sheriff to wagon w and changing m_sheriffPosition to his index
   w->addSheriffDown(s);
   m_sheriffPosition = m_wagons->getWagonIndex(w);
   qDebug() << "Sheriff after moving:";
   qDebug() << m_sheriffPosition;

   // For every player that's in our wagon w, we push them to the roof
   std::vector<Player*> players = w->getPlayersDown();
   for(Player* player: players) {
       w->takePlayerDown(player);
       w->addPlayerUp(player);
       player->setRoof(true);

       // If neutral bullet deck is not empty, player recieves a neutral bullet in his deck.
       if (!m_neutralBulletDeck.empty()) {
            NeutralBullet *b = m_neutralBulletDeck.back();
            m_neutralBulletDeck.pop_back();
            b->setFaceUp(false);
            player->deck()->push_back(b);
       }

   }

}

// This method returns if current player can shoot player with index playerIndex.
bool Game::actionFire(int playerIndex)
{   // playerIndex is index of a player that's been CLICKED on

    // Shooters' position in train
    unsigned positionInTrain = players()[m_indexOfPlayerToMove]->positionInTrain();
    bool roof = players()[m_indexOfPlayerToMove]->roof();
    qDebug() << positionInTrain;
    qDebug() << playerIndex;

    if(playerIndex == m_indexOfPlayerToMove) {
        // You can't shoot yourself!
        return false;
    }

    // All possible targets will be in this vector
    std::vector<Player*> possibleTargets;

    // If the shooter is not on the roof
    if(!roof) {

        // Wagon left from our shooter -> looking for possible targets
        if(positionInTrain > 0) {

            Wagon *left = m_wagons->getWagons()[positionInTrain-1];
            for(Player* p: left->getPlayersDown()) {
                possibleTargets.push_back(p);
            }
        }
        // Wagon right from out shooter -> looking for possible targets
        if(positionInTrain < m_wagons->size()-1) {

            Wagon *right = m_wagons->getWagons()[positionInTrain+1];
            for(Player* p: right->getPlayersDown()) {
                possibleTargets.push_back(p);
            }
        }
    }
    else { // If the shooter is on the roof

        // All players on the roof are possible targets (for now)
        for(Player *p: m_players) {
            if(p->roof()) {
                possibleTargets.push_back(p);
            }
        }
    }

    // Now we check if CLICKED player is a possible target
    for(Player* p: possibleTargets) {
        if(findPlayerById(p->id()) == playerIndex) {
            // player(playerIndex) recieves a BULLET CARD from playerToMove
            qDebug() << "Someone's been shot!";
            Card *c = players()[m_indexOfPlayerToMove]->bullet_deck()->back();
            players()[m_indexOfPlayerToMove]->bullet_deck()->pop_back();
            c->setFaceUp(false);
            players()[playerIndex]->deck()->push_back(c);
            return true;
        }
    }

    return false;
}

ActionType Game::currentAction() const
{
    return m_currentAction;
}

void Game::setCurrentAction(ActionType newCurrentAction)
{
    m_currentAction = newCurrentAction;
}

DialogueBox *Game::dialogueBox() const
{
    return m_dialogueBox;
}

void Game::setDialogueBox(DialogueBox *newDialogueBox)
{
    m_dialogueBox = newDialogueBox;
}


std::pair<Wagon*, Treasure*> Game::actionRobbery(int treasureIndex, int wagonIndex)
{
    Wagon* wagonToTakeTreasure = (*m_wagons)[wagonIndex];
    Treasure* treasureToTake;

    if (!m_players[m_indexOfPlayerToMove]->roof()) {
        if (wagonToTakeTreasure->getContentDown().empty()) {
            qDebug() << "You can't take treasure from this wagon!";
            setNextPlayerToMove();
        }

        treasureToTake = wagonToTakeTreasure->getContentDown()[treasureIndex];
    } else {
        if (wagonToTakeTreasure->getContentUp().empty()) {
            qDebug() << "You can't take treasure from this wagon!";
            setNextPlayerToMove();
        }

        treasureToTake = wagonToTakeTreasure->getContentUp()[treasureIndex];
    }

    return {wagonToTakeTreasure, treasureToTake};
}

std::pair<Wagon*, Treasure*> Game::actionPunch(int treasureIndex, int wagonIndex, int playerIndex)
{
    if (m_players[playerIndex]->treasure().empty()) {
        qDebug() << "Choose another player to punch!";
        setNextPlayerToMove();
    }

    Treasure *treasure = m_players[playerIndex]->treasure()[treasureIndex];
    Wagon *wagon = (*m_wagons)[wagonIndex];

    return {wagon, treasure};
}

