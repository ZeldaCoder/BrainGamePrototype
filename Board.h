
// Forward Declares
class Player;

class Board {
public:
  Board();

private:
  /*
   * Instance Variables
   */
  int boardWidth = 7;
  int boardHeight = 6;

  const int MAX_HEIGHT = 40;
  const int MAX_WIDTH = 40;

  const int MIN_HEIGHT = 5;
  const int MIN_WIDTH = 5;

  int **boardArray;

public:
  /*
   * Methods
   */

  int **InitBoard(int height, int width);
  void DisplayBoard();

  void SetRandomPlayerLocation(Player *p);

  void SetPlayerLocation(Player *p);

  bool IsTileAvailable(int position[2]);
};