#include "../../headers/collections/wagonarray.h"

WagonArray::WagonArray()
= default;

WagonArray::WagonArray(const WagonArray &other)
{
    for(Wagon*w:other){
        this->push_back(new Wagon(w->getContentUp(),w->getContentDown(),w->getPlayersUp(),w->getPlayersDown(), w->isLocomotive()));
    }
}
