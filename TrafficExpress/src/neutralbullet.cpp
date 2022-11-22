#include "../headers/neutralbullet.h"

// Constructors
NeutralBullet::NeutralBullet(unsigned const id) : m_id(id)
{}

Card *NeutralBullet::Copy() const
{
    return new NeutralBullet(*this);
}

// Destructor
NeutralBullet::~NeutralBullet()
{

}

// Get methods
const unsigned &NeutralBullet::id() const
{
    return m_id;
}

// Set methods
void NeutralBullet::setId(const unsigned &newId)
{
    m_id = newId;
}

// Other methods

std::string NeutralBullet::toString() const
{
    return "Neutral bullet id: " + std::to_string(m_id);
}
