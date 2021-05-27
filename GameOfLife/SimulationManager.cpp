#include "SimulationManager.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

SimulationManager::SimulationManager() { //default constructor

}

SimulationManager::~SimulationManager() { //destructor

  for (int i = 0; i < numberOfRows; i++) {

    //delete the inner arrays, each row is array of x columns, so delete the rows
    delete[] currentPopulationGrid[i];

  }

  //delete the outer arrays, or the array of x rows
  delete[] currentPopulationGrid;

  /*

  Since only 1 boundary mode is ran during the simulation,
  only the 2d array for that specific boundary has to be deallocated.
  The code below does this.

  */
  if (boundaryModeType == 0) {

    classicModeManager.deleteGrid();

  }
  else if (boundaryModeType == 1) {

    doughnutModeManager.deleteGrid();

  }
  else if (boundaryModeType == 2) {

    mirrorModeManager.deleteGrid();

  }

}

//dynamically allocates the 2d array that will represent the current population grid
void SimulationManager::setUpPopulationGrids() {

    currentPopulationGrid = new char* [numberOfRows]; //an array of x rows that contain pointers to a row (a row that represents the columns)

    for (int i = 0; i < numberOfRows; i++) {

      currentPopulationGrid[i] = new char[numberOfColumns]; //each row gets an array of x columns equal to numberOfColumns

    }

}

//fills the current population grid in the case the user chooses to input a map file
void SimulationManager::populateFirstPopulationGridFromMapFile(int currentRow, string line) {

  generationNumber = 0;

  for (int i = 0; i < numberOfColumns; i++) {

    currentPopulationGrid[currentRow][i] = line[i]; //fill each column in this row with the corresponding column data for this row in the inputed file

  }

}

//dynamically allocates the 2d array that represents the new population grid for the correct boundary mode setting
void SimulationManager::setUpNewGenerationGridForCorrectNeighborMode() {

  if (boundaryModeType == 0) {

    //dynamically allocate classic mode manager 2d array that represents the new generation grid
    classicModeManager.initializeNewGenerationGrid(numberOfRows, numberOfColumns);

  }
  else if (boundaryModeType == 1) {

    //dynamically allocate doughnut mode manager 2d array that represents the new generation grid
    doughnutModeManager.initializeNewGenerationGrid(numberOfRows, numberOfColumns);

  }
  else if (boundaryModeType == 2) {

    //dynamically allocate mirror mode manager 2d array that represents the new generation grid
    mirrorModeManager.initializeNewGenerationGrid(numberOfRows, numberOfColumns);

  }

}

//fills the current population grid with a random order in the case the user chooses to use a random configuration
void SimulationManager::createRandomGridConfigurationForGenerationZero() {

  int numberOfRegionsThatShouldContainACell = rint(populationDensity * numberOfRows * numberOfColumns); //calculates how many slots should be filled with a cell based on the provided population density

  int randomNumber;
  int numberOfSpacesThatHaveBeenFilled = 0;
  int numberOfSpacesInThisGrid = numberOfRows * numberOfColumns;

  generationNumber = 0;

  //generates a random configuration grid for generation 0, from which the game will then build off of to run the similulations
  if (numberOfRegionsThatShouldContainACell > 0) {

    while(numberOfSpacesThatHaveBeenFilled <= (numberOfRegionsThatShouldContainACell - 1)) { //continue random generation until all the spots that need to be filled are filled

      for (int row = 0; row < numberOfRows; row++) {

        for (int column = 0; column < numberOfColumns; column++) {

          randomNumber = rand() % 2; //generate a random number between 0 and 1, if number is 0, fill this space in, if it is 1, do not fill in the space

          if ((randomNumber == 0) && (currentPopulationGrid[row][column] != 'X') && (numberOfSpacesThatHaveBeenFilled <= (numberOfRegionsThatShouldContainACell - 1))) { //stops adding cells in regardless of the what the random number is if the number of cells added already is at or past the amount that needs to be added

            //The condition that currentPopulationGrid[row][column] != 'X' avoids the placement of a cell in an area that is already occupied by a cell

            //fill this space in with a cell
            currentPopulationGrid[row][column] = 'X';
            numberOfSpacesThatHaveBeenFilled++;

          }
          else if (((randomNumber == 1) && (currentPopulationGrid[row][column] != 'X')) || ((numberOfSpacesThatHaveBeenFilled > (numberOfRegionsThatShouldContainACell - 1)) && (currentPopulationGrid[row][column] != 'X'))) { //

            //The condition that currentPopulationGrid[row][column] != 'X' avoids the deletion of a cell
            currentPopulationGrid[row][column] = '-';

          }

        }

      }

    }

  }
  else {

    //there are 0 bacteria in generation 0, so just fill every slot with a - to represent this
    for (int row = 0; row < numberOfRows; row++) { //loop through each row

      for (int column = 0; column < numberOfColumns; column++) { //loop through each column in this row

        currentPopulationGrid[row][column] = '-';

      }

    }

  }

}

