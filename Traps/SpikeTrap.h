#include "BaseTrap.h"

class SpikeTrap : public BaseTrap {
public:
  // construtor
  SpikeTrap();

protected:
// randomizes what tiles are trapped (Child specific)
void SetRandomAffectedTiles(Board* b) override;

// allows player to pick trapped tiles (Child specific)
void SetChosenAffectedTiles(Board* b) override;

};