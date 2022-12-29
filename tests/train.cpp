#include <catch.hpp>

#include "../TrafficExpress/headers/train.h"
#include "../TrafficExpress/headers/wagon.h"

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

    SECTION("Method size should return number of wagons in train")
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
