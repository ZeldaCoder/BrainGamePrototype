#include <vector>

// Forward Declares
class Player;
class Board;
class BaseTrap;

class GameManager {
public:
  GameManager();

private:
  /*
   * Instance Variables
   */
  Board *gameBoard;
  inline static int numOfTurns = 0;
  std::vector<Player *> players;

  inline static std::vector<BaseTrap *> activeTraps = {};

  /*
   * Methods
   */

  std::vector<Player *> AddPlayers();

  void NextTurn();

  void UpdateTrapTimers();

public:
  void Play();

  inline static int GetNumOfTurns() { return GameManager::numOfTurns; }

  inline static void AddActivatedTrap(BaseTrap *t) {
    GameManager::activeTraps.push_back(t);
  }

  inline static std::vector<BaseTrap*> GetActiveTraps() {
    return GameManager::activeTraps;
  }
};