#include "LazerTrap.h"
#include "../Gameboard/Board.h"
#include <iostream> // delete after debuging

LazerTrap::LazerTrap() {
  trapName = "Lazer Trap";
}

void LazerTrap::SetRandomAffectedTiles(Board *b) {
  std::vector<Tile*> trappedTiles;
  std::vector<Tile> tiles = b->GetAllTiles();

  int horiOrVert = rand() % 2;

  if (horiOrVert == 0) {
    // Horizontal lazer
    
    // get a random row
    int row = rand() % b->GetBoardHeight();
    std::cout << "row: " << row << std::endl;


    // find all tiles in the row
    for (Tile tile : tiles) {
      if (tile.y == row) {
        Tile* tilePtr = b->GetBoardTile(tile);
        trappedTiles.push_back(tilePtr);
        std::cout << tile << std::endl;
      }
    }
  } else {
    // Vertical lazer

    // get a random column
    int column = random() % b->GetBoardWidth();
    std::cout << "column: " << column << std::endl;

    // find all tiles in the column
    for (Tile tile : tiles) {
      if (tile.x == column) {
        Tile* tilePtr = b->GetBoardTile(tile);
        trappedTiles.push_back(tilePtr);
        std::cout << tile << std::endl;
      }
    }
  }

  SetAffectedTiles(trappedTiles);
}

void LazerTrap::SetChosenAffectedTiles(Board *b) {
  std::vector<Tile*> trappedTiles;

  int horiOrVert = rand() % 2;

  if (horiOrVert == 0) {
    // Horizontal lazer

    // get a random row
    int row = rand() % b->GetBoardHeight();


    // find all tiles in the row
    for (Tile tile : b->GetAllTiles()) {
      if (tile.y == row) {
        Tile* tilePtr = b->GetBoardTile(tile);
        trappedTiles.push_back(tilePtr);
        std::cout << tile << std::endl;
      }
    }
  } else {
    // Vertical lazer

    // get a random column
    int column = random() % b->GetBoardWidth();

    // find all tiles in the column
    for (Tile tile : b->GetAllTiles()) {
      if (tile.x == column) {
        Tile* tilePtr = b->GetBoardTile(tile);
        trappedTiles.push_back(tilePtr);
        std::cout << tile << std::endl;
      }
    }
  }

  SetAffectedTiles(trappedTiles);
}