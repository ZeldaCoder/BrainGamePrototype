#include "Board.h"
#include "player.h"
#include <iostream>

Board::Board() {
  // Initialize the board with empty spaces
  int h, w;
  std::cout << "How wide do you want the board to be(Max: " << MAX_WIDTH
            << " and Min: " << MIN_WIDTH << ")? ";
  std::cin >> w;
  std::cout << "How tall do you want the board to be(Max " << MAX_HEIGHT
            << " and Min: " << MIN_WIDTH << ")? ";
  std::cin >> h;

  // Cap the width and height
  if (w > MAX_WIDTH) {
    w = MAX_WIDTH;
  } else if (w < MIN_WIDTH) {
    w = MIN_WIDTH;
  }

  if (w > MAX_HEIGHT) {
    h = MAX_HEIGHT;
  } else if (w < MIN_HEIGHT) {
    h = MIN_HEIGHT;
  }

  boardWidth = w;
  boardHeight = h;

  boardArray = InitBoard(h, w);
}

int **Board::InitBoard(int h, int w) {
  // Create an array of pointers to integers
  int **newBoard = new int *[h];

  // For each row, allocate memory for 'cols' integers
  for (int i = 0; i < h; ++i) {
    newBoard[i] = new int[w];
  }

  // Fill the array with values
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      newBoard[i][j] = 1;
    }
  }

  // Print the array
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      std::cout << newBoard[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Old print " << std::endl;

  // // Deallocate memory
  // for (int i = 0; i < h; ++i) {
  //   delete[] newBoard[i];
  // }

  // for (int i = 0; i < h; ++i) {
  //   for (int j = 0; j < w; ++j) {
  //     std::cout << newBoard[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // std::cout << "new print";

  // delete[] newBoard;

  return newBoard;
}

void Board::DisplayBoard() {
  for (int i = 0; i < boardHeight; i++) {
    std::cout << "|";
    for (int ii = 0; ii < boardWidth; ii++) {
      std::cout << " " << boardArray[i][ii] << " ";
    }
    std::cout << "|" << std::endl;
  }
}

void Board::SetRandomPlayerLocation(Player *p) {
  // Get random location
  int initX = rand() % boardWidth;
  int initY = rand() % boardHeight;

  // If there is nothing in that location, Move the player there
  if (boardArray[initY][initX] == 1) {
    boardArray[initY][initX] = p->GetBoardValue();
    p->SetCurrentTilePosition(initX, initY);
  }
}

void Board::SetPlayerLocation(Player *p) {
  // Say where the player moved
  std::cout << p->GetName() + " Has Moved to " +
                   std::to_string(p->GetCurrentTilePosition()[0]) + " and " +
                   std::to_string(p->GetCurrentTilePosition()[1])
            << std::endl;

  // Set the player location on the board
  boardArray[p->GetCurrentTilePosition()[1]][p->GetCurrentTilePosition()[0]] =
      p->GetBoardValue();

  // clear the previous location if
  // if that is the only thing on the square set it to one else set it to the
  // other object there
  int previousLoc = boardArray[p->GetPreviousTilePosition()[1]]
                              [p->GetPreviousTilePosition()[0]];
  if (previousLoc - p->GetBoardValue() == 0) {
    // Nothing was there you can just set it back to a regular tile
    boardArray[p->GetPreviousTilePosition()[1]]
              [p->GetPreviousTilePosition()[0]] = 1;
  } else {
    // some other collectable was there don't get rid of it
    boardArray[p->GetPreviousTilePosition()[1]]
              [p->GetPreviousTilePosition()[0]] =
                  previousLoc - p->GetBoardValue();
  }
}

bool Board::IsTileAvailable(int *position) {
  // Check is the player is trying to move out of bounds
  if (position[0] > boardWidth || position[0] < 0 ||
      position[1] > boardHeight || position[1] < 0) {
    return false;
  } else {
    // Check if the tile is already ocupied
    if (boardArray[position[1]][position[0]] == 1 &&
        boardArray[position[1]][position[0]] != 0 &&
        boardArray[position[1]][position[0]] != 8 &&
        boardArray[position[1]][position[0]] != 9 &&
        boardArray[position[1]][position[0]] != 10 &&
        boardArray[position[1]][position[0]] != 11) {
      return true;
    } else {
      return false;
    }
  }
}