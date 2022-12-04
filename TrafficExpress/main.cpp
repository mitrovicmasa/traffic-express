#include "mainwindow.h"
#include "game.h"

#include <QApplication>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

void generateAllTreasure(const int &count, const int &value, TreasureType type, std::vector<Treasure> &treasure);
std::vector<unsigned> getMoneybags(std::vector<unsigned>& remainingMoneybags, unsigned numberOfMoneybags);
std::vector<RoundCard*> generateRoundCards(std::vector<EventType> &events, std::vector<std::vector<MiniRoundType>> &miniRounds);
std::vector<RoundCard*> selectRoundCards(RoundCardType type, std::vector<RoundCard*> &allRoundCards);
RoundCard* selectOneTrainStationCard(std::vector<RoundCard*> &allRoundCards);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


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
    unsigned numberOfPlayers = 3; //players.size();
    std::cout << numberOfPlayers << std::endl;

    // Each player:
    //       Shuffle Action Cards
    for (Player &player : players)
        player.shuffleDeck();

    // 18x Moneybags (8x250$, 2x300$, 2x350$, 2x400$, 2x450$, 2x500$), 6x Diamonds (5x500$), 2x Suitcase (2x 1000$)
    std::vector<Treasure> allPossibleTreasure;
    allPossibleTreasure.push_back({Treasure(250,TreasureType::MONEYBAG)}); //0
    allPossibleTreasure.push_back({Treasure(300,TreasureType::MONEYBAG)}); //1
    allPossibleTreasure.push_back({Treasure(350,TreasureType::MONEYBAG)}); //2
    allPossibleTreasure.push_back({Treasure(400,TreasureType::MONEYBAG)}); //3
    allPossibleTreasure.push_back({Treasure(450,TreasureType::MONEYBAG)}); //4
    allPossibleTreasure.push_back({Treasure(500,TreasureType::MONEYBAG)}); //5
    //allPossibleTreasure.insert({Treasure(500,TreasureType::DIAMOND),6});
    //allPossibleTreasure.insert({Treasure(1000,TreasureType::SUITCASE),2});

    // Create Locomotive and n number of wagons: (Locomotive must be first/last in array)
        // 6x Wagons ((3xPurse,1xDiamond),(4xPurse,1xDiamond),(3xPurse),(1xPurse),(1xPurse,1xDiamond),(3xDiamond))
        // 1x Locomotive
    std::vector<Wagon> allPossibleWagons = {
        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
        Wagon({TreasureType::MONEYBAG, TreasureType::MONEYBAG, TreasureType::MONEYBAG}, {}),
        Wagon({TreasureType::MONEYBAG}, {}),
        Wagon({TreasureType::MONEYBAG, TreasureType::DIAMOND}, {}),
        Wagon({TreasureType::DIAMOND, TreasureType::DIAMOND, TreasureType::DIAMOND}, {})
    };

    // Choose n out of 6 wagons

    std::vector<Wagon> selectedWagons = {};
    std::sample(allPossibleWagons.begin(), allPossibleWagons.end(), std::back_inserter(selectedWagons),
               numberOfPlayers, std::mt19937_64{std::random_device{}()});


    // Place required Loot (of random value each) in the wagons


    std::vector<unsigned> remainingMoneybags = {0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,5,5};
    std::vector<unsigned> selectedMoneybagsIndexes;
    std::vector<Treasure> contentDown = {};

    for (unsigned i = 0; i < numberOfPlayers; ++i) {


        int numberOfMoneybags = selectedWagons[i].numberOfTreasureInWagon(TreasureType::MONEYBAG);
        int numberOfDiamonds = selectedWagons[i].numberOfTreasureInWagon(TreasureType::DIAMOND);

        selectedWagons[i].clearContentDown();

        selectedMoneybagsIndexes = getMoneybags(remainingMoneybags,numberOfMoneybags);

        for (unsigned i = 0; i < numberOfMoneybags; ++i)
            contentDown.push_back(allPossibleTreasure[selectedMoneybagsIndexes[i]]);

        for (unsigned i = 0; i < numberOfDiamonds; ++i)
            contentDown.push_back(Treasure(500, TreasureType::DIAMOND));

        selectedWagons[i].setContentDown(contentDown);

        contentDown.clear();
        selectedMoneybagsIndexes.clear();
    }

    //Place Marshall and Suitcase in the Locomotive

    selectedWagons.push_back(Wagon({Treasure(1000, TreasureType::SUITCASE)},{}));

    // Test
    for (Wagon &wagon : selectedWagons)
        std::cout << wagon.toString() << std::endl << std::endl;






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


std::vector<unsigned> getMoneybags(std::vector<unsigned>& remainingMoneybags, unsigned numberOfMoneybags)
{

    std::vector<unsigned> selectedMoneybags;

    for(unsigned i = 0; i<numberOfMoneybags; i++)
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
