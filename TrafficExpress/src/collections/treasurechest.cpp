#include "../../headers/collections/treasurechest.h"

TreasureChest::TreasureChest()
{

}

TreasureChest::TreasureChest(vector<Treasure *> vt)
{
    for(Treasure*t:vt)
        this->push_back(t);
}

TreasureChest::TreasureChest(const TreasureChest &other)
{
    for(Treasure*t:other){
        this->push_back(new Treasure(t->getValue(),t->getType()));
    }
}