//used to launch the entire simulation
void SimulationManager::runSimulation() {

  consoleOutputManager.outputGenerationToConsole(currentPopulationGrid, generationNumber, numberOfRows, numberOfColumns);
  timesWherePopulationWasStable = 0;
  counter = 0;

  if (simulationVisualizerMode == 2) {

    //prep the fileOutputManager for writing to a file of a name the user gave and write generation 0 into it
    fileOutputManager.openFileForWriting(nameOfFileToOutputTo);
    fileOutputManager.writeGenerationToFile(generationNumber, currentPopulationGrid, numberOfRows, numberOfColumns);

  }

  while (true) { //run the simulation until the population has stabalized or everything has died or the number of iterations is too high

    counter++;
    calculateNeighborsUsingModeUserHasSelected();

    if (simulationVisualizerMode == 0) {

      //put a brief pause before displaying the next generation to the user on the console:
      createSmallDelay();

    }
    else if (simulationVisualizerMode == 1) {

      //prompt user to press enter in order for next generation to show on the console:
      cout<<endl;
      promptUserToPressEnter("Press ENTER for the next generation to appear");

    }
    else if (simulationVisualizerMode == 2){

      //output the generations to a file by the name the user gave
      fileOutputManager.writeGenerationToFile(generationNumber, currentPopulationGrid, numberOfRows, numberOfColumns);

    }

    consoleOutputManager.outputGenerationToConsole(currentPopulationGrid, generationNumber, numberOfRows, numberOfColumns);

    if (checkIfSimuluationShouldEnd()) {

      promptUserToPressEnter("The world has either become empty or has stabalized or the simulation has gone on for too long. Press ENTER to exit the program");

      break; //break out of the while loop so that the simulation can end

    }

  }

}

//asks the user to press enter before something else can occur
void SimulationManager::promptUserToPressEnter(string messageToGiveToUser) {

  //for info on ignore and get, I used: https://www.youtube.com/watch?v=yTk33AlatIw
  cin.ignore(); //clear the last line of input that may be here, so that cin.get() is not ignored
  cout<<messageToGiveToUser<<endl;
  cin.get(); //wait for the user to press enter
  cin.unget(); //put the enter char extracted by get back into characters available to be extracted by input, for this I used: http://www.cplusplus.com/reference/istream/istream/unget/

}

//creates a pause effect of about 1 sec between generations displaying on the console if the user chose this option
void SimulationManager::createSmallDelay() {

  //for info on the clock method I used: http://www.cplusplus.com/reference/ctime/
  clock_t timeOne = clock(); //returns a time expressed in clock ticks
  clock_t timeTwo = clock(); //returns a time expressed in clock ticks

  while (((timeTwo - timeOne) / CLOCKS_PER_SEC) < 1) { //since the clock() method returns a time expressed as clock ticks, then a simple dimensional analysis equation can convert this to seconds using the CLOCKS_PER_SEC constant, which stores the amount of clock ticks in 1 sec

    timeTwo = clock();

  }

}

//calls the correct neighbor check method for the boundary mode setting the user selected
void SimulationManager::calculateNeighborsUsingModeUserHasSelected() {

  if (generationNumber == 0) {

    //initializes these values:
    numberOfCellsBornInPreviousGrid = 0;
    numberOfCellsThatDiedInPreviousGrid = 0;

  }

  if (boundaryModeType == 0) {

    //use classic mode
    classicModeManager.generateNextGeneration(currentPopulationGrid, numberOfRows, numberOfColumns);
    updateCurrentGridToNewGrid(classicModeManager.newGenerationGrid);

  }
  else if (boundaryModeType == 1) {

    //use doughnut mode
    doughnutModeManager.generateNextGeneration(currentPopulationGrid, numberOfRows, numberOfColumns);
    updateCurrentGridToNewGrid(doughnutModeManager.newGenerationGrid);

  }
  else {

    //use mirror mode
    mirrorModeManager.generateNextGeneration(currentPopulationGrid, numberOfRows, numberOfColumns);
    updateCurrentGridToNewGrid(mirrorModeManager.newGenerationGrid);

  }

  generationNumber++;

}

