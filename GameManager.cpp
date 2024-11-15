#include "GameManager.h"
#include "Board.h"
#include "player.h"
#include <iostream>

GameManager::GameManager() {
  // Create players
  players = AddPlayers();

  // Set Player health
  int inputHealth;
  std::cout << "How much health do you want each player to have (MAX: " << players[0]->GetMaxHealth() << ")? ";
  std::cin >> inputHealth;

  if (inputHealth < 1) {
    inputHealth = 1;
  } else if (inputHealth > players[0]->GetMaxHealth()) {
    inputHealth = players[0]->GetMaxHealth();
  }
  for (Player *p : players) {
    p->SetHealth(inputHealth);
  };

  // Create Board
  gameBoard = new Board();

  // Optional removal of up to a quarter of the tiles
  gameBoard->DeleteRandomTile();

  // Set init player positions
  for (int i = 0; i < players.size(); i++) {
    gameBoard->SetRandomPlayerLocation(players[i]);
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
  // Get the levers of the board
  std::vector<Lever*> ls = gameBoard->GetLevers();
  std::cout << ls.size() << std::endl;
  if (ls.size() < 1) {
    std::cout << "Spawning lever" << std::endl;
    gameBoard->SpawnRandomLevers();
  }
  
  // Loop through all players and make them do their actions
  int playerTurn = numOfTurns % players.size();
  Player *currentPlayer = players[playerTurn];
  currentPlayer->Action(gameBoard);

  // Move to next round
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