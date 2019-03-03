/*

This class is responsible for grabbing all of the input needed from the user
in order for the game of life simulation to run.

*/

#include "SimulationManager.h"

class InputManager {

private:
  void promptUserForConfigurationType(); //asks the user if they want to generate a random bacteria configuration for generation 0 or if they want to use a flat file configuration
  void promptUserForBoundaryModeToRunIn(); //asks the user which boundary mode they want: classic mode, doughnut mode, or mirror mode
  void promptUserForSimulationVisualizerMode(); //asks the user if they want to press enter for each generation to appear, want a brief pause between generations, or want the generations outputed to a file
  void promptUserForNumberOfRows(); //prompts the user for the number of rows the grid should have
  void promptUserForNumberOfColumns(); //prompts the user for the number of columns the grid should have
  void promptUserForPopulationDensity(); //prompts the user for how many slots should be filled with a cell in the grid

  bool attemptToOpenAFile(); //attempts to open the map file user inputs, read the configuration settings, and signals whether or not the file was opened successfully

  SimulationManager simulator; //used to access the methods needed to launch the game of life simulation and feed in the settings the user inputs from this class

public:
  InputManager(); //default constructor
  ~InputManager(); //default destructor
  void promptUserForGameSettings(); //will ask the user for the settings of the games via the use of more specific methods

};
