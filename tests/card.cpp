//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../TrafficExpress/headers/hand.h"
#include "../TrafficExpress/headers/deck.h"
#include "../TrafficExpress/headers/card.h"
#include "../TrafficExpress/headers/banditcard.h"
#include "../TrafficExpress/headers/actioncard.h"
#include "../TrafficExpress/headers/neutralbullet.h"
#include "../TrafficExpress/headers/bulletcard.h"

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
