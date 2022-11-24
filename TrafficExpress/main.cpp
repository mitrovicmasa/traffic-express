#include "mainwindow.h"
#include "game.h"

#include <QApplication>
#include <iostream>

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

    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    players.push_back(player5);
    players.push_back(player6);

    unsigned numberOfPlayers = players.size();

    // Each player:
    //       Shuffle Action Cards

    player1.shuffleDeck();
    player2.shuffleDeck();
    player3.shuffleDeck();
    player4.shuffleDeck();
    player5.shuffleDeck();
    player6.shuffleDeck();

    std::cout << numberOfPlayers << std::endl;

    // Create Locomotive and n number of wagons: (Locomotive must be first/last in array)
        // 6x Wagons ((3xPurse,1xDiamond),(4xPurse,1xDiamond),(3xPurse),(1xPurse),(1xPurse,1xDiamond),(3xDiamond))
        // 1x Locomotive
    std::vector<Wagon> allPossibleWagons = {
        Wagon(Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::DIAMOND)),
        Wagon(Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::DIAMOND)),
        Wagon(Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::MONEYBAG)),
        Wagon(Treasure(TreasureType::MONEYBAG)),
        Wagon(Treasure(TreasureType::MONEYBAG),Treasure(TreasureType::DIAMOND)),
        Wagon(Treasure(TreasureType::DIAMOND),Treasure(TreasureType::DIAMOND),Treasure(TreasureType::DIAMOND))
        )};

    //        Random Wagon order depending on number of players (Fisher-Yates shuffle)
    //        Place required Loot (of random value each) in the wagons
        // 18x Moneybags (8x250$, 2x300$, 2x350$, 2x400$, 2x450$, 2x500$), 6x Diamonds (5x500$), 2x Suitcase (2x 1000$)
    //        Place Marshall in the Locomotive
    //        Place Suitcase in the Locomotive



    // Randomly draw 4 RoundCards (out of 7) depending on n number of players
        // 17 RoundCards (7x 2-4, 7x 5-6, 3x TrainStation) (EXACT CARD LAYOUTS are attached in the appropriate task)

    // Shuffle selected RoundCards
    // Randomly draw 1 out of 3 TrainStation RoundCard and push to the end of the array

    // Create the Game

    return 0;
}
