#include "../headers/game.h"

// Constructors
Game::Game()
{

}

Game::Game(const std::vector<Player> &players, const std::vector<Wagon> &wagons, unsigned sheriffPosition,
           const std::vector<RoundCard *> &rounds, const std::vector<ActionCard *> &cardsPlayed,
           const std::vector<Treasure> &unusedTreasure, BanditType mostBulletsShot, BanditType richestPlayer)
{}

// Get methods
const std::vector<Player> &Game::players() const
{
    return m_players;
}

const std::vector<Wagon> &Game::wagons() const
{
    return m_wagons;
}

const std::vector<RoundCard*> &Game::rounds() const
{
    return m_rounds;
}

const std::vector<ActionCard*> &Game::cardsPlayed() const
{
    return m_cardsPlayed;
}

const std::vector<Treasure> &Game::unusedTreasure() const
{
    return m_unusedTreasure;
}

BanditType Game::mostBulletsShot() const
{
    return m_mostBulletsShot;
}

BanditType Game::richestPlayer() const
{
    return m_richestPlayer;
}

// Set methods
void Game::setPlayers(const std::vector<Player> &newPlayers)
{
    m_players = newPlayers;
}

void Game::setWagons(const std::vector<Wagon> &newWagons)
{
    m_wagons = newWagons;
}

void Game::setRounds(const std::vector<RoundCard*> &newRounds)
{
    m_rounds = newRounds;
}

void Game::setCardsPlayed(const std::vector<ActionCard*> &newCardsPlayed)
{
    m_cardsPlayed = newCardsPlayed;
}

void Game::setUnusedTreasure(const std::vector<Treasure> &newUnusedTreasure)
{
    m_unusedTreasure = newUnusedTreasure;
}

void Game::setMostBulletsShot(BanditType newMostBulletsShot)
{
    m_mostBulletsShot = newMostBulletsShot;
}

void Game::setRichestPlayer(BanditType newRichestPlayer)
{
    m_richestPlayer = newRichestPlayer;
}



//Other methods

// ToDo:


// CREATE GAME OBJECTS


// 18x Moneybags (8x250$, 2x300$, 2x350$, 2x400$, 2x450$, 2x500$), 6x Diamonds (5x500$), 2x Suitcase (2x 1000$)
// 17 RoundCards (7x 2-4, 7x 5-6, 3x TrainStation) (EXACT CARD LAYOUTS are attached in the appropriate task)
// 6x Wagons ((3xPurse,1xDiamond),(4xPurse,1xDiamond),(3xPurse),(1xPurse),(1xPurse,1xDiamond),(3xDiamond))
// 1x Locomotive
// 13x Neutral Bullet Cards

// For each player:
//  10x ActionCards (2x MOVE, 2x FLOOR_CHANGE, 2x FIRE, 2x TAKETREASURE, 1x PUNCH, 1x MARSHAL   )
//  6x Bullets


// GAME INITIALIZATION


// Create n number of players
// Each player:
//       Shuffle Action Cards
//       250$ Moneybag

// Create Locomotive and n number of wagons: (Locomotive must be first/last in array)
//        Random Wagon order
//        Place required Loot (of random value each) in the wagons
//        Place Marshall in the Locomotive
//        Place Suitcase in the Locomotive

// Randomly draw 4 RoundCards (out of 7) depending on n number of players
// Shuffle selected RoundCards
// Randomly draw 1 out of 3 TrainStation RoundCard and push to the end of the array





























