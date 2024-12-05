#include "GameManager.h"
#include <iostream>

int main() {
  std::cout << "Hello World!\n";
  GameManager *gameManager = new GameManager();

  gameManager->Play();

  return 0;
}