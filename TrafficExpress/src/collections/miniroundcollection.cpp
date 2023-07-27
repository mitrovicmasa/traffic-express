#include "../../headers/collections/miniroundcollection.h"

MiniRoundCollection::MiniRoundCollection() = default;

MiniRoundCollection::MiniRoundCollection(std::vector<MiniRound *> &other) {
  for (MiniRound *mr : other) this->push_back(mr);
}

MiniRoundCollection::MiniRoundCollection(const MiniRoundCollection &other) {
  for (MiniRound *mr : other)
    this->push_back(new MiniRound(mr->getMiniRoundType()));
}
