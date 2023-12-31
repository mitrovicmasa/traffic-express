#include "../headers/game.h"
#include <QApplication>
#include <QAbstractButton>
#include <QObject>
//// Constructors
Game::Game()
{

}

Game::Game( std::vector<Player*> &players)
    : m_players(players),m_indexOfPlayerToMove(0),m_indexOfRound(0), m_indexOfMiniround(0)
{
    m_players[m_indexOfPlayerToMove]->setMyMove(true);
}

Game::Game(const Game &other)
    :m_players(PlayerGroup(other.m_players)),
      m_wagons(new Train(other.m_wagons->getWagons())),
      m_sheriffPosition(other.m_sheriffPosition),
      m_rounds(new RoundCardDeck(other.m_rounds->getRoundCards())),
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
      m_dialogueBox(new DialogueBox(other.m_dialogueBox->text())),
      m_seed(other.m_seed)
{
    srand(m_seed);

    for(NeutralBullet*nb:other.m_neutralBulletDeck)
        m_neutralBulletDeck.push_back((NeutralBullet*)nb->Copy());
}

Game::~Game()
{
    for(NeutralBullet*nb:m_neutralBulletDeck){
        delete nb;
    }
}

//// Get methods
PlayerGroup &Game::players()
{
    return m_players;
}

Train* Game::wagons()
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

ActionType Game::currentAction() const
{
    return m_currentAction;
}

DialogueBox *Game::dialogueBox() const
{
    return m_dialogueBox;
}

const unsigned &Game::seed() const
{
    return m_seed;
}

bool Game::actionPending() const
{
    return m_actionPending;
}

void Game::setWagons(Train* newWagons)
{
    m_wagons = newWagons;
}

void Game::setRounds( std::vector<RoundCard*> &newRounds)
{
    m_rounds = new RoundCardDeck(newRounds);
}

void Game::setNeutralBulletDeck(const std::vector<NeutralBullet*> &newNeutralBulletDeck)
{
    m_neutralBulletDeck = newNeutralBulletDeck;
}

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

void Game::setCardsPlayed(Deck *newCardsPlayed)
{
    m_cardsPlayed = newCardsPlayed;
}

