#include "GenericBoundaryMode.h"

/*

This class is responsible for allowing the simulation to
run using the correct boundary settings for MirrorMode

*/

class MirrorModeManager: public GenericBoundaryMode {

/*

This class inherits from GenericBoundaryMode since it has methods
that are needed and that can be used with any boundary mode, so this
eliminates the inclusion of large amounts of redundant code.

*/
private:
  void checkTheAmountOfNeighborsThisLocationHas(char** previousGenerationGrid, int rows, int columns); //calculates the amount of neighbors the current location has using the correct boundary mode rules

public:
  MirrorModeManager(); //default constructor
  ~MirrorModeManager(); //default destructor

};
