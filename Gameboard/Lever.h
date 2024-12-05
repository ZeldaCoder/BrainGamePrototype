#include "Tile.h"
#include <vector>
#pragma once

class BaseTrap;

class Lever {
public:
  // Constructor
  Lever(Tile t);

private:
  /*
   * Instance Variables
   */

  inline static int boardValue = 5; // Number on the board
  Tile currentTile; // position on the board
  // bool isActivated = false; // whether the lever is activated or not

  /*
  * Methods
  */
  
 

public:

  /*
   * Methods
   */

  BaseTrap* SetRandomTrap();

  void SetCurrentTile(Tile newPos);
  Tile GetCurrentTile();

  inline static int GetLeverValue() {
    return Lever::boardValue;
  }
};

