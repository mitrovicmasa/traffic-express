//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../TrafficExpress/headers/card.h"
#include "../TrafficExpress/headers/player.h"
#include "../TrafficExpress/headers/banditcard.h"

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
