#include <catch.hpp>

#include "../TrafficExpress/headers/wagon.h"
#include "../TrafficExpress/headers/player.h"
#include "../TrafficExpress/headers/collections/treasurechest.h"

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

        const auto expectedOutput = 2;
        const auto expectedOutput1 = treasure;

        // act
        wagon->getContentUp().push_back(treasure);

        const auto actualOutput = wagon->getContentUp().size();
        const auto actualOutput1 = wagon->getContentUp().back();

        // assert
        REQUIRE(expectedOutput == actualOutput);
        REQUIRE(expectedOutput1 == actualOutput1);

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

        const auto expectedOutput = 2;
        const auto expectedOutput1 = treasure;

        // act
        wagon->getContentDown().push_back(treasure);

        const auto actualOutput = wagon->getContentDown().size();
        const auto actualOutput1 = wagon->getContentDown().back();

        // assert
        REQUIRE(expectedOutput == actualOutput);
        REQUIRE(expectedOutput1 == actualOutput1);

        delete wagon;
    }

    SECTION("Method addPlayerDown should move player inside the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Player *player = new Player(BanditType::HOMELESS_MAN);

        const auto expectedOutput = 1;
        const auto expectedOutput1 = false;

        // act
        wagon->addPlayerDown(player);

        const auto actualOutput = wagon->getPlayersDown().size();
        const auto actualOutput1 = player->roof();

        // assert
        REQUIRE(expectedOutput == actualOutput);
        REQUIRE(expectedOutput1 == actualOutput1);

        delete player;
        delete wagon;
    }

    SECTION("Method addPlayerUp should move player on the roof of the wagon")
    {
        // arrange
        Wagon *wagon = new Wagon();
        Player *player = new Player(BanditType::PICKPOCKET);

        const auto expectedOutput = 1;
        const auto expectedOutput1 = true;

        // act
        wagon->addPlayerUp(player);

        const auto actualOutput = wagon->getPlayersUp().size();
        const auto actualOutput1 = player->roof();

        // assert
        REQUIRE(expectedOutput == actualOutput);
        REQUIRE(expectedOutput1 == actualOutput1);

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
