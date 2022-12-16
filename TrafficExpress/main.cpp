#include "mainwindow.h"
#include "game.h"

#include <QApplication>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>
#include <algorithm>

// Actions
void actionMarshal(Game &game);
void actionMove(Game &game, unsigned);
void actionPunch(Game &game, unsigned);
void actionRobbery(Game &game, unsigned);
void actionFloorChange(Game &game, unsigned);

void placeBanditsOnTheRoof(Game &game, unsigned);
void printPlayerStat(std::vector<Player*> players);

unsigned chooseNewPositionForMarshal();
unsigned chooseNewPositionInTrain(int, int, int);
unsigned chooseTreasureToTake(std::vector<Treasure*> content);

BanditType chooseBanditToPunch(std::vector<BanditType> bandits);
std::vector<BanditType> getPossibleTargets(std::vector<Player*> players, BanditType, unsigned, bool);
std::vector<Treasure*> getWagonContent(Train* wagons, unsigned, bool);

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.showFullScreen();
//    w.show();
//    return a.exec();

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
    //game.selectBanditPositions();


   // TEST - INIT
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

    for (auto round : game.rounds())
    {
         //For every miniRound

        for (auto *miniround :(*round) )
        {
            // DRAW PHASE

            for (auto player: game.players())
            {
                player->returnCardsToDeck();
                player->shuffleDeck();
                player->drawCards(6);

            }

            //PHASE 1:

             //For every player:

            std::vector<ActionCard*> cardsPlayed;

            for (auto player: game.players())
            {
                std::cout << player->toString() << std::endl;

                std::cout << "Select option 1 or 2 \n";
                unsigned option;
                std::cin >> option;

                if (option == 1)
                {
                    player->drawCards(3);
                }
                if (option == 2)
                {
                    std::cout << "Select index of desired card:" << "\n";
                    unsigned ind;
                    std::cin >> ind;

                    //std::cout << player->hand()->at(ind)->toString() << "\n";
                    cardsPlayed.push_back((ActionCard *)player->hand()->at(ind));
                }
                 //option2: play card from hand
            }

            game.setCardsPlayed(cardsPlayed);

//            std::cout << "PLAYED CARDS";
//            for(auto card: cardsPlayed)
//                std::cout << card->toString() << "\n";

//        game.setCardsPlayed({
//                           new ActionCard(ActionType::MOVE, BanditType::PICKPOCKET),
//                           new ActionCard(ActionType::MARSHAL, BanditType::SEDUCTRESS),
//                           new ActionCard(ActionType::ROBBERY, BanditType::STUDENT),
//                                 new ActionCard(ActionType::PUNCH, BanditType::PICKPOCKET),
//                           new ActionCard(ActionType::MARSHAL, BanditType::HOMELESS_MAN),
//                                 new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN),
//                            new ActionCard(ActionType::MOVE, BanditType::PICKPOCKET),
//                                  new ActionCard(ActionType::PUNCH, BanditType::SEDUCTRESS),
//                            new ActionCard(ActionType::FLOOR_CHANGE, BanditType::STUDENT),
//                            new ActionCard(ActionType::FLOOR_CHANGE, BanditType::RETIREE),
//                            new ActionCard(ActionType::MARSHAL, BanditType::HOMELESS_MAN),
//                                  new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN),
//                          });


            // PHASE 2:

            // For every card played:
            // print list of valid moves
            // If action possible (list not empty):
                // Player chooses and plays the move

//        for (auto *card : game.cardsPlayed()) {
//            ActionType action = card->action();
//            BanditType bandit = card->bandit();

//            unsigned position = game.findPlayerById(bandit);
//            std::cout << ::toString(bandit) << " is on the move!" << std::endl;

//            if (action == ActionType::FLOOR_CHANGE) {
//                actionFloorChange(game, position);
//                std::cout << ::toString(bandit) << " changes floor!" << std::endl;
//                std::cout << "#### STATS ####" << std::endl;
//                printPlayerStat(game.players());
//                std::cout << "###############" << std::endl;
//            } else if (action == ActionType::MARSHAL) {
//                actionMarshal(game);
//                std::cout << "Marshal's new position: " << std::to_string(game.sheriffPosition()) << std::endl;
//                std::cout << "#### STATS ####" << std::endl;
//                printPlayerStat(game.players());
//                std::cout << "###############" << std::endl;
//            } else if (action == ActionType::MOVE) {
//                actionMove(game, position);
//                std::cout << "#### STATS ####" << std::endl;
//                printPlayerStat(game.players());
//                std::cout << "###############" << std::endl;
//            } else if (action == ActionType::PUNCH) {
//                actionPunch(game, position);
//                std::cout << "#### STATS ####" << std::endl;
//                printPlayerStat(game.players());
//                std::cout << "###############" << std::endl;
//            } else if (action == ActionType::ROBBERY) {
//                actionRobbery(game, position);
//                std::cout << "#### STATS ####" << std::endl;
//                printPlayerStat(game.players());
//                std::cout << "###############" << std::endl;
//            } else {
//                continue;
//            }
//        }
        }
    }



    // ToDo:

        // Rang list

        // Player special  abilities
        // Round card effects
        // Timer


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

