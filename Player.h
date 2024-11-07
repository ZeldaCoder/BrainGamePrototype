#include <string>

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
  std::string
      name; // Gets outputted for winner or who died or who used power-up
  int movementSpeed = 1;
  bool canMoveDiagonally = false;

  int currentTilePosition[2] = {0, 0};

  /*
   * Methods
   */

  int* Move();

public:
  /*
   * Accessors and Mutators
   */

  int GetHealth();
  void SetHealth(int newHealth);

  std::string GetName();
  void SetName(std::string newName);

  int GetBoardValue();
  void SetBoardValue(int newBoardValue);

  int* getCurrentTilePosition();

  /*
  * Methods
  */

  void Action();
};