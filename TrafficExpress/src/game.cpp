#include "../headers/game.h"

//// Constructors
//Game::Game()
//{

//}

//Game::Game(const std::vector<Player> &players)
//    : m_players(players)
//{}

//Game::Game(const std::vector<Player> &players, const std::vector<Wagon> &wagons, unsigned sheriffPosition,
//           const std::vector<RoundCard *> &rounds, const std::vector<ActionCard *> &cardsPlayed,
//           const std::vector<Treasure> &unusedTreasure, BanditType mostBulletsShot, BanditType richestPlayer)
//{}

//// Get methods
//const std::vector<Player> &Game::players() const
//{
//    return m_players;
//}

//const std::vector<Wagon> &Game::wagons() const
//{
//    return m_wagons;
//}

//const std::vector<RoundCard*> &Game::rounds() const
//{
//    return m_rounds;
//}

//const std::vector<ActionCard*> &Game::cardsPlayed() const
//{
//    return m_cardsPlayed;
//}

//const std::vector<NeutralBullet> &Game::neutralBulletDeck() const
//{
//    return m_neutralBulletDeck;
//}

//const std::vector<Treasure> &Game::unusedTreasure() const
//{
//    return m_unusedTreasure;
//}

//BanditType Game::mostBulletsShot() const
//{
//    return m_mostBulletsShot;
//}

//BanditType Game::richestPlayer() const
//{
//    return m_richestPlayer;
//}

//// Set methods
//void Game::setPlayers(const std::vector<Player> &newPlayers)
//{
//    m_players = newPlayers;
//}

//void Game::setWagons(const std::vector<Wagon> &newWagons)
//{
//    m_wagons = newWagons;
//}

//void Game::setRounds(const std::vector<RoundCard*> &newRounds)
//{
//    m_rounds = newRounds;
//}

//void Game::setCardsPlayed(const std::vector<ActionCard*> &newCardsPlayed)
//{
//    m_cardsPlayed = newCardsPlayed;
//}

//void Game::setNeutralBulletDeck(const std::vector<NeutralBullet> &newNeutralBulletDeck)
//{
//    m_neutralBulletDeck = newNeutralBulletDeck;
//}

//void Game::setUnusedTreasure(const std::vector<Treasure> &newUnusedTreasure)
//{
//    m_unusedTreasure = newUnusedTreasure;
//}

//void Game::setMostBulletsShot(BanditType newMostBulletsShot)
//{
//    m_mostBulletsShot = newMostBulletsShot;
//}

//void Game::setRichestPlayer(BanditType newRichestPlayer)
//{
//    m_richestPlayer = newRichestPlayer;
//}

//// Initialization methods

//std::vector<Wagon> Game::selectWagons(std::vector<Wagon> &allPossibleWagons, unsigned numberOfPlayers) const
//{
//    std::vector<Wagon> selectedWagons = {};
//    std::sample(allPossibleWagons.begin(), allPossibleWagons.end(), std::back_inserter(selectedWagons),
//               numberOfPlayers, std::mt19937_64{std::random_device{}()});
//    return selectedWagons;
//}
//std::vector<RoundCard*> Game::selectRoundCards(RoundCardType cardType, std::vector<RoundCard*> &allRoundCards) const
//{
//    std::vector<RoundCard*> cards, result = {};
//    std::copy_if(allRoundCards.cbegin(), allRoundCards.cend(),
//                 std::back_inserter(cards),
//                 [cardType](auto *card) { return card->type() == cardType; });

//    std::sample(cards.cbegin(), cards.cend(), std::back_inserter(result), 4, std::mt19937_64{std::random_device{}()});

//    return result;
//}
//RoundCard* Game::selectOneTrainStationCard(std::vector<RoundCard*> &allRoundCards)
//{
//    std::vector<RoundCard*> trainStationCards = {};
//    std::copy_if(allRoundCards.cbegin(), allRoundCards.cend(),
//                 std::back_inserter(trainStationCards),
//                 [](auto *card) { return card->type() == RoundCardType::TRAIN_STATION; });

//    srand(time(0));
//    return trainStationCards[rand() % trainStationCards.size()];
//}
//std::vector<unsigned> getMoneybags(std::vector<unsigned>& remainingMoneybags, unsigned numberOfMoneybags)
//{

