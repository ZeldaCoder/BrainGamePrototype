class Board {
public:
  Board();

private:
  /*
  * Instance Variables
  */
  int boardWidth = 7;
  int boardHeight = 6;
  int oldBoard[6][7] = {1};

public:
  /*
  * Methods
  */

  int** InitBoard(int height, int width);
  void DisplayBoard();

};