#include "mainwindow.h"
#include "game.h"

#include <QApplication>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

// Actions
void actionMarshal(Game &game);
void actionMove(Game &game, unsigned);
void actionFloorChange(Game &game, unsigned);

void placeBanditsOnTheRoof(Game &game, unsigned);
void printPlayerStat(std::vector<Player*> players);

unsigned chooseNewPositionForMarshal();
unsigned chooseNewPositionInTrain(int, int, int);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    w.show();
    return a.exec();

    // Create n number of players

    std::vector<Player*> players;
    players = {
        new Player(BanditType::PICKPOCKET),
        new Player(BanditType::SEDUCTRESS),
        new Player(BanditType::STUDENT),
//        new Player(BanditType::RETIREE),
//        new Player(BanditType::HOMELESS_MAN),
//        new Player(BanditType::BUSINESS_WOMAN)
    };

    // Create the Games
    Game game(players);
    game.initialize();

    // Each player selects one the first 2 wagons to place their character
    game.selectBanditPositions();

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
    // TEST - end

    // For every roundcard  (round) :

//    for (auto round : game.rounds())
//    {
        // For every miniRound

//        for (auto *miniround :(*round) )
//        {
            // PHASE 1:

            // For every player:
//            for (auto player: game.players())
//            {
                // Draw cards


                // option1: draw 3 cards
                // option2: play card from hand
//            }
        game.setCardsPlayed({
                           new ActionCard(ActionType::FLOOR_CHANGE, BanditType::PICKPOCKET),
                           new ActionCard(ActionType::MARSHAL, BanditType::SEDUCTRESS),
                           new ActionCard(ActionType::MOVE, BanditType::STUDENT),
//                                 new ActionCard(ActionType::PUNCH, BanditType::RETIREE),
//                           new ActionCard(ActionType::MARSHAL, BanditType::HOMELESS_MAN),
//                                 new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN),
//                            new ActionCard(ActionType::MOVE, BanditType::PICKPOCKET),
//                                  new ActionCard(ActionType::PUNCH, BanditType::SEDUCTRESS),
//                            new ActionCard(ActionType::FLOOR_CHANGE, BanditType::STUDENT),
//                            new ActionCard(ActionType::FLOOR_CHANGE, BanditType::RETIREE),
//                            new ActionCard(ActionType::MARSHAL, BanditType::HOMELESS_MAN),
//                                  new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN),
                          });


            // PHASE 2:

            // For every card played:
            // print list of valid moves
            // If action possible (list not empty):
                // Player chooses and plays the move
        for (auto *card : game.cardsPlayed()) {
            ActionType action = card->action();
            BanditType bandit = card->bandit();

            unsigned position = game.findPlayerById(bandit);
            std::cout << ::toString(bandit) << " is on the move!" << std::endl;

            if (action == ActionType::FLOOR_CHANGE) {
                actionFloorChange(game, position);
                std::cout << ::toString(bandit) << " changes floor!" << std::endl;
                std::cout << "#### STATS ####" << std::endl;
                printPlayerStat(game.players());
                std::cout << "###############" << std::endl;
            } else if (action == ActionType::MARSHAL) {
                actionMarshal(game);
                std::cout << "Marshal's new position: " << std::to_string(game.sheriffPosition()) << std::endl;
                std::cout << "#### STATS ####" << std::endl;
                printPlayerStat(game.players());
                std::cout << "###############" << std::endl;
            } else if (action == ActionType::MOVE) {
                actionMove(game, position);
                std::cout << "#### STATS ####" << std::endl;
                printPlayerStat(game.players());
                std::cout << "###############" << std::endl;
            } else {
                continue;
            }
        }
//        }
//    }

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

// Actions
void actionFloorChange(Game &game, unsigned position)
{
    bool isPlayerOnTheRoof = game.players()[position]->roof();
    BanditType banditId = game.players()[position]->id();

    if (!isPlayerOnTheRoof) {
        game.players()[position]->setRoof(!isPlayerOnTheRoof);
    } else {
        if (game.sheriffPosition() != game.players()[position]->positionInTrain()) {
            game.players()[position]->setRoof(!isPlayerOnTheRoof);
        } else {
            game.players()[position]->deck()->push_back(new NeutralBullet(banditId));
            game.neutralBulletDeck().pop_back();
        }
    }
}

void actionMarshal(Game &game)
{
    unsigned newMarshalPosition = chooseNewPositionForMarshal();
    game.setSeriffPosition(newMarshalPosition);

    placeBanditsOnTheRoof(game, newMarshalPosition);
}

void actionMove(Game &game, unsigned position)
{
    unsigned newPosition;
    if (!game.players()[position]->roof()) {
        newPosition = chooseNewPositionInTrain(game.players()[position]->positionInTrain(), (*game.wagons()).size(), 1);
        std::cout << ::toString(game.players()[position]->id()) << " moves to position: " << std::to_string(newPosition) << std::endl;
        game.players()[position]->setPositionInTrain(newPosition);
    } else {
        newPosition = chooseNewPositionInTrain(game.players()[position]->positionInTrain(), (*game.wagons()).size(), 3);
        std::cout << ::toString(game.players()[position]->id()) << " moves to position: " <<  std::to_string(newPosition) << std::endl;
        game.players()[position]->setPositionInTrain(newPosition);
    }
}

unsigned chooseNewPositionInTrain(int currentPosition, int numberOfWagons, int numberOfSteps)
{
    unsigned newPosition;

    int maxLeft = std::max(0, currentPosition - numberOfSteps);
    int maxRight = std::min(currentPosition + numberOfSteps, numberOfWagons - 1);

    std::cout << "Enter new position in train! (choose number between " << maxLeft << " and " << maxRight << ")" << std::endl;
    std::cout << "You can't stay at your current position: " << std::to_string(currentPosition) << std::endl;

    std::cin >> newPosition;

    return newPosition;
}

unsigned chooseNewPositionForMarshal()
{
    unsigned newPosition;
    std::cout << "Enter new position for Marshal (choose wisely, Marshal can't be on the roof)!" << std::endl;
    std::cin >> newPosition;

    return newPosition;
}

void placeBanditsOnTheRoof(Game &game, unsigned marshalPosition)
{
    for (auto *player : game.players()) {
        if (!player->roof() && player->positionInTrain() == marshalPosition) {
            player->setRoof(!player->roof());
            player->deck()->push_back(new NeutralBullet(player->id()));
            game.neutralBulletDeck().pop_back();
        }
    }
}

void printPlayerStat(std::vector<Player*> players)
{
    for (auto *player : players)
        std::cout << player->toString() << std::endl;
}