//    std::vector<unsigned> selectedMoneybags = {};

//    for(unsigned i = 0; i < numberOfMoneybags; i++)
//    {
//        srand(time(0));
//        int randomIndex = rand() % remainingMoneybags.size();
//        selectedMoneybags.push_back(remainingMoneybags[randomIndex]);
//        remainingMoneybags.erase(remainingMoneybags.begin() + randomIndex);
//    }

//    return selectedMoneybags;
//}
//std::vector<RoundCard*> generateRoundCards(std::vector<EventType> &events, std::vector<std::vector<MiniRoundType>> &miniRounds)
//{
//    std::vector<RoundCard*> roundCards = {};
//    unsigned numberOfMiniRounds = miniRounds.size();
//    unsigned numberOfEvents = events.size();

//    for (unsigned i = 0; i < 7; ++i) {
//        roundCards.push_back(new RoundCard(RoundCardType::THREE_TO_FOUR_PLAYERS, events[i], miniRounds[i]));
//        roundCards.push_back(new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, events[i], miniRounds[i + 7]));
//    }

//    for (unsigned i = 7; i < numberOfEvents; ++i)
//        roundCards.push_back(new RoundCard(RoundCardType::TRAIN_STATION, events[i], miniRounds[numberOfMiniRounds - 1]));

//    return roundCards;
//}
//std::vector<Treasure> remainingTreasure(std::vector<unsigned> &remainingMoneybags, unsigned remainingDiamonds, unsigned remainingSuitcases)
//{
//    std::map<unsigned, unsigned> mappedMoneybagValues = {
//        {0, 250},
//        {1, 300},
//        {2, 350},
//        {3, 400},
//        {4, 450},
//        {5, 500}
//    };

//    std::vector<Treasure> treasure = {};
//    for (unsigned i = 0; i < remainingMoneybags.size(); ++i)
//        treasure.push_back(Treasure(mappedMoneybagValues[remainingMoneybags[i]], TreasureType::MONEYBAG));

//    treasure.insert(treasure.end(), remainingDiamonds, Treasure(500, TreasureType::DIAMOND));
//    treasure.insert(treasure.end(), remainingSuitcases, Treasure(1000, TreasureType::SUITCASE));

//    return treasure;
//}
//std::vector<NeutralBullet> Game::generateNeutralBullets(unsigned numberOfNeutralBullets) const
//{
//    std::vector<NeutralBullet> bulletDeck = {};
//    for (unsigned i = 0; i < numberOfNeutralBullets; ++i)
//        bulletDeck.push_back(NeutralBullet());
//    return bulletDeck;
//}

//void Game::initialize()
//{
//    unsigned numberOfPlayers = m_players.size();
//    shuffleDecks();

//    // Treasure
//    std::vector<Treasure> allPossibleTreasure;
//    allPossibleTreasure.push_back({Treasure(250,TreasureType::MONEYBAG)}); //0
//    allPossibleTreasure.push_back({Treasure(300,TreasureType::MONEYBAG)}); //1
//    allPossibleTreasure.push_back({Treasure(350,TreasureType::MONEYBAG)}); //2
//    allPossibleTreasure.push_back({Treasure(400,TreasureType::MONEYBAG)}); //3
//    allPossibleTreasure.push_back({Treasure(450,TreasureType::MONEYBAG)}); //4
//    allPossibleTreasure.push_back({Treasure(500,TreasureType::MONEYBAG)}); //5
//    allPossibleTreasure.insert(allPossibleTreasure.end(), 6, {Treasure(500,TreasureType::DIAMOND)});
//    allPossibleTreasure.insert(allPossibleTreasure.end(), 2, {Treasure(1000,TreasureType::SUITCASE)});

//    // Wagons
//    std::vector<Wagon> allPossibleWagons = {
//        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
//        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
//        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG}, {}),
//        Wagon({TreasureType::MONEYBAG}, {}),
//        Wagon({TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
//        Wagon({TreasureType::DIAMOND, TreasureType::DIAMOND, TreasureType::DIAMOND}, {})
//    };

//    std::vector<Wagon> selectedWagons = selectWagons(allPossibleWagons, numberOfPlayers);

