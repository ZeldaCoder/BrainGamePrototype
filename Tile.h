#include <iostream>
#pragma once
// coordinate system Point
struct Tile {
  int x;
  int y;
  int boardValue;

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

  std::iostream &operator<<(std::iostream &os) {
    std::cout << "(" << this->x << ", " << this->y << ")";
    return os;
  }

};