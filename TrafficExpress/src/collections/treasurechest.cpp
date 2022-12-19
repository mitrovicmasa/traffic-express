#include "../../headers/collections/treasurechest.h"

TreasureChest::TreasureChest()
{

}

TreasureChest::TreasureChest(vector<Treasure *> vt)
    :TreasureChest(TreasureChest())
{
    for(Treasure*t:vt)
        this->push_back(t);
}
