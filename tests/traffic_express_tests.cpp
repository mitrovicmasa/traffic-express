#include <catch.hpp>

#include "../TrafficExpress/headers/game.h"
#include "../TrafficExpress/headers/hand.h"
#include "../TrafficExpress/headers/deck.h"
#include "../TrafficExpress/headers/card.h"
#include "../TrafficExpress/headers/table.h"
#include "../TrafficExpress/headers/train.h"
#include "../TrafficExpress/headers/wagon.h"
#include "../TrafficExpress/headers/player.h"
#include "../TrafficExpress/headers/playerstats.h"
#include "../TrafficExpress/headers/banditcard.h"
#include "../TrafficExpress/headers/actioncard.h"
#include "../TrafficExpress/headers/neutralbullet.h"
#include "../TrafficExpress/headers/bulletcard.h"
#include "../TrafficExpress/headers/miniround.h"
#include "../TrafficExpress/headers/roundcard.h"
#include "../TrafficExpress/headers/roundcarddeck.h"

TEST_CASE("Testing correctness of methods in class Card", "[card]")
{
    SECTION("Method Type should return type of card")
    {
        // arrange
        ActionCard* ac= new ActionCard(ActionType::FIRE,BanditType::STUDENT);
        NeutralBullet* nb = new NeutralBullet();
        BulletCard* bc = new BulletCard(BanditType::BUSINESS_WOMAN, 4);

        const auto expectedOutput1 = CardType::ACTION_CARD;
        const auto expectedOutput2 = CardType::BULLET_CARD;
        const auto expectedOutput3 = CardType::NEUTRAL_BULLET;

        // act
        const auto actualOutput1 = ac->Type();
        const auto actualOutput2 = bc->Type();
        const auto actualOutput3 = nb->Type();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);
        REQUIRE(expectedOutput3 == actualOutput3);

        delete ac;
        delete bc;
        delete nb;
    }
}

TEST_CASE("Testing correctness of methods in class Hand", "[hand]")
{

    SECTION("Method push_back should add card to the back of m_cards")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FIRE,BanditType::STUDENT);
        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = card;

        // act
        hand->push_back(card);
        const auto actualOutput1 = hand->getCards().size();
        const auto actualOutput2 = hand->getCards().back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete card;
        delete hand;
    }

    SECTION("Method back should return card in the back of m_cards")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        hand->push_back(card);
        const auto expectedOutput1 = card;

        // act
        const auto actualOutput1 = hand->back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete hand;
    }

    SECTION("Method pop_back should pop card from the back of m_cards")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        hand->push_back(card);
        const auto expectedOutput1 = 0;

        // act
        hand->pop_back();
        const auto actualOutput1 = hand->getCards().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete hand;
    }

    SECTION("Method push_front should add card to the front of m_cards")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FIRE,BanditType::STUDENT);
        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = card;

        // act
        hand->push_front(card);
        const auto actualOutput1 = hand->getCards().size();
        const auto actualOutput2 = hand->getCards().front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete card;
        delete hand;
    }

    SECTION("Method front should return card in the front of m_cards")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        hand->push_front(card);
        const auto expectedOutput1 = card;

        // act
        const auto actualOutput1 = hand->front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete hand;
    }

    SECTION("Method pop_front should pop card from the front of m_cards")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        hand->push_front(card);
        const auto expectedOutput1 = 0;

        // act
        hand->pop_front();
        const auto actualOutput1 = hand->getCards().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete hand;
    }

    SECTION("Method empty should return if the Hand is empty")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        hand->push_front(card);
        const auto expectedOutput1 = false;
        const auto expectedOutput2 = true;
        // act
        const auto actualOutput1 = hand->empty();
        hand->pop_front();
        const auto actualOutput2 = hand->empty();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete card;
        delete hand;
    }

    SECTION("Method takeCard(c) should remove a Card c from Hand")
    {
        // arrange
        Hand* hand = new Hand();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        hand->push_front(card);
        const auto expectedOutput1 = card;
        // act
        const auto actualOutput1 = hand->takeCard(card);

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete hand;
    }
}


