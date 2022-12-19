#ifndef PLAYERGROUP_H
#define PLAYERGROUP_H

#include <player.h>



class PlayerGroup:public std::vector<Player*>
{
public:
    PlayerGroup();
    PlayerGroup(std::vector<Player*>&);
};

#endif // PLAYERGROUP_H