void Game::setIndexOfPlayerToMove(int nextPlayerIndex)
{
    m_players[m_indexOfPlayerToMove]->setMyMove(false);
    m_indexOfPlayerToMove=nextPlayerIndex;
    m_players[m_indexOfPlayerToMove]->setMyMove(true);
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

void Game::setActionPending(bool newActionPending)
{
    m_actionPending = newActionPending;
}

void Game::setSeed(const unsigned &newSeed)
{
    m_seed = newSeed;
}

void Game::setCurrentAction(ActionType newCurrentAction)
{
    m_currentAction = newCurrentAction;
}

void Game::setDialogueBox(DialogueBox *newDialogueBox)
{
    m_dialogueBox = newDialogueBox;
}


// Initialization methods

Train* Game::selectWagons(std::vector<Wagon*> allPossibleWagons, unsigned numberOfPlayers) const
{
    std::vector<Wagon*> selectedWagons ;
    std::sample(allPossibleWagons.begin(), allPossibleWagons.end(), std::back_inserter(selectedWagons),
               numberOfPlayers, std::mt19937_64{std::random_device{}()});
    for(Wagon*w:allPossibleWagons){
        if(std::find(selectedWagons.begin(),selectedWagons.end(),w)==allPossibleWagons.end()){
            delete w;
        }
    }
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

std::vector<NeutralBullet*> Game::generateNeutralBullets(unsigned numberOfNeutralBullets) const
{
    std::vector<NeutralBullet*> bulletDeck = {};
    for (unsigned i = 0; i < numberOfNeutralBullets; ++i)
        bulletDeck.push_back(new NeutralBullet());
    return bulletDeck;
}

void Game::initialize()
{
    m_seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(m_seed);

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

    // Wagons
    std::vector<Wagon*> allPossibleWagons = std::vector<Wagon*>();
    auto tc1=TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::DIAMOND)});
    auto tc2=TreasureChest();
    auto tc3=TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::DIAMOND)});
    auto tc4=TreasureChest();
    auto tc5=TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::MONEYBAG)});
    auto tc6=TreasureChest();
    auto tc7=TreasureChest({new Treasure(TreasureType::MONEYBAG)});
    auto tc8=TreasureChest();
    auto tc9=TreasureChest({new Treasure(TreasureType::MONEYBAG), new Treasure(TreasureType::DIAMOND)});
    auto tc10=TreasureChest();
    auto tc11=TreasureChest({new Treasure(TreasureType::DIAMOND), new Treasure(TreasureType::DIAMOND), new Treasure(TreasureType::DIAMOND)});
    auto tc12=TreasureChest();

    allPossibleWagons.push_back(new Wagon(tc1, tc2));
    allPossibleWagons.push_back(new Wagon(tc3, tc4));
    allPossibleWagons.push_back(new Wagon(tc5,tc6 ));
    allPossibleWagons.push_back(new Wagon(tc7,tc8 ));
    allPossibleWagons.push_back(new Wagon(tc9,tc10 ));
    allPossibleWagons.push_back(new Wagon(tc11,tc12 ));

    Train* selectedWagons = selectWagons(allPossibleWagons, numberOfPlayers);

    // Random value Loot order
    unsigned remainingSuitcases = 2;
    std::vector<unsigned> remainingMoneybags = {0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,5,5};
    std::vector<unsigned> selectedMoneybagsIndexes;
    std::vector<Treasure*> contentDown = {};

    for (unsigned i = 0; i < numberOfPlayers; ++i) {


        int numberOfMoneybags = (*selectedWagons)[i]->numberOfTreasureInWagonDown(TreasureType::MONEYBAG);
        int numberOfDiamonds = (*selectedWagons)[i]->numberOfTreasureInWagonDown(TreasureType::DIAMOND);

        selectedMoneybagsIndexes = ::getMoneybags(remainingMoneybags,numberOfMoneybags);

        for (unsigned i = 0; i < numberOfMoneybags; ++i)
            contentDown.push_back(new Treasure(allPossibleTreasure[selectedMoneybagsIndexes[i]]));

        for (unsigned i = 0; i < numberOfDiamonds; ++i)
            contentDown.push_back(new Treasure(500, TreasureType::DIAMOND));

        (*selectedWagons)[i]->setContentDown(contentDown);
        contentDown.clear();
        selectedMoneybagsIndexes.clear();
    }

    for(Wagon *w: selectedWagons->getWagons()) {
        w->setIsLocomotive(false);
        w->repositionTreasure();
    }

    auto tc13=TreasureChest({new Treasure(1000, TreasureType::SUITCASE)});
    auto tc14=TreasureChest();

    // Place Marshal and suitcase in Locomotive
    selectedWagons->push_back(new Wagon(tc13,tc14));
    selectedWagons->back()->setIsLocomotive(true);
    selectedWagons->back()->addSheriffDown(new Sheriff());
    m_sheriffPosition = selectedWagons->size() - 1;

    // Set wagons for current game
    setWagons(selectedWagons);

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
    for(RoundCard*rc:allRoundCards){
        if(std::find(m_rounds->getRoundCards().begin(),m_rounds->getRoundCards().end(),rc)==m_rounds->getRoundCards().end()){
            delete rc;
        }
    }
    setNeutralBulletDeck(generateNeutralBullets(13));

    m_indexOfPlayerToMove=0;

    QString text = "WAGON SELECTION PHASE!";
    m_dialogueBox = new DialogueBox(text);
}

void Game::allPlayersDrawCards(int n)
{
    for(Player*p:m_players){
        p->drawCards(n);
    }
}

