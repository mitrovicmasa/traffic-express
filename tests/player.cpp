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
}
