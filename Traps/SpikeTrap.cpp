#include "SpikeTrap.h"
#include "../Gameboard/Board.h"
#include <iostream>

SpikeTrap::SpikeTrap() {
  trapName = "Spiked Trap";

}

void SpikeTrap::SetRandomAffectedTiles(Board* b) {
  std::vector<Tile*> trappedTiles;

  // Randomize the tiles
  int numOfTrappedTiles = rand() % b->GetNumOfTiles() / 4; // Only cover up to 25% of the tiles
  for (int i = 0; i < numOfTrappedTiles; i++) {
    // Get a random tile
    Tile* possibleTile = b->GetRandomBoardTile();

    // Check if tile is nearby other trapped tiles
    if (i >= 1) {
      Tile* previousTile = trappedTiles.back();
      while ((previousTile->x == possibleTile->x || previousTile->x == possibleTile->x + 1 || previousTile->x == possibleTile->x - 1)&&(previousTile->y == possibleTile->y || previousTile->y == possibleTile->y + 1 || previousTile->y == possibleTile->y - 1)) {
        possibleTile = b->GetRandomBoardTile();
      } 
    }

    // if it isn't then add the tile to the list
    trappedTiles.push_back(possibleTile);
  }

  if (numOfTrappedTiles <= 0) {
      std::cout << "No traps were activated" << std::endl;
  } 

  SetAffectedTiles(trappedTiles);
}


void SpikeTrap::SetChosenAffectedTiles(Board* b) {
  std::vector<Tile*> trappedTiles;

  // Randomize the tiles
  int numOfTrappedTiles = rand() % b->GetNumOfTiles() / 4; // Only cover up to 25% of the tiles
  for (int i = 0; i < numOfTrappedTiles; i++) {
    // Get a random tile
    Tile* possibleTile = b->GetRandomBoardTile();

    // Check if tile is nearby other trapped tiles
    if (i >= 1) {
      Tile* previousTile = trappedTiles.back();
      if (previousTile->x == possibleTile->x || previousTile->x == possibleTile->x + 1 || previousTile->x == possibleTile->x - 1) {
        possibleTile = b->GetRandomBoardTile();
      } else if (previousTile->y == possibleTile->y || previousTile->y == possibleTile->y + 1 || previousTile->y == possibleTile->y - 1) {
        possibleTile = b->GetRandomBoardTile();
      }
    }

    // if it isn't then add the tile to the list
    trappedTiles.push_back(possibleTile);
  }

  if (numOfTrappedTiles <= 0) {
      std::cout << "No traps were activated" << std::endl;
  } 

  SetAffectedTiles(trappedTiles);
}