#include "../headers/neutralbullet.h"

NeutralBullet::NeutralBullet(unsigned const id) : m_id(id)
{}

std::string NeutralBullet::toString() const
{
    return "Neutral bullet id: " + std::to_string(m_id);
}

const unsigned &NeutralBullet::id() const
{
    return m_id;
}

void NeutralBullet::setId(const unsigned &newId)
{
    m_id = newId;
}


NeutralBullet::~NeutralBullet()
{

}
