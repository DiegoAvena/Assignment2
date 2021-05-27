#include "GenericBoundaryMode.h"

/*

This class is responsible for allowing the simulation to
run using the correct settings for Doughnut mode

*/
class DoughnutModeManager:public GenericBoundaryMode{

/*

This class inherits from GenericBoundaryMode since it has methods
that are needed and that can be used with any boundary mode, so this
eliminates the inclusion of large amounts of redundant code.

*/
private:

  //overrides a method in Generic boundary mode to check the amount of neighbors the current location has using the correct rules for doughnut mode
  void checkTheAmountOfNeighborsThisLocationHas(char** previousGenerationGrid, int rows, int columns);

public:
  DoughnutModeManager(); //default constructor
  ~DoughnutModeManager(); //destructor

};
