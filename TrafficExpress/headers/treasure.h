#ifndef TREASURE_H
#define TREASURE_H

#include<string>
enum class TreasureType{
   SUITCASE,DIAMOND,MONEYBAG
};

class Treasure
{
public:
    Treasure();


    Treasure(int value,TreasureType type);
    Treasure(const Treasure&t);

    Treasure& operator=(const Treasure&t);

    std::string toString();
    bool operator==(const Treasure&t);
    bool operator!=(const Treasure&t);

    TreasureType getType();
    int getValue();
private:
    TreasureType m_type;
    int m_value;
};

#endif // TREASURE_H
