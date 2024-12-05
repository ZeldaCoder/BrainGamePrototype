#include "BaseTrap.h"

class LazerTrap : public BaseTrap {
public:
  // construtor
  LazerTrap();

private:

// randomizes what tiles are trapped (Child specific)
void SetRandomAffectedTiles(Board* b) override;

// allows player to pick trapped tiles (Child specific)
void SetChosenAffectedTiles(Board* b) override;
  
};