//copies each item in the new generation grid into the current generation grid
void SimulationManager::updateCurrentGridToNewGrid(char** newGridToCopy) {

  for (int row = 0; row < numberOfRows; row++) {

    for (int column = 0; column < numberOfColumns; column++) {

      currentPopulationGrid[row][column] = newGridToCopy[row][column];

    }

  }

}

//determines if the population has stabalized
bool SimulationManager::checkForStabilityUsingCorrectBoundaryModeSettings(int cellsThatWillDieInNextGeneration, int cellsThatWillBeBornInNextGeneration) {

  if ((cellsThatWillDieInNextGeneration == 0) && (cellsThatWillBeBornInNextGeneration == 0)) {

    //no more cells are being born and no more cells are dying, the population has stabalized:
    numberOfCellsThatDiedInPreviousGrid = cellsThatWillDieInNextGeneration;
    numberOfCellsBornInPreviousGrid = cellsThatWillBeBornInNextGeneration;
    return true;

  }
  else if (((cellsThatWillDieInNextGeneration - cellsThatWillBeBornInNextGeneration) == 0) || (numberOfCellsThatDiedInPreviousGrid == cellsThatWillBeBornInNextGeneration) || (numberOfCellsBornInPreviousGrid == cellsThatWillDieInNextGeneration)) {

    //the amount of cells dying is equal to the amount of cells born, so the population will remain stable, or there is some oscilation happening between generations
    timesWherePopulationWasStable += 1;
    numberOfCellsThatDiedInPreviousGrid = cellsThatWillDieInNextGeneration;
    numberOfCellsBornInPreviousGrid = cellsThatWillBeBornInNextGeneration;

    if (timesWherePopulationWasStable >= 600) { //600 is the arbitrary number I chose for the number of times the population needs to be stable for

      //we can say with some degree of certainty that the population is stabalized, the simulation needs to end.
      return true;

    }
    else {

      return false;

    }

  }
  else {

    //there are either more cells that will die in the next generation than cells that will be born or vice versa
    //timesWherePopulationWasStable = 0;

    numberOfCellsThatDiedInPreviousGrid = cellsThatWillDieInNextGeneration;
    numberOfCellsBornInPreviousGrid = cellsThatWillBeBornInNextGeneration;
    return false;

  }

}

//ends the simulation if the population has stabalized with the aid of a helper method or if everything has died
bool SimulationManager::checkIfSimuluationShouldEnd() {

  numberOfCellsAliveInNewGrid = determineAmountOfCellsAliveInCurrentGrid();

  if (counter >= 1000) {

    //this is the 1000th iteration, the simulation has gone on for too long
    return true;

  }

  if ((numberOfCellsAliveInNewGrid <= 0) && (generationNumber != 0)) {

    //all cells have died
    return true;

  }
  else if (boundaryModeType == 0) {

      return checkForStabilityUsingCorrectBoundaryModeSettings(classicModeManager.amountOfCellsThatWillDieInTheUpcommingGeneration, classicModeManager.amountOfCellsThatWillBeBornInTheUpcommingGeneration);

  }
  else if (boundaryModeType == 1) {

    return checkForStabilityUsingCorrectBoundaryModeSettings(doughnutModeManager.amountOfCellsThatWillDieInTheUpcommingGeneration, doughnutModeManager.amountOfCellsThatWillBeBornInTheUpcommingGeneration);

  }
  else if (boundaryModeType == 2) {

    return checkForStabilityUsingCorrectBoundaryModeSettings(mirrorModeManager.amountOfCellsThatWillDieInTheUpcommingGeneration, mirrorModeManager.amountOfCellsThatWillBeBornInTheUpcommingGeneration);

  }

  //the simulation should continue:
  numberOfCellsAliveInPreviousGrid = numberOfCellsAliveInNewGrid;
  return false;

}

//loops through the current grid to determine the amount of cells currently alive
int SimulationManager::determineAmountOfCellsAliveInCurrentGrid() {

  int amountOfCellsLiving = 0;

  for (int row = 0; row < numberOfRows; row++) {

    for (int column = 0; column < numberOfColumns; column++) {

      if (currentPopulationGrid[row][column] == 'X') {

        amountOfCellsLiving++;

      }

    }

  }

  return amountOfCellsLiving;

}
