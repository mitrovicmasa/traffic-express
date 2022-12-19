#include "../../headers/collections/wagonarray.h"

WagonArray::WagonArray()
{

}

WagonArray::WagonArray(const WagonArray &other)
{
    for(Wagon*w:other){
        this->push_back(new Wagon(w->getContentUp(),w->getContentDown(),w->getPlayersUp(),w->getPlayersDown()));
    }
}
