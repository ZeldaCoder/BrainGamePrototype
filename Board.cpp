#include "Board.h"
#include "Lever.h"
#include "player.h"
#include "BaseTrap.h"
#include "GameManager.h"
#include <iostream>
#include <algorithm>

Board::Board() {
  // Initialize the board with empty spaces
  int h, w;
  std::cout << "How wide do you want the board to be(Max: " << MAX_WIDTH
            << " and Min: " << MIN_WIDTH << ")? ";
  std::cin >> w;
  std::cout << "How tall do you want the board to be(Max " << MAX_HEIGHT
            << " and Min: " << MIN_WIDTH << ")? ";
  std::cin >> h;

  // Cap the width and height
  if (w > MAX_WIDTH) {
    w = MAX_WIDTH;
  } else if (w < MIN_WIDTH) {
    w = MIN_WIDTH;
  }

  if (h > MAX_HEIGHT) {
    h = MAX_HEIGHT;
  } else if (h < MIN_HEIGHT) {
    h = MIN_HEIGHT;
  }

  boardWidth = w;
  boardHeight = h;

  boardArray = InitBoard(h, w);
}

std::vector<Tile> Board::InitBoard(int h, int w) {
  // Create an array of pointers to integers
  std::vector<Tile> tiles;

  for (int i = 0; i < h; i++) {
    for (int ii = 0; ii < w; ii++) {
      Tile newTile;
      newTile.x = ii;
      newTile.y = i;
      newTile.boardValue = 1;

      tiles.push_back(newTile);
    }
  }

  return tiles;
}

void Board::DisplayBoard() {
  for (int i = 0; i < boardHeight; i++) {
    std::cout << "|";
    for (int ii = 0; ii < boardWidth; ii++) {
      if (boardArray[i * boardWidth + ii].boardValue == 1) {
        std::cout << " -- ";
      } else if (boardArray[i * boardWidth + ii].boardValue == 0) {
        std::cout << "    ";
      } else if (boardArray[i * boardWidth + ii].boardValue < 10 &&
                 boardArray[i * boardWidth + ii].boardValue > 1) {
        std::cout << " " << boardArray[i * boardWidth + ii].boardValue << "  ";
      } else if (boardArray[i * boardWidth + ii].boardValue >= 10) {
        std::cout << " " << boardArray[i * boardWidth + ii].boardValue << " ";
      }
    }
    std::cout << "|" << std::endl;
  }
}

void Board::SetRandomPlayerLocation(Player *p) {
  // Get random location
  Tile *newPos = GetRandomBoardTile();

  // If there is nothing in that location, Move the player there
  if (newPos->boardValue == 1) {
    newPos->boardValue = p->GetBoardValue();
    p->SetCurrentTilePosition(newPos->x, newPos->y);
  }
}

void Board::SetPlayerLocation(Player *p) {
  // Say where the player moved
  std::cout << p->GetName() << " Has Moved to " << p->GetCurrentTilePosition() << std::endl;

  /*
  std::cout << p->GetName() << " has moved to " << p->GetCurrentTilePosition()
  << std::endl;
  */

  // Set the player location on the board
  for (int i = 0; i < boardArray.size(); i++) {
    if (boardArray[i] == p->GetCurrentTilePosition()) {
      if (boardArray[i].boardValue == 1) {
        boardArray[i].boardValue = p->GetBoardValue();
      } else {
        // If there is a trap or something else there add the values together so that the computer knows
        boardArray[i].boardValue += p->GetBoardValue();
      }
      
    }
  }

  // clear the previous location if
  // if that is the only thing on the square set it to one else set it to the
  // other object there
  Tile *previousLoc = GetBoardTile(p->GetPreviousTilePosition());

  if (previousLoc->boardValue - p->GetBoardValue() == 0) {
    // Nothing was there you can just set it back to a regular tile
    previousLoc->boardValue = 1;
  } else {
    // some other collectable was there don't get rid of it
    previousLoc->boardValue -= p->GetBoardValue();
  }
}

bool Board::IsTileAvailable(Tile position) {
  // Check is the player is trying to move out of bounds
  if (position.x > boardWidth || position.y < 0 || position.y > boardHeight ||
      position.y < 0) {
    return false;
  } else {
    Tile *bPos = GetBoardTile(position);

    // Check if the tile is already ocupied
    if (bPos->boardValue != 8 &&
        bPos->boardValue != 9 && bPos->boardValue != 10 &&
        bPos->boardValue != 11) {
      return true;
    } else {
      return false;
    }
  }
}