TEST_CASE("Testing correctness of methods in class Deck", "[deck]")
{

    SECTION("Method push_back should add card to the back of m_cards")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FIRE,BanditType::STUDENT);
        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = card;

        // act
        deck->push_back(card);
        const auto actualOutput1 = deck->getCards().size();
        const auto actualOutput2 = deck->getCards().back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete card;
        delete deck;
    }

    SECTION("Method back should return card in the back of m_cards")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        deck->push_back(card);
        const auto expectedOutput1 = card;

        // act
        const auto actualOutput1 = deck->back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete deck;
    }

    SECTION("Method pop_back should pop card from the back of m_cards")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        deck->push_back(card);
        const auto expectedOutput1 = 0;

        // act
        deck->pop_back();
        const auto actualOutput1 = deck->getCards().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete deck;
    }

    SECTION("Method push_front should add card to the front of m_cards")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FIRE,BanditType::STUDENT);
        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = card;

        // act
        deck->push_front(card);
        const auto actualOutput1 = deck->getCards().size();
        const auto actualOutput2 = deck->getCards().front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete card;
        delete deck;
    }

    SECTION("Method front should return card in the front of m_cards")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        deck->push_front(card);
        const auto expectedOutput1 = card;

        // act
        const auto actualOutput1 = deck->front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete deck;
    }

    SECTION("Method pop_front should pop card from the front of m_cards")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        deck->push_front(card);
        const auto expectedOutput1 = 0;

        // act
        deck->pop_front();
        const auto actualOutput1 = deck->getCards().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete deck;
    }

    SECTION("Method empty should return if the Deck is empty")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        deck->push_front(card);
        const auto expectedOutput1 = false;
        const auto expectedOutput2 = true;
        // act
        const auto actualOutput1 = deck->empty();
        deck->pop_front();
        const auto actualOutput2 = deck->empty();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete card;
        delete deck;
    }

    SECTION("Method setAllCardsFaceUp should set all cards in Deck to FaceUp")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        deck->push_front(card);
        const auto expectedOutput1 = true;

        // act
        deck->setAllCardsFaceUp();
        const auto actualOutput1 = deck->front()->faceUp();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete deck;
    }

    SECTION("Method setAllCardsFaceDown should set all cards in Deck to face down")
    {
        // arrange
        Deck* deck = new Deck();
        ActionCard* card = new ActionCard(ActionType::FLOOR_CHANGE, BanditType::SEDUCTRESS);
        deck->push_front(card);
        const auto expectedOutput1 = false;

        // act
        deck->setAllCardsFaceDown();
        const auto actualOutput1 = deck->front()->faceUp();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete card;
        delete deck;
    }

}

TEST_CASE("Testing correctness of methods in class Miniround", "[miniround]")
{
    SECTION("Method getMiniRoundType should return type of mini round")
    {
        // arrange
        MiniRound* mr1 = new MiniRound(MiniRoundType::HIDDEN);
        MiniRound* mr2 = new MiniRound(MiniRoundType::DOUBLE_CARDS);
        MiniRound* mr3 = new MiniRound(MiniRoundType::FACE_UP);
        MiniRound* mr4 = new MiniRound(MiniRoundType::OPPOSITE_DIRECTION);

        const auto expectedOutput1 = MiniRoundType::HIDDEN;
        const auto expectedOutput2 = MiniRoundType::DOUBLE_CARDS;
        const auto expectedOutput3 = MiniRoundType::FACE_UP;
        const auto expectedOutput4 = MiniRoundType::OPPOSITE_DIRECTION;

        // act
        const auto actualOutput1 = mr1->getMiniRoundType();
        const auto actualOutput2 = mr2->getMiniRoundType();
        const auto actualOutput3 = mr3->getMiniRoundType();
        const auto actualOutput4 = mr4->getMiniRoundType();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);
        REQUIRE(expectedOutput3 == actualOutput3);
        REQUIRE(expectedOutput4 == actualOutput4);

        delete mr1;
        delete mr2;
        delete mr3;
        delete mr4;
    }
}

TEST_CASE("Testing correctness of methods in class RoundCard", "[roundcard]")
{
    SECTION("Method back should return MiniRound at the back of m_minirounds")
    {
        // arrange
        MiniRound* mr = new MiniRound(MiniRoundType::HIDDEN);
        std::vector<MiniRound*> minirounds;
        minirounds.push_back(mr);
        RoundCard* rc = new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, EventType::NONE, minirounds);
        const auto expectedOutput1 = mr;

        // act
        const auto actualOutput1 = rc->back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete rc;
        minirounds.clear();
    }

    SECTION("Method front should return MiniRound at the front of m_minirounds")
    {
        // arrange
        MiniRound* mr = new MiniRound(MiniRoundType::HIDDEN);
        std::vector<MiniRound*> minirounds;
        minirounds.push_back(mr);
        RoundCard* rc = new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, EventType::NONE, minirounds);
        const auto expectedOutput1 = mr;

        // act
        const auto actualOutput1 = rc->front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete rc;
        minirounds.clear();
    }
}


