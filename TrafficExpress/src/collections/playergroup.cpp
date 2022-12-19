#include "../../headers/collections/playergroup.h"

PlayerGroup::PlayerGroup()
{

}

PlayerGroup::PlayerGroup(std::vector<Player *> &vp)
{
    for(Player*p:vp)
        this->push_back(p);
}
