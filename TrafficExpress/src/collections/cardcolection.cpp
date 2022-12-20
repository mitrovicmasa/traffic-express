#include "../../headers/collections/cardcolection.h"

CardColection::CardColection()
    :std::vector<Card*>()
{

}

CardColection::CardColection(std::vector<ActionCard *> cards)
{
    for(Card* c: cards){
        this->push_back(c);
    }
}

CardColection::CardColection(const CardColection &other)
{
    for(Card* c: other){
        this->push_back(c->Copy());
    }
}

CardColection CardColection::Copy()
{
    CardColection cc=CardColection();
    for(Card* c:(*this)){
        cc.push_back(c->Copy());

    }
    return cc;

}
