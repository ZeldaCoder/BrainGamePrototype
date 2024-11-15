#include "Tile.h"

// Forward Declares
class BaseTrap;


class Lever {
public:
  // Constructor
  Lever(Tile* t);

private:
  /*
   * Instance Variables
   */

  static int boardValue; // Number on the board
  Tile currentTile; // position on the board
  BaseTrap* activeTrap; // trap that the lever is connected to
  bool isActivated = false; // whether the lever is activated or not

  /*
  * Methods
  */
  
  void SetRandomTrap();

public:

  /*
   * Methods
   */

  void SetCurrentTile(Tile newPos);
  Tile GetCurrentTile();

  static int GetLeverValue() {
    return boardValue;
  };
  

};

// Set static board value
int Lever::boardValue = 5;