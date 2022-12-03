#ifndef WAGON_H
#define WAGON_H

#include <treasure.h>
#include <vector>

class Wagon
{
public:

    // Constructors
    Wagon();
    Wagon(const std::vector<Treasure> &contentDown, const std::vector<Treasure> &contentUp);

    // Destructor


    // Get methods
    // Set methods
    void setContentDown(const std::vector<Treasure>& newContentDown);

    // Other methods

    void addContentUp( const Treasure );
    void addContentDown(Treasure);
    void clearContentDown();
    Treasure takeContentUp(TreasureType);
    Treasure takeContentDown(TreasureType);
    int numberOfTreasureInWagon(TreasureType) const;

    std::string toString();

private:

std::vector<Treasure>m_contentUp;
std::vector<Treasure>m_contentDown;
};

#endif // WAGON_H
