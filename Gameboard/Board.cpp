#include "Board.h"
#include "Lever.h"
#include "../Characters/player.h"
#include "../Traps/BaseTrap.h"
#include "../Runners/GameManager.h"
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
      newTile.AddState(TileState::RegTile);
      tiles.push_back(newTile);
    }
  }

  return tiles;
}

void Board::DisplayBoard() {
  for (int i = 0; i < boardHeight; i++) {
    std::cout << "|";
    for (int ii = 0; ii < boardWidth; ii++) {
      if (boardArray[i * boardWidth + ii].displayedState == TileState::RegTile) {
        std::cout << " - ";
      } else if (boardArray[i * boardWidth + ii].displayedState == TileState::HoleTile) {
        std::cout << "   ";
      } else if (boardArray[i * boardWidth + ii].displayedState == TileState::WarningTile) {
        std::cout << " ~ ";
      } else if (boardArray[i * boardWidth + ii].displayedState == TileState::TrapTile) {
        std::cout << " X ";
      } else if (boardArray[i * boardWidth + ii].displayedState == TileState::ThoughtTile) {
        std::cout << " T ";
      } else if (boardArray[i * boardWidth + ii].displayedState == TileState::LeverTile) {
        std::cout << " L ";
      } else if (boardArray[i * boardWidth + ii].displayedState == TileState::MBTile) {
        std::cout << " ? ";
      } else if (boardArray[i * boardWidth + ii].displayedState == TileState::PlayerTile) {
        // make some distinction between players
        std::cout << " P ";
      } 
    }
    std::cout << "|" << std::endl;
  }
}

void Board::SetRandomPlayerLocation(Player *p) {
  // Get random location
  Tile *newPos = GetRandomBoardTile();

  // If there is nothing in that location, Move the player there
  if (newPos->displayedState == TileState::RegTile) {
    newPos->AddState(TileState::PlayerTile);
    p->SetCurrentTilePosition(newPos->x, newPos->y);
  }
}

void Board::SetPlayerLocation(Player *p) {
  // Say where the player moved
  std::cout << p->GetName() << " Has Moved to " << p->GetCurrentTilePosition()
            << std::endl;

  // Set the player location on the board
  for (int i = 0; i < boardArray.size(); i++) {
    if (boardArray[i] == p->GetCurrentTilePosition()) {
      boardArray[i].AddState(TileState::PlayerTile);
      
    }
  }

  // clear the previous location if
  // if that is the only thing on the square set it to one else set it to the
  // other object there
  Tile *previousLoc = GetBoardTile(p->GetPreviousTilePosition());

  previousLoc->RemoveState(TileState::PlayerTile);

  
}

bool Board::IsTileAvailable(Tile position) {
  // Check is the player is trying to move out of bounds
  if (position.x > boardWidth || position.y < 0 || position.y > boardHeight ||
      position.y < 0) {
    return false;
  } else {
    Tile *bPos = GetBoardTile(position);

    // Check if the tile is already ocupied
    if (bPos->ContainsState(TileState::HoleTile) || bPos->ContainsState(TileState::PlayerTile)) {
      return false;
    } else {
      return true;
    }
  }
}

void Board::TileHarmful(Player *p) {

  Tile *bPos = GetBoardTile(p->GetCurrentTilePosition());

  int newHealth = p->GetHealth();

  // Check if the tile contains trap or hole
  if (bPos->displayedState == 
    TileState::TrapTile) {
    std::cout << "You hit a trap, you will lose a life!" << std::endl;
    newHealth--;
    p->SetHealth(newHealth);
  } else if (bPos->displayedState == TileState::HoleTile) {
    std::cout << "You fell into a hole, you will lose a life!" << std::endl;
    newHealth--;
    p->SetHealth(newHealth);
  } else if (bPos->displayedState == TileState::ThoughtTile) {
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
  Tile *emptyTile = new Tile{0, 0, TileState::RegTile};
  return emptyTile;
}

Tile *Board::GetRandomBoardTile() {
  // Get a random tile
  int randTile = rand() % boardArray.size();

  // Check if the tile has anything on it
  while (boardArray[randTile].displayedState != TileState::RegTile) {
    randTile = rand() % boardArray.size();
  }

  // The momenent there is a normal tile return it
  return &boardArray[randTile];
}

int Board::GetNumOfTiles() { return boardArray.size(); }

int Board::GetBoardWidth() { return boardWidth; }

int Board::GetBoardHeight() { return boardHeight; }

std::vector<Tile> Board::GetAllTiles() { return boardArray; }

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
      removedTile->AddState(TileState::HoleTile);
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
    randomTile->AddState(TileState::LeverTile);
  }
}

std::vector<Lever*>& Board::GetLevers() { return levers; }

void Board::ApplyTraps(std::vector<Lever*>::iterator& leverIter) {
    // get trap
    Lever* l = (*leverIter);
    BaseTrap* t = l->SetRandomTrap();

    // 50% chance of choosing the tiles
    int chance = rand() % 2;

    // Issue here <-----------------------------------------------------------
    if (chance == 0) {
        // randomly pick trapped tiles
        t->SetRandomAffectedTiles(this);
    } else {
        // Pick tiles you want to activate
        t->SetChosenAffectedTiles(this);
    }
    // Apply the Trap that the lever has
    t->SetWhenActivated(GameManager::GetNumOfTurns());
    GameManager::AddActivatedTrap(t);

    // Erase and move iterator to the next element
    auto leverEnd = std::remove(levers.begin(), levers.end(), l);
    leverIter = levers.erase(leverEnd, levers.end());  
}