#include "../headers/wagon.h"
#include <strings.h>
#include<QRandomGenerator>

// Constructors
Wagon::Wagon()
    :m_contentDown(std::vector<Treasure>()),m_contentUp(std::vector<Treasure>())
{

}

Wagon::Wagon(const std::vector<Treasure> &contentDown, const std::vector<Treasure> &contentUp)
    : m_contentDown(contentDown), m_contentUp(contentUp)
{

}

// Setters
void Wagon::setContentDown(const std::vector<Treasure>& newContentDown)
{
    m_contentDown = newContentDown;
}

// Other methods
void Wagon::addContentUp(const Treasure t)
{
    m_contentUp.push_back(t);

}

void Wagon::addContentDown(Treasure t)
{
    m_contentDown.push_back(t);
}

void Wagon::clearContentDown()
{
    m_contentDown.clear();
}
/*this function returns a random reasure of Type type from
m_contentUp,and removes it from m_contentUp,and if no such Treasure is found the function returns a
Treasure of value 0 and tye MONEYBAG,and doesent change m_contentUp*/
Treasure Wagon::takeContentUp(TreasureType type)
{
    Treasure r;
    std::vector<Treasure>tmp;
    for(int i=0;i<m_contentUp.size();i++){
        if(m_contentUp[i].getType()==type)
            tmp.push_back(m_contentUp[i]);

    }
    if(tmp.size()>0){
        int index=QRandomGenerator::global()->bounded((int)tmp.size());
        r=tmp[index];
        m_contentUp.erase(std::find(m_contentUp.begin(),m_contentUp.end(),r));
        return r;
    }
    return Treasure(0,TreasureType::MONEYBAG);
}
/*this function returns a random reasure of Type type from
m_contentDown,and removes it from m_contentDown,and if no such Treasure is found the function returns a
Treasure of value 0 and tye MONEYBAG,and doesent change m_contentDown*/
Treasure Wagon::takeContentDown(TreasureType type)
{
    Treasure r;
    std::vector<Treasure>tmp;
    for(int i=0;i<m_contentDown.size();i++){
        if(m_contentDown[i].getType()==type)
            tmp.push_back(m_contentDown[i]);

    }
    if(tmp.size()>0){
        int index=QRandomGenerator::global()->bounded((int)tmp.size());
        r=tmp[index];
        m_contentDown.erase(std::find(m_contentDown.begin(),m_contentDown.end(),r));
        return r;
    }
    return Treasure(0,TreasureType::MONEYBAG);
}

int Wagon::numberOfTreasureInWagon(TreasureType type) const
{
    return std::count_if(m_contentDown.begin(), m_contentDown.end(), [type](auto treasure) { return treasure.getType() == type; });
}

std::string Wagon::toString()
{
    std::string r="myContentUp:\n";
    for(auto begin=m_contentUp.begin();begin!=m_contentUp.end();begin++)
        r+=begin->toString()+", ";
    r+="\nMyContentDown:\n";
    for(auto begin=m_contentDown.begin();begin!=m_contentDown.end();begin++)
        r+=begin->toString()+", ";
    return r;
}
