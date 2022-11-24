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




























