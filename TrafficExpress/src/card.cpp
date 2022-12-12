#include "../headers/card.h"

// Constructors
Card::Card():QGraphicsObject()
{

}

// Destructor
Card::~Card()
{

}

// Get methods
bool Card::faceUp() const
{
    return m_faceUp;
}

// Set methods
void Card::setFaceUp(bool newFaceUp)
{
    m_faceUp = newFaceUp;
}

// Other methods
std::string Card::toString() const
{
    return "";
}

// GUI
int Card::height() const
{
    return 80;
}

int Card::width() const
{
    return 80;
}

QRectF Card::boundingRect() const
{
    return QRectF(0,0,width(),height());
}