TEST_CASE("Testing correctness of methods in class RoundCardDeck", "[roundcarddeck]")
{

    SECTION("Method push_front should add RoundCard to the front of m_rounds")
    {
        // arrange
        RoundCardDeck* deck = new RoundCardDeck();
        MiniRound* mr = new MiniRound(MiniRoundType::HIDDEN);
        std::vector<MiniRound*> minirounds;
        minirounds.push_back(mr);
        RoundCard* rc = new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, EventType::NONE, minirounds);
        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = rc;

        // act
        deck->push_front(rc);
        const auto actualOutput1 = deck->getRoundCads().size();
        const auto actualOutput2 = deck->getRoundCads().front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete rc;
        minirounds.clear();
        delete deck;
    }

    SECTION("Method front should return roundcard in the front of m_rounds")
    {
        // arrange
        RoundCardDeck* deck = new RoundCardDeck();
        MiniRound* mr = new MiniRound(MiniRoundType::HIDDEN);
        std::vector<MiniRound*> minirounds;
        minirounds.push_back(mr);
        RoundCard* rc = new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, EventType::NONE, minirounds);
        deck->push_front(rc);
        const auto expectedOutput1 = rc;

        // act
        const auto actualOutput1 = deck->front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);


        delete rc;
        minirounds.clear();
        delete deck;
    }

    SECTION("Method back should return roundcard in the back of m_rounds")
    {
        // arrange
        RoundCardDeck* deck = new RoundCardDeck();
        MiniRound* mr = new MiniRound(MiniRoundType::HIDDEN);
        std::vector<MiniRound*> minirounds;
        minirounds.push_back(mr);
        RoundCard* rc = new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, EventType::NONE, minirounds);
        deck->push_front(rc);
        const auto expectedOutput1 = rc;

        // act
        const auto actualOutput1 = deck->back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);


        delete rc;
        minirounds.clear();
        delete deck;
    }

    SECTION("Method pop_front should pop roundcard from the front of m_rounds")
    {
        // arrange
        RoundCardDeck* deck = new RoundCardDeck();
        MiniRound* mr = new MiniRound(MiniRoundType::HIDDEN);
        std::vector<MiniRound*> minirounds;
        minirounds.push_back(mr);
        RoundCard* rc = new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, EventType::NONE, minirounds);
        deck->push_front(rc);
        const auto expectedOutput1 = 0;
        // act
        deck->pop_front();
        const auto actualOutput1 = deck->getRoundCads().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete rc;
        minirounds.clear();
        delete deck;
    }
}

TEST_CASE("Testing correctness of methods in class Player", "[player]")
{
    SECTION("Method countAmountOfTreasure should return amount of treasure that player currently has")
    {
        // arrange
        Player *player = new Player(BanditType::PICKPOCKET);
        player->treasure().push_back(new Treasure(500, TreasureType::DIAMOND));
        player->treasure().push_back(new Treasure(250, TreasureType::MONEYBAG));
        player->treasure().push_back(new Treasure(1000, TreasureType::SUITCASE));

        const auto expectedOutput = 2000;

        // act
        const auto actualOutput = player->countAmountOfTreasure();

        // assert
        REQUIRE(expectedOutput == actualOutput);

        delete player;
    }

    SECTION("Method empty should checked if bullet deck has no cards")
    {
        // arrange
        Player* player = new Player(BanditType::STUDENT);

        const auto expectedOutput1 = false;

        const auto expectedOutput2 = true;

        // act
        const auto actualOutput1 = player->isBulletDeckEmpty();

        player->bullet_deck()->pop_back();
        player->bullet_deck()->pop_back();
        player->bullet_deck()->pop_back();
        player->bullet_deck()->pop_back();
        player->bullet_deck()->pop_back();
        player->bullet_deck()->pop_back();


        const auto actualOutput2 = player->isBulletDeckEmpty();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete player;
    }

    SECTION("Method returnCardsToDeck should return cards from hand to deck ")
    {
        // arrange
        Player *player = new Player(BanditType::BUSINESS_WOMAN);

        player->hand()->push_back(new ActionCard(ActionType::FIRE, BanditType::BUSINESS_WOMAN));
        player->hand()->push_back(new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN));
        player->hand()->push_back(new ActionCard(ActionType::TAKETREASURE, BanditType::BUSINESS_WOMAN));

        const auto expectedOutput1 = 13;
        // act

        player->returnCardsToDeck();
        const auto actualOutput1 = player->deck()->size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

    }

    SECTION("Method drawCards should take n cards from deck ")
    {
        // arrange
        Player *player = new Player(BanditType::BUSINESS_WOMAN);

        const auto expectedOutput1 = 4;
        const auto expectedOutput2 = 6;

        // act

        player->drawCards(4);

        const auto actualOutput1 = player->hand()->getCards().size();
        const auto actualOutput2 = player->deck()->size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

    }

}

TEST_CASE("Testing addTreasureToPlayer of methods in class playerStats", "[playerStats]")
{

    SECTION("Method addTreasureToPlayer should add treasure to player")
    {
        // arrange
        Player* p = new Player(BanditType::SEDUCTRESS);
        PlayerStats* ps = new PlayerStats(p, true);

        Treasure* t1 = new Treasure(250, TreasureType::MONEYBAG);
        Treasure* t2 = new Treasure(500, TreasureType::DIAMOND);

        const auto expectedOutput1 = 3; //Each player has one treasure at the beginning

        // act
        ps->addTreasureToPlayer(t1);
        ps->addTreasureToPlayer(t2);

        const auto actualOutput1 = ps->getPlayer()->treasure().size();


        // assert
        REQUIRE(expectedOutput1 == actualOutput1);


        delete t2;
        delete t1;
        delete ps;
        delete p;

    }

    SECTION("Method takeTreasureFromPlayer should remove treasure from the playerStats")
    {
        // arrange
        Player* p = new Player(BanditType::SEDUCTRESS);
        PlayerStats* ps = new PlayerStats(p, true);

        Treasure* t1 = new Treasure(250, TreasureType::MONEYBAG);
        Treasure* t2 = new Treasure(500, TreasureType::DIAMOND);
        Treasure* t3 = new Treasure(1000, TreasureType::SUITCASE);

        const auto expectedOutput1 = 3;
        const auto expectedOutput2 = t3;

        // act
        ps->addTreasureToPlayer(t1);
        ps->addTreasureToPlayer(t2);
        ps->addTreasureToPlayer(t3);

        Treasure* t4 = ps->takeTreasureFromPlayer(t3);

        const auto actualOutput1 = ps->getPlayer()->treasure().size();
        const auto actualOutput2 = t4;

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);


//        delete p;
//        delete ps;
//        delete t3;
//        delete t4;
//        delete t2;
//        delete t1;

    }

}

