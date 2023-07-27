#ifndef PLAYERGROUP_H
#define PLAYERGROUP_H

#include <player.h>

class PlayerGroup : public std::vector<Player*> {
 public:
  PlayerGroup();
  PlayerGroup(std::vector<Player*>&);
  // this is a copy constructor
  PlayerGroup(const PlayerGroup& other);
};

#endif  // PLAYERGROUP_H
