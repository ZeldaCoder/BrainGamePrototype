#include "player.h"
#include "Board.h"
#include <iostream>

Player::Player() {
  // Init Player name
  std::string inputName;
  std::cout << "What is your name? ";
  std::cin >> inputName;
  name = inputName;
}

void Player::Move(Board *b, std::string dir) {
  int newDir[2] = {0, 0};

  // Find direction we want to move in based on input
  if (dir == DIR_UP) {
    newDir[1] = -1;
  } else if (dir == DIR_DOWN) {
    newDir[1] = 1;
  } else if (dir == DIR_LEFT) {
    newDir[0] = -1;
  } else if (dir == DIR_RIGHT) {
    newDir[0] = 1;
  }

  // Set the new destination then check it
  int newPosition[2] = {currentTilePosition[0] + newDir[0],
                        currentTilePosition[1] + newDir[1]};

  // check if there is no player or hole there
  if (b->IsTileAvailable(newPosition)) {
    // Set previous position to clear the old one on the board
    previousTilePosition[1] = currentTilePosition[1];
    previousTilePosition[0] = currentTilePosition[0];
    
    // Update currentTilePosition
    currentTilePosition[0] = newPosition[0];
    currentTilePosition[1] = newPosition[1];

    // Move the Player and Update the board
    b->SetPlayerLocation(this);

  } else {
    std::cout << "You can't move there!" << std::endl;
    this->Action(b);
  }
}

void Player::Action(Board *b) {
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
}

void Player::SetName(std::string newName) { name = newName; }

std::string Player::GetName() { return name; }

void Player::SetBoardValue(int value) { boardValue = value; }

int Player::GetBoardValue() { return boardValue; }

int *Player::GetCurrentTilePosition() { return currentTilePosition; }

void Player::SetCurrentTilePosition(int newX, int newY) {
  currentTilePosition[0] = newX;
  currentTilePosition[1] = newY;
}

int *Player::GetPreviousTilePosition() { return previousTilePosition; }

void Player::SetPreviousTilePosition(int newX, int newY) {
  previousTilePosition[0] = newX;
  previousTilePosition[1] = newY;
}