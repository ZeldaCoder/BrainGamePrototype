#include "Tile.h"

std::ostream &operator<<(std::ostream &os, const Tile& tile) {
  os << "(" << tile.x << ", " << tile.y << ")";
  return os;
}