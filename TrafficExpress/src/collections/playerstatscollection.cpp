#include "../../headers/collections/playerstatscollection.h"

PlayerStatsCollection::PlayerStatsCollection() = default;

PlayerStatsCollection::PlayerStatsCollection(std::vector<PlayerStats *> &psv) {
  for (PlayerStats *ps : psv) this->push_back(ps);
}

PlayerStatsCollection::PlayerStatsCollection(const PlayerStatsCollection &psc) {
  for (PlayerStats *ps : psc) {
    this->push_back(new PlayerStats(ps->getPlayer(), true));
  }
}
