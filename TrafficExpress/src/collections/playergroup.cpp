#include "../../headers/collections/playergroup.h"

PlayerGroup::PlayerGroup()
= default;

PlayerGroup::PlayerGroup(std::vector<Player *> &vp)
{
    for(Player*p:vp)
        this->push_back(p);
}

PlayerGroup::PlayerGroup(const PlayerGroup &other)
{

    for(Player* p:other){
        this->push_back(new Player(p->isItMyMove(),p->id(),p->hand(),p->deck(),p->bullet_deck(),p->positionInTrain(),
                                   p->roof(),p->treasure()));

    }

}


