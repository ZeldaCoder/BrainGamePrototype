#include <string>
#include "Tile.h"

class Board;

class Player {
public:
  // Constructor
  Player();

private:
  /*
   * Instance Variables
   */
  int boardValue; // Number on the board
  int health;
  int maxHealth = 3;
  bool isAlive = true;
  std::string name; // Gets outputted for winner or who died or who used power-up
  int movementSpeed = 1;
  bool canMoveDiagonally = false;

  Tile currentTilePosition;
  Tile previousTilePosition;

  // Base Directions
  const std::string DIR_UP = "w";
  const std::string DIR_DOWN = "x";
  const std::string DIR_RIGHT = "d";
  const std::string DIR_LEFT = "a";

  // Diagonal Directions
  const std::string DIR_UL = "q";
  const std::string DIR_UR = "e";
  const std::string DIR_DL = "z";
  const std::string DIR_DR = "c";

  // Interaction Input
  const std::string ACT_PU = "c";
  const std::string INTERACT = "i";
  const std::string ACT_BLOCK = "s";

  /*
   * Methods
   */

  void Move(Board* b, std::string dir);
  void Interact(Board* b);

public:
  /*
   * Accessors and Mutators
   */


  std::string GetName();
  void SetName(std::string newName);

  int GetBoardValue();
  void SetBoardValue(int newBoardValue);

  Tile GetCurrentTilePosition();
  void SetCurrentTilePosition(int newX, int newY);

  Tile GetPreviousTilePosition();
  void SetPreviousTilePosition(int newX, int newY);

  /*
  * Methods
  */

  void Action(Board* b);

  bool GetIsAlive();
  void SetIsAlive(bool newIsAlive);

  void SetHealth(int newHealth);
  int GetHealth();

  int GetMaxHealth();

};