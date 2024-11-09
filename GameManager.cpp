#include "GameManager.h"
#include "Board.h"
#include "player.h"
#include <iostream>

GameManager::GameManager() {
  // Create players
  players = AddPlayers();

  // Create Board
  gameBoard = new Board();

  // Set init player positions
  for (Player *p : players) {
    gameBoard->SetRandomPlayerLocation(p);
  }
}

void GameManager::Play() {
  // Game loop
  if (numOfTurns == 0) {
    std::cout << "Game started!" << std::endl;
  }

  while (numOfTurns < 12) {
    gameBoard->DisplayBoard();
    NextTurn();
  }
}

/**
  Main gameplay loop
*/
void GameManager::NextTurn() {
  int playerTurn = numOfTurns % players.size();
  Player *currentPlayer = players[playerTurn];
  currentPlayer->Action(gameBoard);
  numOfTurns++;
}

std::vector<Player *> GameManager::AddPlayers() {
  // Ask for number of players
  std::cout << "How many players are playing(1-4)? ";
  int numPlayers;
  std::cin >> numPlayers;

  if (numPlayers < 1) {
    numPlayers = 1;
  } else if (numPlayers > 4) {
    numPlayers = 4;
  }

  std::vector<Player *> playerList;

  for (int i = 0; i < numPlayers; i++) {
    Player *newPlayer = new Player();
    newPlayer->SetBoardValue(8 + i);
    playerList.push_back(newPlayer);
  }

  std::cout << std::endl;

  for (Player *p : playerList) {
    std::cout << p->GetName() << ": " << p->GetBoardValue() << std::endl;
  }

  std::cout << std::endl;

  return playerList;
}