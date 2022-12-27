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
#include <roundcardcollection.h>
#include <roundcarddeck.h>
#include <cstdlib>

enum class Phase {
    WAGON_SELECTION,
    PHASE_1,
    PHASE_2
};

class Game
{
public:

    // Constructors
    Game();
    Game(std::vector<Player*> &players);
    Game(const Game&);

    //Get methods
    PlayerGroup &players();
    Train *wagons() const;
    RoundCardDeck *rounds();
    std::vector<NeutralBullet*> neutralBulletDeck() const;
    const TreasureChest &unusedTreasure() const;
    BanditType mostBulletsShot() const;
    BanditType richestPlayer() const;
    unsigned sheriffPosition() const;
    int getIndexOfPlayerToMove()const;
    Deck* getCardsPlayed();
    int indexOfRound() const;
    int indexOfMiniround() const;
    Phase phase() const;
    ActionType currentAction() const;
    DialogueBox *dialogueBox() const;
    bool actionPending() const;

    //Set methods
    void setPlayers(const std::vector<Player*> &newPlayers);
    void setWagons(Train* newWagons);
    void setRounds(std::vector<RoundCard*> &newRounds);
    //void setCardsPlayed(std::vector<ActionCard*> newCardsPlayed);
    void setNeutralBulletDeck(const std::vector<NeutralBullet*> &newNeutralBulletDeck);
    void setUnusedTreasure(const std::vector<Treasure*> &newUnusedTreasure);
    void setMostBulletsShot(BanditType newMostBulletsShot);
    void setRichestPlayer(BanditType newRichestPlayer);
    void setSeriffPosition(unsigned newSheriffPosition);
    void setIndexOfPlayerToMove(int);
    void setCardsPlayed(Deck *newCardsPlayed);
    void setIndexOfRound(int newIndexOfRound);
    void setIndexOfMiniround(int newIndexOfMiniround);
    void setPhase(Phase newPhase);
    void setCurrentAction(ActionType newCurrentAction);
    void setDialogueBox(DialogueBox *newDialogueBox);
    void setActionPending(bool newActionPending);

    // Initialization methods

    const std::vector<Card*> &drawCards(unsigned) const;
    std::vector<Card*> drawCards(unsigned numberOfCards, const Player* &player) const;
    std::vector<RoundCard*> selectRoundCards(RoundCardType cardType, std::vector<RoundCard*> &allRoundCards) const;
    RoundCard* selectOneTrainStationCard(std::vector<RoundCard*> &allRoundCards);
    std::vector<NeutralBullet*> generateNeutralBullets(unsigned numberOfNeutralBullets) const;
    Train* selectWagons(std::vector<Wagon*> allPossibleWagons, unsigned numberOfPlayers) const;
    void placeBanditInWagon(unsigned) const;

    void initialize();

    //Other methods
    void setNextPlayerToMove();
    void allPlayersDrawCards(int n);
    void shuffleDecks() const;
    void selectBanditPositions();
    unsigned findPlayerById(BanditType);

    void checkNextActionCard();
    void updateRounds();

    int findPlayersTreasureIndex(Treasure*, unsigned);


    //Action methods
    void actionChangeWagon(int wagonIndex);
    void actionFloorChange();
    void actionSheriffMove(Wagon*w);
    bool actionFire(int playerIndex);
    std::pair<Wagon*, Treasure*> actionRobbery(int treasureIndex, int wagonIndex);
    std::pair<Wagon*, Treasure*> actionPunch(int treasureIndex, int wagonIndex, int playerIndex);

private:
    int m_indexOfPlayerToMove;
    int m_indexOfRound;
    int m_indexOfMiniround;
    ActionType m_currentAction;
    PlayerGroup m_players;
    Train* m_wagons;
    unsigned m_sheriffPosition;
    RoundCardDeck* m_rounds;
    Deck* m_cardsPlayed;
    std::vector<NeutralBullet*> m_neutralBulletDeck;
    TreasureChest m_unusedTreasure;
    BanditType m_mostBulletsShot;
    BanditType m_richestPlayer;
    Phase m_phase;
    DialogueBox* m_dialogueBox;
    bool m_actionPending;
};

void generateAllTreasure(const int &count, const int &value, TreasureType type, std::vector<Treasure> &treasure);
std::vector<unsigned> getMoneybags(std::vector<unsigned>& remainingMoneybags, unsigned numberOfMoneybags);
std::vector<RoundCard*> generateRoundCards(std::vector<EventType> &events, std::vector<std::vector<MiniRoundType>> &miniRounds);
std::vector<Treasure*> remainingTreasure(std::vector<unsigned> &remainingMoneybags, unsigned remainingDiamonds, unsigned remainingSuitcases);

#endif // GAME_H
