#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "wagon.h"
#include "player.h"
#include "roundcard.h"
#include "actioncard.h"
#include "neutralbullet.h"
#include "train.h"

#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

class Game
{
public:

    // Constructors
    Game();
    Game(const std::vector<Player*> &players);

    //Get methods
    const std::vector<Player*> &players() const;
    Train *wagons() const;
    const std::vector<RoundCard*> &rounds() const;
    const std::vector<ActionCard*> &cardsPlayed() ;
    std::vector<NeutralBullet*> neutralBulletDeck() const;
    const std::vector<Treasure*> &unusedTreasure() const;
    BanditType mostBulletsShot() const;
    BanditType richestPlayer() const;
    unsigned sheriffPosition() const;

    //Set methods
    void setPlayers(const std::vector<Player*> &newPlayers);
    void setWagons(Train* newWagons);
    void setRounds(const std::vector<RoundCard*> &newRounds);
    void setCardsPlayed(std::vector<ActionCard*> newCardsPlayed);
    void setNeutralBulletDeck(const std::vector<NeutralBullet*> &newNeutralBulletDeck);
    void setUnusedTreasure(const std::vector<Treasure*> &newUnusedTreasure);
    void setMostBulletsShot(BanditType newMostBulletsShot);
    void setRichestPlayer(BanditType newRichestPlayer);
    void setSeriffPosition(unsigned newSheriffPosition);


    // Initialization methods

    const std::vector<Card*> &drawCards(unsigned) const;
    std::vector<Card*> drawCards(unsigned numberOfCards, const Player* &player) const;
    std::vector<RoundCard*> selectRoundCards(RoundCardType cardType, std::vector<RoundCard*> &allRoundCards) const;
    RoundCard* selectOneTrainStationCard(std::vector<RoundCard*> &allRoundCards);
    std::vector<NeutralBullet*> generateNeutralBullets(unsigned numberOfNeutralBullets) const;
    Train* selectWagons(Train* allPossibleWagons, unsigned numberOfPlayers) const;
    void placeBanditInWagon(unsigned) const;

    void initialize();

    //Other methods

    void shuffleDecks() const;
    void selectBanditPositions();
    unsigned findPlayerById(BanditType);


private:

    std::vector<Player*> m_players;
    Train* m_wagons;
    unsigned m_sheriffPosition;
    std::vector<RoundCard*> m_rounds;
    std::vector<ActionCard*> m_cardsPlayed;
    std::vector<NeutralBullet*> m_neutralBulletDeck;
    std::vector<Treasure*> m_unusedTreasure;
    BanditType m_mostBulletsShot;
    BanditType m_richestPlayer;
};

void generateAllTreasure(const int &count, const int &value, TreasureType type, std::vector<Treasure> &treasure);
std::vector<unsigned> getMoneybags(std::vector<unsigned>& remainingMoneybags, unsigned numberOfMoneybags);
std::vector<RoundCard*> generateRoundCards(std::vector<EventType> &events, std::vector<std::vector<MiniRoundType>> &miniRounds);
std::vector<Treasure*> remainingTreasure(std::vector<unsigned> &remainingMoneybags, unsigned remainingDiamonds, unsigned remainingSuitcases);

#endif // GAME_H
