# include "Lever.h"
# include "Tile.h"

Lever:: Lever (Tile *tile) {
  this->currentTile = *tile;
}

Tile Lever::GetCurrentTile() {
  return currentTile;
}