#include <catch.hpp>

#include "../TrafficExpress/headers/playerstats.h"
#include "../TrafficExpress/headers/treasure.h"
#include "../TrafficExpress/headers/player.h"

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