void Board::TileHarmful(Player *p) {

  Tile *bPos = GetBoardTile(p->GetCurrentTilePosition());

  int newHealth = p->GetHealth();

  // Check if the tile contains trap or hole
  if (bPos->boardValue == 4) {
    std::cout << "You hit a trap, you will lose a life!" << std::endl;
    newHealth--;
    p->SetHealth(newHealth);
  } else if (bPos->boardValue == 0) {
    std::cout << "You fell into a hole, you will lose a life!" << std::endl;
    newHealth--;
    p->SetHealth(newHealth);
  } else if (bPos->boardValue == 2) {
    int chanceForGood = rand() % 2;
    if (chanceForGood == 1) {
      std::cout << "You hit a rouge thought! Unlucky" << std::endl;
      newHealth--;
      p->SetHealth(newHealth);
    }
  }
}

Tile *Board::GetBoardTile(Tile givenTile) {
  // For all possible tiles, find the one that matches the given tile
  for (int i = 0; i < boardArray.size(); i++) {
    if (boardArray[i] == givenTile) {
      return &boardArray[i];
    }
  }

  // If couldn't find it return nullptr
  Tile *emptyTile = new Tile{0, 0, 0};
  return emptyTile;
}

Tile *Board::GetRandomBoardTile() {
  // Get a random tile
  int randTile = rand() % boardArray.size();

  // Check if the tile has anything on it
  while (boardArray[randTile].boardValue != 1) {
    randTile = rand() % boardArray.size();
  }

  // The momenent there is a normal tile return it
  return &boardArray[randTile];
}

void Board::DeleteRandomTile() {
  std::cout << "Do you want to delete random tiles from the board (y/n)? ";

  std::string input;
  std::cin >> input;

  // If chosen, delete random tiles
  if (input == "y" || input == "Y") {
    // chose how many tiles to delete
    int numOfTiles = (rand() % boardArray.size()) / 4;

    for (int i = 0; i < numOfTiles; i++) {
      // Get a random tile
      Tile *removedTile = GetRandomBoardTile();

      // Set it to unlandable
      removedTile->boardValue = 0;
    }
  }
}

void Board::SpawnRandomLevers() {
  // randomly choose how many levers to spawn
  int chanceOfLevers = (rand() % MAX_LEVERS) + 1;

  for (int i = 0; i < chanceOfLevers; i++) {
    // Get a random tile that doesn't have anything
    Tile *randomTile = GetRandomBoardTile();
    std::cout << *randomTile << std::endl;

    // Create a lever for that tile
    Lever* lever = new Lever(*randomTile);
    
    levers.push_back(lever);

    // Set location on the board
    randomTile->boardValue = Lever::GetLeverValue();
  }
}

std::vector<Lever*>& Board::GetLevers() { return levers; }

void Board::ApplyTraps(std::vector<Lever*>::iterator& leverIter) {
    Lever* l = (*leverIter);
    std::cout << l->GetCurrentTile() << std::endl;
    BaseTrap* t = l->SetRandomTrap();
    // List of traps made by the lever
    std::vector<Tile*> trappedTiles;

    // 50% chance of choosing the tiles
    int chance = rand() % 2;
    // Delete when make child trap specific selection
    chance = 0;
    if (chance == 0) {
        // Make this code trap specific 
        // Randomize the tiles
        int numOfTrappedTiles = rand() % boardArray.size() / 4; // Only cover up to 25% of the tiles
        for (int i = 0; i < numOfTrappedTiles; i++) {
            trappedTiles.push_back(GetRandomBoardTile());
        }
    } else {
        // Pick tiles you want to activate
    }
    // Apply the Trap that the lever has
    t->SetWhenActivated(GameManager::GetNumOfTurns());
    t->SetAffectedTiles(trappedTiles);
    GameManager::AddActivatedTrap(t);
    if (trappedTiles.size() <= 0) {
        std::cout << "No traps were activated" << std::endl;
    } 

    std::cout << (*leverIter)->GetCurrentTile() << std::endl; // Print before erase

    auto leverEnd = std::remove(levers.begin(), levers.end(), l);
  
    leverIter = levers.erase(leverEnd, levers.end());  // Erase and move iterator to the next element

    
    
    for (int i = 0; i < levers.size(); i++) {
        std::cout << levers[i]->GetCurrentTile() << std::endl; // Print the rest of the elements
    }

}