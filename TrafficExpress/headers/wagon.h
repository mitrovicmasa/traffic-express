#ifndef WAGON_H
#define WAGON_H

#include <treasure.h>
#include <vector>

class Wagon
{
public:

    // Constructors
    Wagon();

    // Destructor


    // Get methods
    // Set methods


    // Other methods

    void addContentUp( const Treasure );
    void addContentDown(Treasure);
    Treasure takeContentUp(TreasureType);
    Treasure takeContentDown(TreasureType);

    std::string toString();

private:

std::vector<Treasure>m_contentUp;
std::vector<Treasure>m_contentDown;
};

#endif // WAGON_H