//    // Random value Loot order
//    unsigned remainingDiamonds = 6;
//    unsigned remainingSuitcases = 2;
//    std::vector<unsigned> remainingMoneybags = {0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,5,5};
//    std::vector<unsigned> selectedMoneybagsIndexes;
//    std::vector<Treasure> contentDown = {};

//    for (unsigned i = 0; i < numberOfPlayers; ++i) {


//        int numberOfMoneybags = selectedWagons[i].numberOfTreasureInWagon(TreasureType::MONEYBAG);
//        int numberOfDiamonds = selectedWagons[i].numberOfTreasureInWagon(TreasureType::DIAMOND);

//        selectedWagons[i].clearContentDown();

//        selectedMoneybagsIndexes = ::getMoneybags(remainingMoneybags,numberOfMoneybags);

//        for (unsigned i = 0; i < numberOfMoneybags; ++i)
//            contentDown.push_back(allPossibleTreasure[selectedMoneybagsIndexes[i]]);

//        for (unsigned i = 0; i < numberOfDiamonds; ++i)
//            contentDown.push_back(Treasure(500, TreasureType::DIAMOND));

//        remainingDiamonds -= numberOfDiamonds;

//        selectedWagons[i].setContentDown(contentDown);

//        contentDown.clear();
//        selectedMoneybagsIndexes.clear();
//    }

//    // Place Marshal and suitcase in Locomotive
//    selectedWagons.push_back(Wagon({Treasure(1000, TreasureType::SUITCASE)},{}));
//    remainingSuitcases -= 1;
//    m_sheriffPosition = selectedWagons.size() - 1;

//    // Set wagons for current game
//    setWagons(selectedWagons);

//    // Unused treasure init??
//    //setUnusedTreasure(::remainingTreasure(remainingMoneybags, remainingDiamonds, remainingSuitcases));

//    // RoundCards
//    std::vector<EventType> events = {
//        EventType::NONE,
//        EventType::ANGRY_MARSHAL,
//        EventType::PASSENGERS_REBELLION,
//        EventType::BRACKING,
//        EventType::TAKE_IT_ALL,
//        EventType::SWIVEL_ARM,
//        EventType::NONE,
//        EventType::PICKPOCKETING,
//        EventType::HOSTAGE_TACKING_OF_THE_CONDUCTOR,
//        EventType::MARSHALS_REVENGE
//    };

//    std::vector<std::vector<MiniRoundType>> miniRounds = {
//        {MiniRoundType::FACE_UP, MiniRoundType::DOUBLE_CARDS, MiniRoundType::FACE_UP},
//        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::OPPOSITE_DIRECTION},
//        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
//        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
//        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::DOUBLE_CARDS, MiniRoundType::FACE_UP},
//        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
//        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP},

//        {MiniRoundType::FACE_UP, MiniRoundType::DOUBLE_CARDS},
//        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::OPPOSITE_DIRECTION},
//        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::OPPOSITE_DIRECTION},
//        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::FACE_UP},
//        {MiniRoundType::FACE_UP, MiniRoundType::DOUBLE_CARDS, MiniRoundType::OPPOSITE_DIRECTION},
//        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP},
//        {MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN},

//        {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::FACE_UP}
//    };

//    std::vector<RoundCard*> allRoundCards = ::generateRoundCards(events, miniRounds);

//    // Random round cards selection
//    std::vector<RoundCard*> roundCards = {};
//    if (numberOfPlayers >= 3 && numberOfPlayers < 5) {
//        roundCards = selectRoundCards(RoundCardType::THREE_TO_FOUR_PLAYERS, allRoundCards);
//    } else {
//        roundCards = selectRoundCards(RoundCardType::FIVE_TO_SIX_PLAYERS, allRoundCards);
//    }

//    srand(time(0));
//    std::random_shuffle(roundCards.begin(), roundCards.end());
//    roundCards.push_back(selectOneTrainStationCard(allRoundCards));

//    setRounds(roundCards);

//    // Neutral Bullets
//    setNeutralBulletDeck(generateNeutralBullets(13));
//}

//// Other methods

//void Game::shuffleDecks() const
//{
//    for (Player player : m_players)
//        player.shuffleDeck();
//}

//void Game::selectBanditPositions()
//{
//    int position;
//    for(auto player: m_players)
//    {
//        std::cin >> position;
//        player.setPositionInTrain(position);

//    }
//}





