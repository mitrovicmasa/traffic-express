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
    w.show();
    return a.exec();

    // Create n number of players

    std::vector<Player> players;

    Player player1 = Player(BanditType::PICKPOCKET);
    Player player2 = Player(BanditType::SEDUCTRESS);
    Player player3 = Player(BanditType::STUDENT);
    Player player4 = Player(BanditType::RETIREE);
    Player player5 = Player(BanditType::HOMELESS_MAN);
    Player player6 = Player(BanditType::BUSINESS_WOMAN);

    players = {player1, player2, player3, player4, player5, player6};

    // Create the Game
    Game game(players);
    game.initialize();

    // Each player selects one the first 2 wagons to place their character

    // For every roundcard (round) :

        // For every miniRound

            // PHASE 1:

            // For every player:
                // Draw cards
                // option1: draw 3 cards
                // option2: play card from hand

            // PHASE 2:

            // For every card played:
            // print list of valid moves
            // If action possible (list not empty):
                // Player chooses and plays the move

    // Create printGameState function

    // ToDo:
        // Player special  abilities
        // Round card effects
        // Rang list
        // Timer
    return 0;
}
