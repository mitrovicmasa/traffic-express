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

#include <QString>
#include <QMessageBox>

enum class Phase {
    WAGON_SELECTION,
    PHASE_1,
    PHASE_2
};

class Game:Serializable
{
public:

    // Constructors
    Game();
    Game(std::vector<Player*> &players);
    Game(const Game&);
    ~Game();

    //Get methods
    PlayerGroup &players();
    Train *wagons() ;
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
    const unsigned &seed() const;
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
    void setSeed(const unsigned &newSeed);

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
    void updateNextAction();

    void updateRounds();

    void showEndGameStats();

    int findPlayersTreasureIndex(Treasure*, unsigned);

    std::vector<Player*> possiblePlayersToShot(int playerIndex);
    std::vector<Player*> possiblePlayersToPunch(int playerIndex);
    std::vector<Treasure*> possibleTreasure(int playerIndex);

    //Action methods
    bool actionChangeWagon(int wagonIndex);
    void actionFloorChange();
    void actionSheriffMove(Wagon*w);
    bool actionFire(int playerIndex);
    std::pair<Wagon*, Treasure*> actionRobbery(int treasureIndex, int wagonIndex);
    std::pair<Wagon*, Treasure*> actionPunch(int treasureIndex, int wagonIndex, int playerIndex);

    int playerClicked() const;
    void setPlayerClicked(int newPlayerClicked);

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
    int m_playerClicked;
    unsigned m_seed;

    // Serializable interface
public:
    QVariant toVariant() const;
    void fromVariant(const QVariant &variant);
};

void generateAllTreasure(const int &count, const int &value, TreasureType type, std::vector<Treasure> &treasure);
std::vector<unsigned> getMoneybags(std::vector<unsigned>& remainingMoneybags, unsigned numberOfMoneybags);
std::vector<RoundCard*> generateRoundCards(std::vector<EventType> &events, std::vector<std::vector<MiniRoundType>> &miniRounds);
std::vector<Treasure*> remainingTreasure(std::vector<unsigned> &remainingMoneybags, unsigned remainingDiamonds, unsigned remainingSuitcases);

#endif // GAME_H
