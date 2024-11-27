# include "Lever.h"
# include "Tile.h"
# include "BaseTrap.h"

Lever:: Lever(Tile tile) {
  currentTile = tile;
  
}

Tile Lever::GetCurrentTile() {
  return currentTile;
}

void Lever::SetCurrentTile(Tile newTile) {
  currentTile = newTile;
}

BaseTrap* Lever::SetRandomTrap() {
  int trapChoice = rand() % 5;
  BaseTrap* t = nullptr;
  if (trapChoice == 0) {
    t = new BaseTrap();
  } else if (trapChoice == 1) {
    t = new BaseTrap();
  } else {
     t = new BaseTrap();
  }
 

  return t;
}