#include "../headers/treasure.h"

// Constructors
Treasure::Treasure()
    :m_type(TreasureType::MONEYBAG),m_value(250)
{

}

Treasure::Treasure(int value, TreasureType type)
    :m_type(type),m_value(value)
{

}

Treasure::Treasure(const Treasure &t)
    :m_type(t.m_type),m_value(t.m_value)
{

}

// Get methods
TreasureType Treasure::getType()
{
    return m_type;
}

int Treasure::getValue()
{
    return m_value;
}

// Other methods
Treasure &Treasure::operator=(const Treasure &t)
{
    auto tmp=Treasure(t);
    std::swap(m_type,tmp.m_type);
    std::swap(m_value,tmp.m_value);
    return *this;
}

bool Treasure::operator==(const Treasure &t)
{
    return m_type==t.m_type && m_value==t.m_value;
}

bool Treasure::operator!=(const Treasure &t)
{
    return !(m_type==t.m_type && m_value==t.m_value);
}

std::string Treasure::toString()
{
    switch(m_type){
                case TreasureType::MONEYBAG:return "MONEYBAG:"+std::to_string(m_value);
                case TreasureType::DIAMOND:return "DIAMOND:"+std::to_string(m_value);;
                case TreasureType::SUITCASE:return "SUITCASE:"+std::to_string(m_value);;
                default:return "UNKNOWN TREASURE TYPE";

    }
}



