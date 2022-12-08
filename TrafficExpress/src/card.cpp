#include "../headers/card.h"

// Constructors
Card::Card()
{

}

// Destructor
Card::~Card()
{

}

// Other methods
std::string Card::toString() const
{
    return "";
}

int Card::visina() const
{
    return 100;
}

int Card::sirina() const
{
    return 50;
}

QRectF Card::boundingRect() const
{
    return QRectF(0,0,sirina(),visina());
}
