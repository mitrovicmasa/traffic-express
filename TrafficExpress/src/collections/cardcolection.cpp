#include "../../headers/collections/cardcolection.h"

CardColection::CardColection()
    :std::vector<Card*>()
{

}

CardColection CardColection::Copy()
{
    CardColection cc=CardColection();
    for(Card* c:(*this)){
        cc.push_back(c->Copy());

    }
    return cc;

}
