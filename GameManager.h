#include <vector>


// Forward Declares
class Player;
class Board;

class GameManager {
public:
  GameManager();

private:

  /*
   * Instance Variables
   */
  Board* gameBoard;
  int numOfTurns = 0;
  std::vector<Player*> players;


  /*
  * Methods
  */

  std::vector<Player> AddPlayers();
  void NextTurn();

public:
  void Play();
  

};