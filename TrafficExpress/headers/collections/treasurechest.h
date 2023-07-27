#ifndef TREASURECHEST_H
#define TREASURECHEST_H
#include <treasure.h>

#include <vector>

class TreasureChest : public std::vector<Treasure*> {
 public:
  TreasureChest();
  TreasureChest(vector<Treasure*>);
  TreasureChest(const TreasureChest& other);
};

#endif  // TREASURECHEST_H
