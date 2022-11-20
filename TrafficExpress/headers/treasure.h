#ifndef TREASURE_H
#define TREASURE_H

#include<string>
enum class TreasureType{
   SUITCASE,DIAMOND,MONEYBAG
};

class Treasure
{
public:

    // Constructors
    Treasure();
    Treasure(int value,TreasureType type);
    Treasure(const Treasure&t);

    // Destructor


    // Operator overloading
    Treasure& operator=(const Treasure&t);
    bool operator==(const Treasure&t);
    bool operator!=(const Treasure&t);

    // Get methods
    TreasureType getType();
    int getValue();

    // Set methods


    // Other methods

    std::string toString();

private:
    TreasureType m_type;
    unsigned m_value;
};

#endif // TREASURE_H
