#include "../../headers/collections/roundcardcollection.h"

RoundCardCollection::RoundCardCollection() = default;

RoundCardCollection::RoundCardCollection(std::vector<RoundCard *> &rcv) {
  for (auto rc : rcv) this->push_back(rc);
}

RoundCardCollection::RoundCardCollection(const RoundCardCollection &rcc) {
  for (auto rc : rcc) {
    this->push_back(
        new RoundCard(rc->typeOfRoundCard(), rc->event(), rc->getMiniRounds()));
  }
}