// Other methods
void Game::shuffleDecks() const
{
    for(Player *player : m_players)
        player->shuffleDeck(rand());
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

void Game::showEndGameStats()
{
    QMessageBox* msgBox = new QMessageBox();

    std::vector<Player*> sortedPlayers = this->players();
    std::sort(sortedPlayers.begin(),sortedPlayers.end(), [](Player* a, Player* b) { return a->countAmountOfTreasure() > b->countAmountOfTreasure(); } );

    QString msg;
    unsigned ind = 1;

    for(Player* p : sortedPlayers)
    {
        msg.append(QString::number(ind) + ". " + QString::fromStdString(toString((*p).id())) + ": Amount of treasure: " + QString::number(p->countAmountOfTreasure()) );
        msg.append('\n');
        ind++;
    }

    msgBox->setText(msg);
    msgBox->exec();
    QAbstractButton * btn =  msgBox->clickedButton();
    if(btn) {
        QApplication::quit();
    }
}

std::vector<Player *> Game::possiblePlayersToShot(int playerIndex)
{
    Player* p1 = m_players[playerIndex];
    int positionInTrain = p1->positionInTrain();
    int roof = p1->roof();

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
            if(p->roof() && (p->id() != p1->id()) && (p->positionInTrain() != p1->positionInTrain())) {
                possibleTargets.push_back(p);
            }
        }
    }
    return possibleTargets;
}

std::vector<Player *> Game::possiblePlayersToPunch(int playerIndex)
{
    Player* p1 = m_players[playerIndex];
    int positionInTrain = p1->positionInTrain();
    int roof = p1->roof();

    std::vector<Player*> possibleTargets;
    for (auto possibleTarget : m_players) {
        if (possibleTarget->positionInTrain() == positionInTrain && possibleTarget->roof() == roof
            && possibleTarget->id() != p1->id() && !possibleTarget->treasure().empty())
            possibleTargets.push_back(possibleTarget);
    }

    return possibleTargets;
}

std::vector<Treasure *> Game::possibleTreasure(int playerIndex)
{
    Player* p1 = m_players[playerIndex];
    int positionInTrain = p1->positionInTrain();
    int roof = p1->roof();
    Wagon *wagon = (*m_wagons)[positionInTrain];

    std::vector<Treasure*> treasure = {};
    if (roof) {
        for (auto content : wagon->getContentUp()) {
            treasure.push_back(content);
        }
    } else {
        for (auto content : wagon->getContentDown()) {
            treasure.push_back(content);
        }
    }
    return treasure;
}

