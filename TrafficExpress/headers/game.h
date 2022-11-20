#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "wagon.h"
#include "player.h"
#include "roundcard.h"
#include "actioncard.h"

#include <vector>
#include <algorithm>

class Game
{
public:

    // Constructors
    Game();
    Game(const std::vector<Player> &players, const std::vector<Wagon> &wagons, unsigned sheriffPosition,
         const std::vector<RoundCard*> &rounds, const std::vector<ActionCard*> &cardsPlayed,
         const std::vector<Treasure> &unusedTreasure, BanditType mostBulletsShot, BanditType richestPlayer);

    //Get methods
    const std::vector<Player> &players() const;
    const std::vector<Wagon> &wagons() const;
    const std::vector<RoundCard*> &rounds() const;
    const std::vector<ActionCard*> &cardsPlayed() const;
    const std::vector<Treasure> &unusedTreasure() const;
    BanditType mostBulletsShot() const;
    BanditType richestPlayer() const;

    //Set methods
    void setPlayers(const std::vector<Player> &newPlayers);
    void setWagons(const std::vector<Wagon> &newWagons);
    void setRounds(const std::vector<RoundCard*> &newRounds);
    void setCardsPlayed(const std::vector<ActionCard*> &newCardsPlayed);
    void setUnusedTreasure(const std::vector<Treasure> &newUnusedTreasure);
    void setMostBulletsShot(BanditType newMostBulletsShot);
    void setRichestPlayer(BanditType newRichestPlayer);

    //Other methods

    const std::vector<Card> &shuffleDeck(std::vector<Card*> &cards) const;
    const std::vector<Card> &drawCards(unsigned) const;
    std::vector<Card*> drawCards(unsigned numberOfCards, const Player &player) const;
    std::vector<RoundCard*> selectRoundCards() const;
    std::vector<Wagon> selectWagons() const;
    void placeBanditInWagon(unsigned) const;

private:

    std::vector<Player> m_players;
    std::vector<Wagon> m_wagons;
    unsigned m_sheriffPosition;
    std::vector<RoundCard*> m_rounds;
    std::vector<ActionCard*> m_cardsPlayed;
    std::vector<Treasure> m_unusedTreasure;
    BanditType m_mostBulletsShot;
    BanditType m_richestPlayer;
};

#endif // GAME_H
