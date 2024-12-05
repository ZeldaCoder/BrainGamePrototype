#include <ostream>
#include "TileState.h"
#include <vector>
#pragma once
// coordinate system Point
struct Tile {
  int x;
  int y;
  TileState displayedState;
  std::vector<TileState> states;

  // Comparison operator
  bool operator==(const Tile &other) const {
    return x == other.x && y == other.y;
  }

  // add two tiles to get a nearby tile
  Tile operator+(const Tile &other) const {
    Tile result;
    result.x = this->x + other.x; // Add the x components
    result.y = this->y + other.y; // Add the y components
    return result;
  }

  bool ContainsState(TileState state) {
    bool doesContain = false;
    for (TileState s : states) {
      if (s == state) {
        doesContain = true;
        break;
      }
    }

    return doesContain;
  }

  void CalcStateWithHighPriority() {
    displayedState = RegTile;
    for (TileState s : states) {
      if (s > displayedState) {
        displayedState = s;
      }
    }
  }

  void AddState(TileState state) {
    states.push_back(state);
    CalcStateWithHighPriority();
  }

  // Contains states other than the display state
  void RemoveState(TileState state) {
    std::vector<TileState>::iterator stateIter;

    for (stateIter = states.begin(); stateIter != states.end(); stateIter++) {
      if (*stateIter == state) {
        states.erase(stateIter);
        break;
      }
    }

    CalcStateWithHighPriority();
  }
};

std::ostream &operator<<(std::ostream &os, const Tile& tile);