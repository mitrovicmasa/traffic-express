#include <catch.hpp>

#include "../TrafficExpress/headers/table.h"
#include "../TrafficExpress/headers/playerstats.h"
#include "../TrafficExpress/headers/player.h"

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
