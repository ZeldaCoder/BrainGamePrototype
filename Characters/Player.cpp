#include "player.h"
#include "../Gameboard/Board.h"
#include "../Gameboard/Lever.h"
#include <iostream>

Player::Player() {
  // Init Player name
  std::string inputName;
  std::cout << "What is your name? ";
  std::cin >> inputName;
  name = inputName;
}

void Player::Move(Board *b, std::string dir) {
  Tile newDir = {0, 0, TileState::LeverTile};

  // Find direction we want to move in based on input
  if (dir == DIR_UP) {
    newDir.y = -1;
  } else if (dir == DIR_DOWN) {
    newDir.y = 1;
  } else if (dir == DIR_LEFT) {
    newDir.x = -1;
  } else if (dir == DIR_RIGHT) {
    newDir.x = 1;
  }

  // Set the new destination then check it
  Tile newPosition = currentTilePosition + newDir;

  // check if there is no player or hole there
  if (b->IsTileAvailable(newPosition)) {
    // Set previous position to clear the old one on the board
    previousTilePosition = currentTilePosition;

    // Update currentTilePosition
    currentTilePosition = newPosition;

    // Applies harmful effect if is a trap or hole
    b->TileHarmful(this);

    // Move the Player and Update the board
    b->SetPlayerLocation(this);

  } else {
    std::cout << "You can't move there!" << std::endl;
    this->Action(b);
  }
}

void Player::Action(Board *b) {
  if (GetIsAlive()) {
    std::string actionInput;

    // State whos turn it is
    std::cout << "It is " << name << " turn!" << std::endl;

    // List PowerUps
    std::cout << "You have: " << std::endl;

    // Ask for action
    std::cout << "What do you want to do? ";
    std::cin >> actionInput;

    // Based on input do these things
    if (actionInput == DIR_DOWN || actionInput == DIR_UP ||
        actionInput == DIR_RIGHT || actionInput == DIR_LEFT) {
      Move(b, actionInput);
    }

    if (actionInput == INTERACT && b->GetBoardTile(GetCurrentTilePosition())->ContainsState(TileState::LeverTile)) {
      Interact(b);
    }
  } else {
    std::cout << name << " is dead! Moving on to the next player" << std::endl;

    // remove player from the board (When player dies in a hole, make a tile there)
    Tile* boardTile = b->GetBoardTile(GetCurrentTilePosition());
    if (boardTile->ContainsState(TileState::PlayerTile)) {
      boardTile->RemoveState(TileState::PlayerTile);
    }
  }
}

void Player::SetName(std::string newName) { name = newName; }

std::string Player::GetName() { return name; }

void Player::SetBoardValue(int value) { boardValue = value; }

int Player::GetBoardValue() { return boardValue; }

Tile Player::GetCurrentTilePosition() { return currentTilePosition; }

void Player::SetCurrentTilePosition(int newX, int newY) {
  currentTilePosition.x = newX;
  currentTilePosition.y = newY;
}

Tile Player::GetPreviousTilePosition() { return previousTilePosition; }

void Player::SetPreviousTilePosition(int newX, int newY) {
  previousTilePosition.x = newX;
  previousTilePosition.y = newY;
}

bool Player::GetIsAlive() {
  if (health < 1) {
    isAlive = false;
  } else {
    isAlive = true;
  }

  return isAlive;
}

int Player::GetHealth() { return health; }

void Player::SetHealth(int newHealth) {
  if (newHealth < maxHealth) {
    health = newHealth;
  }
}

int Player::GetMaxHealth() { return maxHealth; }

void Player::Interact(Board* b) {
  // Get the tile that shares the power up
  Tile *bPos = b->GetBoardTile(GetCurrentTilePosition());

  // Remove the trap from the tile (Display wise)
  bPos->RemoveState(TileState::LeverTile);
  std::vector<Lever*> ls = b->GetLevers();

  for (int i = 0; i < ls.size(); i++) {
    std::cout << ls[i]->GetCurrentTile() << std::endl;
  }

  // loop through the levers and check if the current tile is a lever
  for (auto leverIter = ls.begin(); leverIter != ls.end();) {
    if ((*leverIter)->GetCurrentTile() == GetCurrentTilePosition()) {
      // Get access to the lever we activated then remove it (Code wise)
      b->ApplyTraps(leverIter);
      break;
    } else {
      ++leverIter;
    }
  } 
}