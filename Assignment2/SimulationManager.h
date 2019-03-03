#include <iostream>
#include "ManageGenerationOutput.h"
#include "MirrorModeManager.h"
#include "ClassicModeManager.h"
#include "DoughnutModeManager.h"
#include "FileOutputManager.h"

/*

This class is responsible for running the actual simulation
using the input the user gave and the settings the user chose

*/
class SimulationManager {

private:

  char **currentPopulationGrid; //the 2d array representing the grid that stores the current generation
  int numberOfCellsAliveInNewGrid; //stores the amount of cells left alive in the new generation grid for determining population stability
  int numberOfCellsAliveInPreviousGrid; //stores the amount of cells alive in the previous generation grid for determining population stablility

  int numberOfCellsThatDiedInPreviousGrid; //stores the amount of cells that died in the previous generation grid, for determining population stability later
  int numberOfCellsBornInPreviousGrid; //stores the amount of cells that were born in the previous generation grid for determining population stability later

  bool checkIfSimuluationShouldEnd(); //ends the simulation if the population has stabalized with the aid of a helper method or if everything has died
  bool checkForStabilityUsingCorrectBoundaryModeSettings(int cellsThatWillDieInNextGeneration, int cellsThatWillBeBornInNextGeneration); //determines if the population has stabalized
  int determineAmountOfCellsAliveInCurrentGrid(); //loops through the current grid to determine the amount of cells currently alive
  void calculateNeighborsUsingModeUserHasSelected(); //calls the correct neighbor check method for the boundary mode setting the user selected
  void createSmallDelay(); //creates a pause effect of about 1 sec between generations displaying on the console if the user chose this option
  void promptUserToPressEnter(std::string messageToGiveToUser); //asks the user to press enter before something else can occur
  void updateCurrentGridToNewGrid(char** newGridToCopy); //copies each item in the new generation grid into the current generation grid

  int timesWherePopulationWasStable; //keeps track of the times where the population seemed stable, this value is reset to 0 each time the population is found to be unstable

  //The 3 boundary modes that can be used to check for neighbors
  ClassicModeManager classicModeManager;
  DoughnutModeManager doughnutModeManager;
  MirrorModeManager mirrorModeManager;

  FileOutputManager fileOutputManager; //used to output the generations to a file of a name the user defined

public:
  SimulationManager(); //default constructor
  ~SimulationManager(); //destructor
  void setUpPopulationGrids(); //dynamically allocates the 2d array that will represent the current population grid
  void populateFirstPopulationGridFromMapFile(int currentRow, std::string line); //fills the current population grid in the case the user chooses to input a map file
  void createRandomGridConfigurationForGenerationZero(); //fills the current population grid with a random order in the case the user chooses to use a random configuration
  void runSimulation(); //used to launch the entire simulation
  void setUpNewGenerationGridForCorrectNeighborMode(); //dynamically allocates the 2d array that represents the new population grid for the correct boundary mode setting

  int generationNumber; //keeps track of the generations
  int numberOfColumns; //the number of columns the grids should have
  int numberOfRows; //the number of rows the grids should have
  int bacteriaCount; //In the case the user chooses a random configuration, this stores how much bactera/cells should be in the grid for generation 0 based off of the population density the user gives.
  int boundaryModeType;  //0 means Classic mode, 1 means Doughnut mode, and 2 means Mirror mode
  int simulationVisualizerMode; //0 means the user wants a brief pause between generations, 1 means the user wants to press enter for the next generation to appear, and 1 means the user wants to output to a file, in which case they are then prompted for a filename to output to
  std::string nameOfFileToOutputTo; //the name of the file the generations should be ouputed to in the case the user chooses this option

  float populationDensity; //stores the population density the user inputs so that bacteria count can be calculated

  ManageGenerationOutput consoleOutputManager; //used to output each generation to the console

};