void actionPunch(Game &game, unsigned position)
{
    unsigned currentPositionInTrain = game.players()[position]->positionInTrain();
    BanditType bandit = game.players()[position]->id();

    std::vector<BanditType> possibleTargets = getPossibleTargets(game.players(), bandit, currentPositionInTrain, game.players()[position]->roof());
    if (possibleTargets.empty()) {
        std::cout << "Better luck next time!" << std::endl;
        return;
    }

    BanditType target = chooseBanditToPunch(possibleTargets);

    unsigned banditsPosition = game.findPlayerById(target);

    if (game.players()[banditsPosition]->treasure().empty()) {
        std::cout << "Better luck next time!" << std::endl;
        return;
    }

    unsigned treasureIdx = chooseTreasureToTake(game.players()[banditsPosition]->treasure());
    if (game.players()[position]->roof()) {
        (*game.wagons())[currentPositionInTrain]->addContentUp(game.players()[banditsPosition]->treasure()[treasureIdx]);
    } else {
        (*game.wagons())[currentPositionInTrain]->addContentDown(game.players()[banditsPosition]->treasure()[treasureIdx]);
    }

    // TODO: fix removing treasure from vector
//    delete game.players()[banditsPosition]->treasure()[treasureIdx];
//    game.players()[banditsPosition]->treasure()[treasureIdx] = nullptr;

//    game.players()[banditsPosition]->treasure().erase(std::remove(game.players()[banditsPosition]->treasure().begin(),
//                                                                  game.players()[banditsPosition]->treasure().end(), nullptr),
//                                                      game.players()[banditsPosition]->treasure().end());

}

void actionRobbery(Game &game, unsigned position)
{
    unsigned currentPositionInTrain = game.players()[position]->positionInTrain();
    std::vector<Treasure*> content = getWagonContent(game.wagons(), currentPositionInTrain, game.players()[position]->roof());

    if (content.empty()) {
        std::cout << "Better luck next time!" << std::endl;
        return;
    }

    unsigned treasureIdx = chooseTreasureToTake(content);
    if (game.players()[position]->roof()) {
        game.players()[position]->treasure().push_back(content[treasureIdx]);
        // remove treasure from content up
    } else {
        game.players()[position]->treasure().push_back(content[treasureIdx]);
        // remove treasure from content down
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

std::vector<BanditType> getPossibleTargets(std::vector<Player*> players, BanditType banditId, unsigned positionInTrain, bool roof)
{
    std::vector<BanditType> targets = {};
    for (auto *player : players) {
        if (player->roof() == roof && player->positionInTrain() == positionInTrain && player->id() != banditId) {
            targets.push_back(player->id());
        }
    }

    return targets;
}

std::vector<Treasure*> getWagonContent(Train* wagons, unsigned position, bool roof)
{
    std::cout << "Available treasure: " << std::endl;
    if (roof) {
        for (auto treasure : (*wagons)[position]->contentUp()) {
            std::cout << treasure->toString() << std::endl;
        }
        return (*wagons)[position]->contentUp();
    } else {
        for (auto treasure : (*wagons)[position]->contentDown()) {
            std::cout << treasure->toString() << std::endl;
        }
        return (*wagons)[position]->contentDown();
    }
}

unsigned chooseTreasureToTake(std::vector<Treasure*> content)
{
    unsigned treasureIdx;
    std::cout << "Select one treasure to take: " << std::endl;
    for (auto *treasure : content) {
        std::cout << treasure->toString() << std::endl;
    }

    std::cin >> treasureIdx;
    return treasureIdx;
}

BanditType chooseBanditToPunch(std::vector<BanditType> bandits)
{
    unsigned targetIdx;
    std::cout << "Choose one target to punch: (enter index)" << std::endl;
    for (BanditType bandit : bandits)
        std::cout << ::toString(bandit) << std::endl;

    std::cin >> targetIdx;
    return bandits[targetIdx];
}

