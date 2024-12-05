# include "BaseTrap.h"
# include "../Runners/GameManager.h"
# include "../Gameboard/Board.h"
# include <iostream>

BaseTrap::BaseTrap() {
  trapName = "Base Trap";
}

void BaseTrap::SetTurnsActive() {
  numOfTurnsActive = rand() % maxTurnsActive + minTurnsActive;
}

void BaseTrap::TrapCountdown(int currentTurnNum) {
  std::cout << currentTurnNum << std::endl;
  std::cout << TurnWhenActivated << std::endl;
  
  int turnsCounted = currentTurnNum - TurnWhenActivated;
  std::cout << "Trap Countdown: " << turnsCounted << std::endl;
  if (turnsCounted == numOfTurnsWarning) {
    // activate the trap
    for (Tile* trappedTile : affectedTiles) {
      trappedTile->AddState(TileState::TrapTile);
      trappedTile->RemoveState(TileState::WarningTile);
    }
  } else if (turnsCounted < numOfTurnsWarning) {
    // warn the player of potential trap
    for (Tile* trappedTile : affectedTiles) {
      trappedTile->AddState(TileState::WarningTile);
    }
  }
  
  // Disable the trap
  if (turnsCounted >= (numOfTurnsActive + numOfTurnsWarning)) {
    std::cout << "Trap Disabled" << std::endl;
    
    // reset the tiles that were trapped
    for (Tile* trappedTile : affectedTiles) {
      trappedTile->RemoveState(TileState::TrapTile);
    }

    isActivated = false;
  }
}

std::vector<Tile *> BaseTrap::GetAffectedTiles() {
  return affectedTiles;
}

void BaseTrap::SetAffectedTiles(std::vector<Tile *> newTiles) {
  affectedTiles = newTiles;
}

void BaseTrap::SetWhenActivated(int activatedTurn) {
  TurnWhenActivated = activatedTurn;
}

bool BaseTrap::GetIsActivated() {
  return isActivated;
}

void BaseTrap::SetRandomAffectedTiles(Board* b) {
  std::vector<Tile*> trappedTiles;
  
  // Randomize the tiles
  int numOfTrappedTiles = rand() % b->GetNumOfTiles() / 4; // Only cover up to 25% of the tiles
  for (int i = 0; i < numOfTrappedTiles; i++) {
      trappedTiles.push_back(b->GetRandomBoardTile());
  }

  if (trappedTiles.size() <= 0) {
      std::cout << "No traps were activated" << std::endl;
  } 
  
  SetAffectedTiles(trappedTiles);
}

void BaseTrap::SetChosenAffectedTiles(Board* b) {
  std::cout << "Enter the tiles you want to activate (x, y): " << std::endl;
  
  std::vector<Tile*> trappedTiles;

  // Randomize the tiles
  int numOfTrappedTiles = rand() % b->GetNumOfTiles() / 4; // Only cover up to 25% of the tiles
  for (int i = 0; i < numOfTrappedTiles; i++) {
      trappedTiles.push_back(b->GetRandomBoardTile());
  }

  if (trappedTiles.size() <= 0) {
      std::cout << "No traps were activated" << std::endl;
  } 

  SetAffectedTiles(trappedTiles);
}

void BaseTrap::InitTrap() {
  // Set the how long the trap lasts
  SetTurnsActive();

  std::cout << trapName << " has been activated!" << std::endl;
  std::cout << numOfTurnsActive + numOfTurnsWarning << " turns until it deactivates" << std::endl;
  isActivated = true;
}