void Game::checkNextActionCard()
{
    if(this->getCardsPlayed()->empty())
    {
        QString msg = "No more ActionCards to play";
        this->m_dialogueBox->setText(msg);

        // If this was the last round, then the game is over.
        if(indexOfRound()==4) {

            QString msg = "GAME OVER";
            this->m_dialogueBox->setText(msg);
            this->showEndGameStats();

        } else { // If this wasn't the last round, we are moving to the next round.
            this->setIndexOfMiniround(0);
            RoundCard* rc = m_rounds->getRoundCards()[m_indexOfRound];
            rc->setZValue(-1);
            qDebug() << m_indexOfRound;
            this->setIndexOfRound(m_indexOfRound + 1);
            qDebug() << m_indexOfRound;   

            QString msg = "PHASE 1: PICK A CARD FROM YOUR HAND OR DRAW 3 FROM DECK.";
            this->m_dialogueBox->setText(msg);

            for(Player* p : this->m_players)
            {
                p->returnCardsToDeck();
                p->shuffleDeck(this->m_seed);
                p->drawCards(6);
            }

            this->setIndexOfPlayerToMove(0);

            this->setPhase(Phase::PHASE_1);

        }
        return;
    }

    Card* nextCardForAction = this->getCardsPlayed()->front();
    this->getCardsPlayed()->pop_front();

    QString msg = QString::fromStdString(nextCardForAction->toString());
    this->m_dialogueBox->setText(msg);

    BanditType nextBandit = ((ActionCard*)nextCardForAction)->bandit();
    ActionType nextAction = ((ActionCard*)nextCardForAction)->action();

    if(nextAction == ActionType::FIRE) {
        // All possible targets will be in this vector
        std::vector<Player*> possibleTargets = possiblePlayersToShot(findPlayerById(nextBandit));

        // If there are no possible targets, skip this turn & move on to the next ActionCard.
        if(possibleTargets.empty()) {
            qDebug() << "NO POSSIBLE PLAYERS TO SHOOT, SKIPPING THE MOVE!";
            this->players()[findPlayerById(nextBandit)]->deck()->push_back(nextCardForAction);
            nextCardForAction->setFaceUp(false);

            checkNextActionCard();
            return;
        } else {
            //qDebug() << findPlayerById(possibleTargets[0]->id());
            //qDebug() << possibleTargets[0];
        }
    }

    if(nextAction == ActionType::PUNCH) {
        // All possible targets will be in this vector
        std::vector<Player*> possibleTargets = possiblePlayersToPunch(findPlayerById(nextBandit));

        // If there are no possible targets, skip this turn & move on to the next ActionCard.
        if(possibleTargets.empty()) {
            qDebug() << "NO POSSIBLE PLAYERS TO PUNCH, SKIPPING THE MOVE!";
            this->players()[findPlayerById(nextBandit)]->deck()->push_back(nextCardForAction);
            nextCardForAction->setFaceUp(false);

            checkNextActionCard();
            return;
        } else {
            //qDebug() << findPlayerById(possibleTargets[0]->id());
        }
    }

    if(nextAction == ActionType::ROBBERY) {
            // All possible targets will be in this vector
            std::vector<Treasure*> treasure = possibleTreasure(findPlayerById(nextBandit));

            // If there are no possible targets, skip this turn & move on to the next ActionCard.
            if(treasure.empty()) {
                qDebug() << "NO POSSIBLE TREASURE TO TAKE, SKIPPING THE MOVE!";
                this->players()[findPlayerById(nextBandit)]->deck()->push_back(nextCardForAction);
                nextCardForAction->setFaceUp(false);

                checkNextActionCard();
                return;
            } else {
                //qDebug() << treasure[0];
            }
    }

    this->setIndexOfPlayerToMove(this->findPlayerById(nextBandit));
    this->setCurrentAction(nextAction);

    this->players()[this->m_indexOfPlayerToMove]->deck()->push_back(nextCardForAction);
    nextCardForAction->setFaceUp(false);
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

// Actions
bool Game::actionChangeWagon(int wagonIndex)
{
    bool isPlayerOnTheRoof = m_players[m_indexOfPlayerToMove]->roof();
    unsigned positionInWagon = m_players[m_indexOfPlayerToMove]->positionInTrain();

    //std::cout << "RELATIVNA UDALJENOST OD PLAYERA: " << std::abs(int(wagonIndex - positionInWagon)) <<"\n";

    if (!isPlayerOnTheRoof && std::abs(int(wagonIndex - positionInWagon)) == 1 )
    {

        m_wagons->getWagons()[positionInWagon]->takePlayerDown(m_players[m_indexOfPlayerToMove]);

        if (m_sheriffPosition == wagonIndex)
        {
            NeutralBullet *nb = m_neutralBulletDeck.back();
            m_neutralBulletDeck.pop_back();
            nb->setFaceUp(false);
            m_players[m_indexOfPlayerToMove]->deck()->push_back(nb);


            m_wagons->getWagons()[wagonIndex]->addPlayerUp(m_players[m_indexOfPlayerToMove]);

            m_players[m_indexOfPlayerToMove]->setPositionInTrain(wagonIndex);

        }
        else
        {
            m_wagons->getWagons()[wagonIndex]->addPlayerDown(m_players[m_indexOfPlayerToMove]);
            m_players[m_indexOfPlayerToMove]->setPositionInTrain(wagonIndex);
        }

        return true;
    }


    if (isPlayerOnTheRoof && std::abs(int(wagonIndex - positionInWagon)) > 0 && std::abs(int(wagonIndex - positionInWagon)) < 4)
    {
        m_wagons->getWagons()[positionInWagon]->takePlayerUp(m_players[m_indexOfPlayerToMove]);
        m_wagons->getWagons()[wagonIndex]->addPlayerUp(m_players[m_indexOfPlayerToMove]);

        m_players[m_indexOfPlayerToMove]->setPositionInTrain(wagonIndex);

        return true;
    }

    return false;

}

void Game::actionFloorChange()
{
    bool isPlayerOnTheRoof = m_players[m_indexOfPlayerToMove]->roof();
    unsigned positionInWagon = m_players[m_indexOfPlayerToMove]->positionInTrain();

    if (!isPlayerOnTheRoof) {
        m_players[m_indexOfPlayerToMove]->setRoof(isPlayerOnTheRoof);
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

    // Clicked players' position in train
    unsigned positionInTrain2 = players()[playerIndex]->positionInTrain();
    bool roof2 = players()[playerIndex]->roof();

    if(roof != roof2) {
        // You can't shoot yourself someone who is not on the same floor!
        return false;
    }

    if(positionInTrain == positionInTrain2) {
        // You can't shoot yourself someone who is in the same wagon!
        return false;
    }
    // All possible targets will be in this vector
    std::vector<Player*> possibleTargets = possiblePlayersToShot(m_indexOfPlayerToMove);

    // Now we check if clicked player is a possible target
    for(Player* p: possibleTargets) {
       // qDebug() << "Moguci targeti: ";
        //qDebug() << this->findPlayerById(p->id());
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

int Game::playerClicked() const
{
    return m_playerClicked;
}

void Game::setPlayerClicked(int newPlayerClicked)
{
    m_playerClicked = newPlayerClicked;
}

QVariant Game::toVariant() const
{
        QVariantMap map;
        map.insert("p2m",m_indexOfPlayerToMove);
        map.insert("mri",m_indexOfMiniround);
        map.insert("ri",m_indexOfRound);
        map.insert("ca",(int)m_currentAction);

        QVariantList playerList;
        for(Player*p:m_players){
            playerList.append(p->toVariant());
        }
        map.insert("pl",playerList);
        map.insert("train",m_wagons->toVariant());
        map.insert("sPos",m_sheriffPosition);
        map.insert("rcd",m_rounds->toVariant());
        map.insert("cPlayed",m_cardsPlayed->toVariant());

        QVariantList treasureList;
        for(Treasure*t:m_unusedTreasure){
            treasureList.append(t->toVariant());
        }
        map.insert("uTreasure",treasureList);

        map.insert("mBullets",(int)m_mostBulletsShot);
        map.insert("richestPlayer",(int)m_richestPlayer);
        map.insert("phase",(int)m_phase);

        map.insert("aPending",m_actionPending);
        map.insert("pClicked",m_playerClicked);
        map.insert("seed",(int)m_seed);

        return map;
}

void Game::fromVariant(const QVariant &variant)
{
        QVariantMap map=variant.toMap();

        m_indexOfPlayerToMove=map.value("p2m").toInt();
        m_indexOfMiniround=map.value("mri").toInt();
        m_indexOfRound=map.value("ri").toInt();
        m_currentAction=static_cast<ActionType>(map.value("ca").toInt());

        QVariantList playerList=map.value("pl").toList();
        for(auto&p:playerList){
            Player*player=new Player();
            player->fromVariant(p);
            m_players.push_back(player);
        }

          m_wagons=new Train();
          m_wagons->fromVariant(map.value("train"));
          m_sheriffPosition=map.value("sPos").toInt();
          m_rounds=new RoundCardDeck();
          m_rounds->fromVariant(map.value("rcd"));
          m_cardsPlayed=new Deck();
          m_cardsPlayed->fromVariant(map.value("cPlayed"));

        QVariantList treasureList=map.value("uTreasure").toList();
        for(auto&t:treasureList){
            Treasure*tr=new Treasure();
            tr->fromVariant(t);
            m_unusedTreasure.push_back(tr);
        }


        m_mostBulletsShot=static_cast<BanditType>(map.value("mBullets").toInt());
        m_richestPlayer=static_cast<BanditType>(map.value("richestPlayer").toInt());
        m_phase=static_cast<Phase>(map.value("phase").toInt());

        m_actionPending=map.value("aPending").toBool();
        m_playerClicked=map.value("pClicked").toInt();
        m_seed=(unsigned)map.value("seed").toInt();

        srand(m_seed);

        setNeutralBulletDeck(generateNeutralBullets(13));

        m_indexOfPlayerToMove=0;

        QString text = "WAGON SELECTION PHASE!";
        m_dialogueBox = new DialogueBox(text);
}