TEST_CASE("Testing correctness of methods in class Table", "[table]")
{

    SECTION("Method push_back should add playerStats to the back of table")
    {
        // arrange
        Table* table = new Table();

        Player* player = new Player(BanditType::BUSINESS_WOMAN);
        PlayerStats* ps = new PlayerStats(player, true);
        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = ps;

        // act
        table->push_back(ps);
        const auto actualOutput1 = table->getPlayerStats().size();

        const auto actualOutput2 = table->getPlayerStats().back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete player;
        delete ps;
        delete table;
    }

    SECTION("Method empty should return information if the table is empty")
    {
        // arrange
        Table* table = new Table();

        Player* player1 = new Player(BanditType::BUSINESS_WOMAN);
        Player* player2 = new Player(BanditType::STUDENT);

        PlayerStats* ps = new PlayerStats(player1, true);
        PlayerStats* ps1 = new PlayerStats(player2, true);

        const auto expectedOutput1 = 2;

        // act
        table->push_back(ps);
        table->push_back(ps1);
        const auto actualOutput1 = table->getPlayerStats().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);


        delete player1;
        delete player2;
        delete ps;
        delete ps1;
        delete table;
    }
}

TEST_CASE("Testing correctnes of methods in class Train", "[train]")
{
    SECTION("Method push_back should add wagon on the back of train")
    {
        // arrange
        Train *train = new Train();
        Wagon* wagon = new Wagon(TreasureChest({new Treasure(250, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));

        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = wagon;

        // act
        train->push_back(wagon);
        const auto actualOutput1 = train->size();
        const auto actualOutput2 = train->getWagons().back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete wagon;
        delete train;

    }

    SECTION("Method back should return wagon from the back of the train")
    {
        // arrange
        Train* train = new Train();
        Wagon* wagon = new Wagon(TreasureChest({new Treasure(450, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));

        train->push_back(wagon);
        const auto expectedOutput1 = wagon;

        // act
        const auto actualOutput1 = train->back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete wagon;
        delete train;
    }

    SECTION("Method pop_back should remove wagon from the back of the train")
    {
        // arrange
        Train* train = new Train();
        Wagon* wagon = new Wagon(TreasureChest({new Treasure(450, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));

        train->push_back(wagon);
        const auto expectedOutput1 = 0;

        // act
        train->pop_back();
        const auto actualOutput1 = train->getWagons().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete wagon;
        delete train;
    }

    SECTION("Method push_front should add wagon on the front of train")
    {
        // arrange
        Train *train = new Train();
        Wagon* wagon1 = new Wagon(TreasureChest({new Treasure(250, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));
        Wagon* wagon2 = new Wagon(TreasureChest({new Treasure(450, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));

        const auto expectedOutput1 = 2;
        const auto expectedOutput2 = wagon2;

        // act
        train->push_front(wagon1);
        train->push_front(wagon2);

        const auto actualOutput1 = train->getWagons().size();
        const auto actualOutput2 = train->getWagons().front();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete wagon1;
        delete wagon2;
        delete train;

    }

    SECTION("Method front should return wagon from the front of the train")
    {
        // arrange
        Train* train = new Train();
        Wagon* wagon1 = new Wagon(TreasureChest({new Treasure(500, TreasureType::DIAMOND)}),
                                 TreasureChest(std::vector<Treasure*>()));
        Wagon* wagon2 = new Wagon(TreasureChest({new Treasure(250, TreasureType::MONEYBAG)}),
                                  TreasureChest(std::vector<Treasure*>()));

        train->push_front(wagon1);
        train->push_front(wagon2);

        const auto expectedOutput1 = wagon2;
        const auto expectedOutput2 = 2;

        // act
        const auto actualOutput1 = train->front();
        const auto actualOutput2 = train->getWagons().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete wagon1;
        delete wagon2;
        delete train;
    }

    SECTION("Method pop_front should remove wagon from the front of the train")
    {
        // arrange
        Train* train = new Train();
        Wagon* wagon1 = new Wagon(TreasureChest({new Treasure(450, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));
        Wagon* wagon2 = new Wagon(TreasureChest({new Treasure(250, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));

        train->push_back(wagon1);
        train->push_back(wagon2);

        const auto expectedOutput1 = 1;

        // act
        train->pop_front();
        const auto actualOutput1 = train->size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete wagon1;
        delete wagon2;
        delete train;
    }

    SECTION("Method size should return number of wagons in train")
    {
        // arrange
        Train* train = new Train();
        Wagon* wagon1 = new Wagon(TreasureChest({new Treasure(450, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));
        Wagon* wagon2 = new Wagon(TreasureChest({new Treasure(250, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));
        Wagon* wagon3 = new Wagon(TreasureChest({new Treasure(500, TreasureType::DIAMOND)}),
                                 TreasureChest(std::vector<Treasure*>()));

        train->push_back(wagon1);
        train->push_back(wagon2);
        train->push_back(wagon3);

        const auto expectedOutput1 = 3;

        // act
        const auto actualOutput1 = train->size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete wagon1;
        delete wagon2;
        delete wagon3;
        delete train;
    }

    SECTION("Method empty should check if train has no wagons")
    {
        // arrange
        Train* train = new Train();
        Wagon* wagon1 = new Wagon(TreasureChest({new Treasure(450, TreasureType::MONEYBAG)}),
                                 TreasureChest(std::vector<Treasure*>()));
        Wagon* wagon2 = new Wagon(TreasureChest({new Treasure(500, TreasureType::DIAMOND)}),
                                 TreasureChest(std::vector<Treasure*>()));
        Wagon* wagon3 = new Wagon(TreasureChest({new Treasure(1000, TreasureType::SUITCASE)}),
                                 TreasureChest(std::vector<Treasure*>()));

        const auto expectedOutput1 = true;
        const auto expectedOutput2 = false;

        // act
        const auto actualOutput1 = train->empty();

        train->push_back(wagon1);
        train->push_back(wagon2);
        train->push_back(wagon3);

        const auto actualOutput2 = train->empty();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete wagon1;
        delete wagon2;
        delete wagon3;
        delete train;
    }
}

TEST_CASE("Testing correctness of methods in class Wagon", "[wagon]")
{
    SECTION("Method addContentUp should add treasure on the roof of the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        TreasureChest contentUp = TreasureChest();
        contentUp.push_back(new Treasure(250, TreasureType::MONEYBAG));
        wagon->setContentUp(contentUp);

        Treasure *treasure = new Treasure(500, TreasureType::DIAMOND);

        const auto expectedOutput1 = 2;
        const auto expectedOutput2 = treasure;

        // act
        wagon->getContentUp().push_back(treasure);

        const auto actualOutput1 = wagon->getContentUp().size();
        const auto actualOutput2 = wagon->getContentUp().back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete wagon;
    }

    SECTION("Method addContentDown should add treasure inside the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        TreasureChest contentDown = TreasureChest();
        contentDown.push_back(new Treasure(250, TreasureType::DIAMOND));
        wagon->setContentDown(contentDown);

        Treasure *treasure = new Treasure(1000, TreasureType::SUITCASE);

        const auto expectedOutput1 = 2;
        const auto expectedOutput2 = treasure;

        // act
        wagon->getContentDown().push_back(treasure);

        const auto actualOutput1 = wagon->getContentDown().size();
        const auto actualOutput2 = wagon->getContentDown().back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete wagon;
    }

    SECTION("Method addPlayerDown should move player inside the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Player *player = new Player(BanditType::HOMELESS_MAN);

        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = false;

        // act
        wagon->addPlayerDown(player);

        const auto actualOutput1 = wagon->getPlayersDown().size();
        const auto actualOutput2 = player->roof();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete player;
        delete wagon;
    }

    SECTION("Method addPlayerUp should move player on the roof of the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Player *player = new Player(BanditType::PICKPOCKET);

        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = true;

        // act
        wagon->addPlayerUp(player);

        const auto actualOutput1 = wagon->getPlayersUp().size();
        const auto actualOutput2 = player->roof();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete player;
        delete wagon;
    }

    SECTION("Method takeContentDown should take treasure that is inside the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Treasure *treasure1 = new Treasure(250, TreasureType::MONEYBAG);
        Treasure *treasure2 = new Treasure(500, TreasureType::DIAMOND);
        Treasure *treasure3 = new Treasure(1000, TreasureType::SUITCASE);

        const auto expectedOutput1 = 2;
        const auto expectedOutput2 = treasure3;

        // act
        wagon->addContentDown(treasure1);
        wagon->addContentDown(treasure2);
        wagon->addContentDown(treasure3);

        Treasure *treasure4 = wagon->takeContentDown(treasure3);

        const auto actualOutput1 = wagon->getContentDown().size();
        const auto actualOutput2 = treasure4;

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete treasure1;
        delete treasure2;
        delete treasure3;
        delete wagon;
    }

    SECTION("Method takeContentUp should take treasure that is on the roof of the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Treasure *treasure1 = new Treasure(250, TreasureType::MONEYBAG);
        Treasure *treasure2 = new Treasure(500, TreasureType::DIAMOND);
        Treasure *treasure3 = new Treasure(1000, TreasureType::SUITCASE);

        const auto expectedOutput1 = 2;
        const auto expectedOutput2 = treasure3;

        // act
        wagon->addContentUp(treasure1);
        wagon->addContentUp(treasure2);
        wagon->addContentUp(treasure3);

        Treasure *treasure4 = wagon->takeContentUp(treasure3);

        const auto actualOutput1 = wagon->getContentUp().size();
        const auto actualOutput2 = treasure4;

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete treasure1;
        delete treasure2;
        delete treasure3;
        delete wagon;
    }

    SECTION("Method takePlayerUp should remove player from the roof of the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Player *player1 = new Player(BanditType::PICKPOCKET);
        Player *player2 = new Player(BanditType::HOMELESS_MAN);
        Player *player3 = new Player(BanditType::BUSINESS_WOMAN);
        Player *player4 = new Player(BanditType::SEDUCTRESS);

        const auto expectedOutput1 = 3;
        const auto expectedOutput2 = player3;

        // act
        wagon->addPlayerUp(player1);
        wagon->addPlayerUp(player2);
        wagon->addPlayerUp(player3);
        wagon->addPlayerUp(player4);

        Player *player5 = wagon->takePlayerUp(player3);

        const auto actualOutput1 = wagon->getPlayersUp().size();
        const auto actualOutput2 = player5;

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete player1;
        delete player2;
        delete player3;
        delete player4;
        delete wagon;
    }

    SECTION("Method takePlayerDown should remove player from the roof of the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Player *player1 = new Player(BanditType::PICKPOCKET);
        Player *player2 = new Player(BanditType::HOMELESS_MAN);
        Player *player3 = new Player(BanditType::BUSINESS_WOMAN);
        Player *player4 = new Player(BanditType::SEDUCTRESS);

        const auto expectedOutput1 = 3;
        const auto expectedOutput2 = player3;

        // act
        wagon->addPlayerDown(player1);
        wagon->addPlayerDown(player2);
        wagon->addPlayerDown(player3);
        wagon->addPlayerDown(player4);

        Player *player5 = wagon->takePlayerDown(player3);

        const auto actualOutput1 = wagon->getPlayersDown().size();
        const auto actualOutput2 = player5;

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete player1;
        delete player2;
        delete player3;
        delete player4;
        delete wagon;
    }

    SECTION("Method numberOfTreasureInWagonDown returns number of treasure of required type from wagon")
    {
        // arrange

        Wagon *wagon = new Wagon();
        wagon->addContentDown(new Treasure(250, TreasureType::MONEYBAG));
        wagon->addContentDown(new Treasure(500, TreasureType::DIAMOND));
        wagon->addContentDown(new Treasure(450, TreasureType::MONEYBAG));
        wagon->addContentDown(new Treasure(450, TreasureType::MONEYBAG));

        const auto expectedOutput1 = 3;

        // act
        const auto actualOutput1 = wagon->numberOfTreasureInWagonDown(TreasureType::MONEYBAG);

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete wagon;
    }

    SECTION("Method getTreasureIndex should return index of given treasure in wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Treasure *treasure1 = new Treasure(250, TreasureType::MONEYBAG);
        Treasure *treasure2 = new Treasure(250, TreasureType::MONEYBAG);
        Treasure *treasure3 = new Treasure(450, TreasureType::MONEYBAG);
        Treasure *treasure4 = new Treasure(1000, TreasureType::SUITCASE);

        wagon->addContentDown(treasure1);
        wagon->addContentDown(treasure2);
        wagon->addContentDown(treasure3);
        wagon->addContentDown(treasure4);

        const auto expectedOutput1 = 3;
        const auto expectedOutput2 = -1;

        Treasure *treasure5 = new Treasure(500, TreasureType::DIAMOND);

        // act
        const auto actualOutput1 = wagon->getTreasureIndex(treasure4, false);
        const auto actualOutput2 = wagon->getTreasureIndex(treasure5, false);

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete wagon;
    }

}

TEST_CASE("Testing correctness of methods in class Game", "[game]")
{
    SECTION("Method setNextPlayerToMove should set next player to move")
    {
        // arrange
        std::vector<Player*> players;
            players = {
                new Player(BanditType::PICKPOCKET),
                new Player(BanditType::SEDUCTRESS),
                new Player(BanditType::STUDENT),
            };

        Game* game = new Game(players);
        game->setIndexOfPlayerToMove(2);
        const auto expectedOutput1 = 0;

        // act
        game->setNextPlayerToMove();
        const auto actualOutput1 = game->getIndexOfPlayerToMove();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);

        delete game;
        for(Player* p: players)
                delete p;
    }

    SECTION("Method allPlayersDrawCards should draw n cards for all players")
    {
        // arrange
        std::vector<Player*> players;
            players = {
                new Player(BanditType::PICKPOCKET),
                new Player(BanditType::SEDUCTRESS),
                new Player(BanditType::STUDENT),
            };
        for(Player* p: players)
                p->deck()->push_back(new NeutralBullet());
        Game* game = new Game(players);
        const auto expectedOutput1 = true;
        const auto expectedOutput2 = false;
        const auto expectedOutput3 = true;
        const auto expectedOutput4 = false;
        const auto expectedOutput5 = true;
        const auto expectedOutput6 = false;

        // act
        const auto actualOutput1 = game->players()[0]->hand()->empty();
        const auto actualOutput3 = game->players()[1]->hand()->empty();
        const auto actualOutput5 = game->players()[2]->hand()->empty();
        game->allPlayersDrawCards(1);
        const auto actualOutput2 = game->players()[0]->hand()->empty();
        const auto actualOutput4 = game->players()[1]->hand()->empty();
        const auto actualOutput6 = game->players()[2]->hand()->empty();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);
        REQUIRE(expectedOutput3 == actualOutput3);
        REQUIRE(expectedOutput4 == actualOutput4);
        REQUIRE(expectedOutput5 == actualOutput5);
        REQUIRE(expectedOutput6 == actualOutput6);

        delete game;
        for(Player* p: players)
                delete p;
    }

    SECTION("Method findPlayerById returns index of player using his id")
    {
        // arrange
        std::vector<Player*> players;
            players = {
                new Player(BanditType::PICKPOCKET),
                new Player(BanditType::SEDUCTRESS),
                new Player(BanditType::STUDENT),
            };
        for(Player* p: players)
                p->deck()->push_back(new NeutralBullet());
        Game* game = new Game(players);
        const auto expectedOutput1 = 0;
        const auto expectedOutput2 = 1;
        const auto expectedOutput3 = 2;

        // act
        const auto actualOutput1 = game->findPlayerById(BanditType::PICKPOCKET);
        const auto actualOutput2 = game->findPlayerById(BanditType::SEDUCTRESS);
        const auto actualOutput3 = game->findPlayerById(BanditType::STUDENT);

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);
        REQUIRE(expectedOutput3 == actualOutput3);

        delete game;
        for(Player* p: players)
            delete p;
    }

    SECTION("Method findPlayersTreasureIndex returns index of player's treasure")
    {
        // arrange
        std::vector<Player*> players;
            players = {
                new Player(BanditType::PICKPOCKET),
            };
        Treasure* t1 = new Treasure();
        Treasure* t2 = new Treasure();
        players[0]->treasure().push_back(t1);
        players[0]->treasure().push_back(t2);
        Game* game = new Game(players);
        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = 2;

        // act
        const auto actualOutput1 = game->findPlayersTreasureIndex(t1,0);
        const auto actualOutput2 = game->findPlayersTreasureIndex(t2,0);
        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete game;
        delete t1;
        delete t2;
        for(Player* p: players)
            delete p;

    }

    SECTION("Method possiblePlayersToShot returns vector of players that playerIndex can shoot")
    {
        // arrange
        std::vector<Player*> players;
            players = {
                new Player(BanditType::PICKPOCKET),
                new Player(BanditType::SEDUCTRESS),
                new Player(BanditType::STUDENT),
            };
        Game* game = new Game(players);

        game->initialize();
        Wagon* w1 = game->wagons()->getWagons()[0];
        for(Player* p: players) {
            w1->addPlayerDown(p);
            p->setPositionInTrain(0);
            p->setRoof(false);
        }
        const auto expectedOutput1 = true;
        const auto expectedOutput2 = game->players()[0]->id();

        // act
        const auto actualOutput1 = game->possiblePlayersToShot(0).empty();
        game->wagons()->getWagons()[0]->takePlayerDown(game->players()[0]);
        game->wagons()->getWagons()[1]->addPlayerDown(game->players()[0]);
        const auto actualOutput2 = game->possiblePlayersToShot(1)[0]->id();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete game;
        for(Player* p: players)
            delete p;

    }


    SECTION("Method possiblePlayersToPunch returns vector of players that playerIndex can punch")
    {
        // arrange
        std::vector<Player*> players;
            players = {
                new Player(BanditType::PICKPOCKET),
                new Player(BanditType::SEDUCTRESS),
                new Player(BanditType::STUDENT),
            };
        Game* game = new Game(players);

        game->initialize();
        Wagon* w1 = game->wagons()->getWagons()[0];
        for(Player* p: players) {
            w1->addPlayerDown(p);
            p->setPositionInTrain(0);
            p->setRoof(false);
        }
        const auto expectedOutput1 = 2;
        const auto expectedOutput2 = game->players()[0]->id();

        // act
        const auto actualOutput1 = game->possiblePlayersToPunch(0).size();
        game->wagons()->getWagons()[0]->takePlayerDown(game->players()[2]);
        game->wagons()->getWagons()[1]->addPlayerDown(game->players()[2]);
        const auto actualOutput2 = game->possiblePlayersToPunch(1)[0]->id();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete game;
        for(Player* p: players)
            delete p;

    }

    SECTION("Method possibleTreasure returns vector of treasure that playerIndex can take")
    {
        // arrange
        std::vector<Player*> players;
            players = {
                new Player(BanditType::PICKPOCKET),
                new Player(BanditType::SEDUCTRESS),
                new Player(BanditType::STUDENT),
            };
        Game* game = new Game(players);

        game->initialize();
        Wagon* w1 = game->wagons()->getWagons()[0];
        for(Player* p: players) {
            w1->addPlayerDown(p);
            p->setPositionInTrain(0);
            p->setRoof(false);
        }
        std::vector<Treasure*> treasures = w1->getContentDown();

        const auto expectedOutput1 = treasures.size();
        const auto expectedOutput2 = true;

        // act
        const auto actualOutput1 = game->possibleTreasure(0).size();
        for(Treasure* t: treasures)
            w1->takeContentDown(t);
        const auto actualOutput2 = game->possibleTreasure(0).empty();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete game;
        for(Player* p: players)
            delete p;

    }

    SECTION("Method actionChangeFloor should change player's setRoof field")
    {
        // arrange
        std::vector<Player*> players = {
            new Player(BanditType::PICKPOCKET),
            new Player(BanditType::SEDUCTRESS),
            new Player(BanditType::RETIREE),
            new Player(BanditType::HOMELESS_MAN)
        };

        Game *game = new Game(players);
        game->initialize();

        for (unsigned i = 0; i < players.size(); ++i) {
            if (i % 2 == 0) {
                game->wagons()->getWagons()[0]->addPlayerDown(players[i]);
                players[i]->setPositionInTrain(0);
                players[i]->setRoof(false);
            } else {
                game->wagons()->getWagons()[1]->addPlayerDown(players[i]);
                players[i]->setPositionInTrain(1);
                players[i]->setRoof(false);
            }
        }

        const auto expectedOutput1 = 1;
        const auto expectedOutput2 = true;
        const auto expectedOutput3 = 1;

        game->setIndexOfPlayerToMove(0);

        // act
        game->actionFloorChange();
        const auto actualOutput1 = game->wagons()->getWagons()[0]->getPlayersUp().size();
        game->setSeriffPosition(0);

        const auto actualOutput2 = game->players()[0]->roof();

        game->setIndexOfPlayerToMove(0);
        game->actionFloorChange();
        const auto actualOutput3 = game->wagons()->getWagons()[0]->getPlayersUp().size();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);
        REQUIRE(expectedOutput3 == actualOutput3);

        delete game;
        for(Player* p: players)
            delete p;
    }

    SECTION("Method actionChangeWagon should move player to different wagon")
    {
        // arrange
        std::vector<Player*> players = {
            new Player(BanditType::PICKPOCKET),
            new Player(BanditType::STUDENT),
            new Player(BanditType::RETIREE),
            new Player(BanditType::HOMELESS_MAN)
        };

        Game *game = new Game(players);
        game->initialize();

        for (unsigned i = 0; i < players.size(); ++i) {
            if (i % 2 == 0) {
                game->wagons()->getWagons()[0]->addPlayerDown(players[i]);
                players[i]->setPositionInTrain(0);
                players[i]->setRoof(true);
            } else {
                game->wagons()->getWagons()[1]->addPlayerDown(players[i]);
                players[i]->setPositionInTrain(1);
                players[i]->setRoof(false);
            }
        }

        const auto expectedOutput1 = true;
        const auto expectedOutput2 = false;

        game->setIndexOfPlayerToMove(0);

        // act
        const auto actualOutput1 = game->actionChangeWagon(3);;

        game->setIndexOfPlayerToMove(3);

        const auto actualOutput2 = game->actionChangeWagon(3);

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);

        delete game;
        for(Player* p: players)
            delete p;
    }

    SECTION("Method actionFire should add bullet to deck of player that is shot")
    {
        // arrange
        std::vector<Player*> players = {
            new Player(BanditType::PICKPOCKET),
            new Player(BanditType::STUDENT),
            new Player(BanditType::RETIREE),
            new Player(BanditType::HOMELESS_MAN)
        };

        Game *game = new Game(players);
        game->initialize();

        for (unsigned i = 0; i < players.size(); ++i) {
            if (i % 2 == 0) {
                game->wagons()->getWagons()[0]->addPlayerDown(players[i]);
                players[i]->setPositionInTrain(0);
                players[i]->setRoof(false);
            } else {
                game->wagons()->getWagons()[1]->addPlayerDown(players[i]);
                players[i]->setPositionInTrain(1);
                players[i]->setRoof(false);
            }
        }

        const auto expectedOutput1 = false;
        const auto expectedOutput2 = true;
        const auto expectedOutput3 = game->players()[0]->bullet_deck()->back();

        game->setIndexOfPlayerToMove(0);

        // act
        const auto actualOutput1 = game->actionFire(2);
        const auto actualOutput2 = game->actionFire(1);
        const auto actualOutput3 = game->players()[1]->deck()->back();

        // assert
        REQUIRE(expectedOutput1 == actualOutput1);
        REQUIRE(expectedOutput2 == actualOutput2);
        REQUIRE(expectedOutput3 == actualOutput3);

        delete game;
        for(Player* p: players)
            delete p;
    }
}
