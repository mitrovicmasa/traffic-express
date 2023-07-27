#ifndef MINIROUNDCOLLECTION_H
#define MINIROUNDCOLLECTION_H

#include <miniround.h>

#include <vector>

class MiniRoundCollection : public std::vector<MiniRound*> {
 public:
  MiniRoundCollection();
  MiniRoundCollection(std::vector<MiniRound*>&);

  MiniRoundCollection(const MiniRoundCollection&);
};

#endif  // MINIROUNDCOLLECTION_H
