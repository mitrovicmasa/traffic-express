#ifndef PLAYERPERSPECTIVECOLLECTION_H
#define PLAYERPERSPECTIVECOLLECTION_H

#include <playerperspective.h>

class PlayerPerspectiveCollection : public std::vector<PlayerPerspective*> {
 public:
  PlayerPerspectiveCollection();
};

#endif  // PLAYERPERSPECTIVECOLLECTION_H
