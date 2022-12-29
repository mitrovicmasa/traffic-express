//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../TrafficExpress/headers/hand.h"
#include "../TrafficExpress/headers/deck.h"
#include "../TrafficExpress/headers/card.h"
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
