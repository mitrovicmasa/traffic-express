#include "mainwindow.h"
#include "game.h"

#include <QApplication>
#include <iostream>
#include <random>

void generateAllTreasure(const int &count, const int &value, TreasureType type, std::vector<Treasure> &treasure);
std::vector<Treasure> getSpecificTreasure(std::vector<Treasure> treasure, TreasureType type);
std::vector<RoundCard*> generateRoundCards(std::vector<EventType> &events, std::vector<std::vector<MiniRoundType>> &miniRounds);
std::vector<RoundCard*> selectRoundCards(RoundCardType type, std::vector<RoundCard*> &allRoundCards);
RoundCard* selectOneTrainStationCard(std::vector<RoundCard*> &allRoundCards);

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();


    //ToDo: Add 13x Neutral Bullet Cards to Game


    // GAME INITIALIZATION


    // Create n number of players

    std::vector<Player> players;

    Player player1 = Player(BanditType::PICKPOCKET);
    Player player2 = Player(BanditType::SEDUCTRESS);
    Player player3 = Player(BanditType::STUDENT);
    Player player4 = Player(BanditType::RETIREE);
    Player player5 = Player(BanditType::HOMELESS_MAN);
    Player player6 = Player(BanditType::BUSINESS_WOMAN);

    players = {player1, player2, player3, player4, player5, player6};
    unsigned numberOfPlayers = players.size();
    std::cout << numberOfPlayers << std::endl;

    // Each player:
    //       Shuffle Action Cards
    for (Player &player : players)
        player.shuffleDeck();

    // 18x Moneybags (8x250$, 2x300$, 2x350$, 2x400$, 2x450$, 2x500$), 6x Diamonds (5x500$), 2x Suitcase (2x 1000$)
    std::vector<Treasure> allPossibleTreasure = {};
    generateAllTreasure(8, 250, TreasureType::MONEYBAG, allPossibleTreasure);
    generateAllTreasure(2, 300, TreasureType::MONEYBAG, allPossibleTreasure);
    generateAllTreasure(2, 350, TreasureType::MONEYBAG, allPossibleTreasure);
    generateAllTreasure(2, 400, TreasureType::MONEYBAG, allPossibleTreasure);
    generateAllTreasure(2, 450, TreasureType::MONEYBAG, allPossibleTreasure);
    generateAllTreasure(2, 500, TreasureType::MONEYBAG, allPossibleTreasure);
    generateAllTreasure(6, 500, TreasureType::DIAMOND, allPossibleTreasure);
    generateAllTreasure(2, 1000, TreasureType::SUITCASE, allPossibleTreasure);

    // Create Locomotive and n number of wagons: (Locomotive must be first/last in array)
        // 6x Wagons ((3xPurse,1xDiamond),(4xPurse,1xDiamond),(3xPurse),(1xPurse),(1xPurse,1xDiamond),(3xDiamond))
        // 1x Locomotive
    std::vector<Wagon> allPossibleWagons = {
        Wagon(),
        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG}, {}),
        Wagon({TreasureType::MONEYBAG}, {}),
        Wagon({TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
        Wagon({TreasureType::DIAMOND, TreasureType::DIAMOND, TreasureType::DIAMOND}, {})
    };

    //        Place required Loot (of random value each) in the wagons
    unsigned numberOfWagons = allPossibleWagons.size();

    std::vector<Treasure> moneybags = {};
    std::vector<Treasure> diamonds = {};
    std::vector<Treasure> contentDown = {};

    for (unsigned i = 1; i < numberOfWagons; ++i) {
        moneybags = getSpecificTreasure(allPossibleTreasure, TreasureType::MONEYBAG);
        diamonds = getSpecificTreasure(allPossibleTreasure, TreasureType::DIAMOND);

        int numberOfMoneybags = allPossibleWagons[i].numberOfTreasureInWagon(TreasureType::MONEYBAG);
        int numberOfDiamonds = allPossibleWagons[i].numberOfTreasureInWagon(TreasureType::DIAMOND);

        std::sample(moneybags.begin(), moneybags.end(), std::back_inserter(contentDown),
                    numberOfMoneybags, std::mt19937_64{std::random_device{}()});

        for (unsigned i = 0; i < numberOfDiamonds; ++i)
            contentDown.push_back(Treasure(500, TreasureType::DIAMOND));

        allPossibleWagons[i].setContentDown(contentDown);

        contentDown.clear();
        moneybags.clear();
        diamonds.clear();
    }

    //        Random Wagon order depending on number of players (Fisher-Yates shuffle)
    std::vector<Wagon> wagons;
    std::sample(allPossibleWagons.cbegin() + 1, allPossibleWagons.cend(), std::back_inserter(wagons),
                numberOfPlayers, std::mt19937_64{std::random_device{}()});

//    for (Wagon &wagon : wagons)
//        std::cout << wagon.toString() << std::endl << std::endl;

    //        Place Marshall in the Locomotive
    //        Place Suitcase in the Locomotive
    allPossibleWagons[0].addContentDown(Treasure(1000, TreasureType::SUITCASE));

    // 17 RoundCards (7x 2-4, 7x 5-6, 3x TrainStation) (EXACT CARD LAYOUTS are attached in the appropriate task)
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

    std::vector<RoundCard*> allRoundCards = generateRoundCards(events, miniRounds);

    // Randomly draw 4 RoundCards (out of 7) depending on n number of players
    std::vector<RoundCard*> roundCards = {};
    if (numberOfPlayers >= 3 && numberOfPlayers < 5) {
        roundCards = selectRoundCards(RoundCardType::THREE_TO_FOUR_PLAYERS, allRoundCards);
    } else {
        roundCards = selectRoundCards(RoundCardType::FIVE_TO_SIX_PLAYERS, allRoundCards);
    }

    // Shuffle selected RoundCards
    srand(time(0));
    std::random_shuffle(roundCards.begin(), roundCards.end());

    // Randomly draw 1 out of 3 TrainStation RoundCard and push to the end of the array
    roundCards.push_back(selectOneTrainStationCard(allRoundCards));

    for (auto *card : roundCards)
        std::cout << card->toString() << std::endl;
    // Create the Game

    return 0;
}

void generateAllTreasure(const int &amount, const int &value, TreasureType type, std::vector<Treasure> &treasure)
{
    for (int i = 0; i < amount; ++i)
        treasure.push_back(Treasure(value, type));
}

std::vector<Treasure> getSpecificTreasure(std::vector<Treasure> treasure, TreasureType type)
{
    std::vector<Treasure> result = {};
    std::copy_if(treasure.begin(), treasure.end(),
                 std::back_inserter(result),
                 [type](auto &t) { return t.getType() == type; });
    return result;
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

std::vector<RoundCard*> selectRoundCards(RoundCardType type, std::vector<RoundCard*> &allRoundCards)
{
    std::vector<RoundCard*> cards, result = {};
    std::copy_if(allRoundCards.cbegin(), allRoundCards.cend(),
                 std::back_inserter(cards),
                 [type](auto *card) { return card->type() == type; });

    std::sample(cards.cbegin(), cards.cend(), std::back_inserter(result), 4, std::mt19937_64{std::random_device{}()});

    return result;
}

RoundCard* selectOneTrainStationCard(std::vector<RoundCard*> &allRoundCards)
{
    std::vector<RoundCard*> trainStationCards = {};
    std::copy_if(allRoundCards.cbegin(), allRoundCards.cend(),
                 std::back_inserter(trainStationCards),
                 [](auto *card) { return card->type() == RoundCardType::TRAIN_STATION; });

    srand(time(0));
    return trainStationCards[rand() % trainStationCards.size()];
}
