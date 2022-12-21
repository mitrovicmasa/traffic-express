#ifndef PLAYERSTATSCOLLECTION_H
#define PLAYERSTATSCOLLECTION_H

#include <playerstats.h>



class PlayerStatsCollection:public std::vector<PlayerStats*>
{
public:
    PlayerStatsCollection();
    PlayerStatsCollection(std::vector<PlayerStats*>&);

     PlayerStatsCollection(const PlayerStatsCollection&);
};

#endif // PLAYERSTATSCOLLECTION_H
