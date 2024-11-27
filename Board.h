#include <vector>
#include "Tile.h"
#include "Lever.h"

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

  std::vector<Tile> boardArray;

  std::vector<Lever*> levers;

  const int MAX_LEVERS = 5;
  // const int MAX_POWER_UPS = 3;

  /* 
  * Methods
  */

  Tile* GetRandomBoardTile();

  

public:
  /*
   * Methods
   */

  std::vector<Tile> InitBoard(int height, int width);
  void DisplayBoard();

  void SetRandomPlayerLocation(Player *p);

  void SetPlayerLocation(Player *p);

  bool IsTileAvailable(Tile position);
  void TileHarmful(Player *p);

  void DeleteRandomTile();

  void SpawnRandomLevers();

  std::vector<Lever*>& GetLevers();

  Tile* GetBoardTile(Tile givenTile);

  std::vector<Tile> GetAllTiles();

  void ApplyTraps(std::vector<Lever*>::iterator& leverIter);
};