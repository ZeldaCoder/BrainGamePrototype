#include "Tile.h"
#include <vector>
#include <string>
#pragma once

class BaseTrap {
public:
  // Constructor
  BaseTrap();

protected:
  /*
   * Instance Variables
   */


  std::string trapName = "Base Trap"; // changes depending on child trap


  inline static int activeTrapVal = 4; // Number on the board that can harm players and thoughts
  inline static int warningTrapVal = 3; // Number on the board that can warns players and thoughts of traps

  int maxTurnsActive = 5; // adustable for each child trap
  int minTurnsActive = 2; // adustable for each child trap

  int numOfTurnsActive; // how long will each trap (4) remain
  int numOfTurnsWarning = 2; // how long will each warning (3) remain

  int TurnWhenActivated = 0; // What turn was the lever pulled?

  std::vector<Tile*> affectedTiles; // What tiles will be affected by the trap  

  bool isActivated; // count turns only when the specific trap is active

  // Randomly determine how long each trap should be active
  void SetTurnsActive();
  

public:
  /*
   * Methods
   */
  inline static int GetActiveTrapVal() { return BaseTrap::activeTrapVal; }
  inline static int GetWarningTrapVal() { return BaseTrap::warningTrapVal; }

  void SetWhenActivated(int activatedTurn);


  // If the trap is activated then keep track of turn number to see if it should still be active
  void TrapCountdown(int currentTurnNum);
  void SetAffectedTiles(std::vector<Tile*> newTiles); 
  std::vector<Tile*> GetAffectedTiles();

  bool GetIsActivated();
  
};