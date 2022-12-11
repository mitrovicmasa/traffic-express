#include "mainwindow.h"
#include "game.h"

#include <QApplication>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.showFullScreen();
    w.show();
    return a.exec();

    // Create n number of players

    std::vector<Player*> players;
    players = {
        new Player(BanditType::PICKPOCKET),
        new Player(BanditType::SEDUCTRESS),
        new Player(BanditType::STUDENT),
        new Player(BanditType::RETIREE),
        new Player(BanditType::HOMELESS_MAN),
        new Player(BanditType::BUSINESS_WOMAN)
    };

    // Create the Games
    Game game(players);
    game.initialize();

    // Each player selects one the first 2 wagons to place their character
//    game.selectBanditPositions();

    //// TEST - start
//    std::cout << "--- PLAYERS ---" << std::endl;
//    for (auto *player : game.players())
//        std::cout << player->toString() << std::endl;
//    std::cout << "------------------------------------" << std::endl;

//    std::cout << "--- WAGONS ---" << std::endl;
//    for (auto *wagon : *game.wagons())
//        std::cout << wagon->toString() << std::endl;

//    std::cout << "------------------------------------" << std::endl;

//    std::cout << "--- ROUND CARDS ---" << std::endl;
//    for (auto *roundCard : game.rounds())
//        std::cout << roundCard->toString() << std::endl;
    //// TEST - end

    // For every roundcard  (round) :

    for (auto round : game.rounds())
    {
        // For every miniRound

        for (auto miniround : round->miniRound() )
        {
            // PHASE 1:

            // For every player:
            for (auto player: game.players())
            {
                // Draw cards


                // option1: draw 3 cards
                // option2: play card from hand
            }


            // PHASE 2:

            // For every card played:
            // print list of valid moves
            // If action possible (list not empty):
                // Player chooses and plays the move
        }
    }

    // Create printGameState function

    // ToDo:
        // Player special  abilities
        // Round card effects
        // Rang list
        // Timer

//    Wagon w;
//    w.addContentDown(new Treasure());
//    std::cout<<w.toString()<<std::endl<<w.numberOfTreasureInWagonDown(TreasureType::MONEYBAG)<<std::endl;

//    w.takeContentDown(TreasureType::MONEYBAG);
//    std::cout<<w.toString()<<std::endl<<w.numberOfTreasureInWagonDown(TreasureType::MONEYBAG)<<std::endl;

    return 0;
}
