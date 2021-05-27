#include "InputManager.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

InputManager::InputManager() { //default constructor

}

InputManager::~InputManager() { //default destructor

}

void InputManager::promptUserForGameSettings() { //will ask the user for the settings of the games via the use of more specific methods

  promptUserForConfigurationType();
  promptUserForBoundaryModeToRunIn();
  promptUserForSimulationVisualizerMode();

  //by this point all the information needed for the simulation to run has been obtained, so launch the simulation:
  simulator.runSimulation();

}

//asks the user if they want to generate a random bacteria configuration for generation 0 or if they want to use a flat file configuration
void InputManager::promptUserForConfigurationType() {

  char response; //stores the response the user inputs

  //keep prompting the user for a bacteria configuration type until what they enter is valid, since the simulation cannot run without this information
  while (true) {

    cout<<"Would you like to start with a random configuration?, Enter y for yes or n for no"<<endl;
    cin>>response;

    if (tolower(response) == 'n') { //user does not want to generate a random configuration

      if (attemptToOpenAFile()) {

        //map file has been opened and read successfully, configuration settings have been obtained, break out of loop
        break;

      }

    }
    else if (tolower(response) == 'y') { //user wants to generate a random configuration

      promptUserForNumberOfRows();
      promptUserForNumberOfColumns();
      promptUserForPopulationDensity();
      simulator.setUpPopulationGrids();
      simulator.createRandomGridConfigurationForGenerationZero();

      //configuration settings have been set, break out of loop
      break;

    }

  }

}

//prompts the user for the number of rows the grid should have
void InputManager::promptUserForNumberOfRows() {

  //keep asking the user for the number of rows they want until they enter something valid since this is needed for the population grid
  while (true) {

    string response; //store user response, I store it as a string so that I can convert the response to an int number of rows using stoi()

    try { //try catch block used to catch the error that may arise in the case the user inputs something that cannot be converted to an integer with stoi()

      cout<<"Enter the number of rows you want, or enter c to cancel: "<<endl;
      cin>>response;
      simulator.numberOfRows = stoi(response); //convert to int since the number of rows should not be a decimal, and store it in the simulator object for user later

      if (simulator.numberOfRows > 0) { //the number of rows has to be greater than 0 since it does not make sense to have a negative amount of rows or 0 rows in a grid

        break;

      }
      else {

        cout<<"Sorry, but the number of rows must be greater than 0"<<endl;

      }

    }
    catch (invalid_argument) {

      cout<<"Sorry, but the value you entered is not a number"<<endl;

    }

  }

}

//prompts the user for the number of columns the grid should have
void InputManager::promptUserForNumberOfColumns() {

  //keep asking the user for the number of columns until they enter something valid since this is needed for the population grid
  while (true) {

    string response; //store user response, I store it as a string so that I can convert the response to an int number of rows using stoi()

    try { //try catch block used to catch the error that may arise in the case the user inputs something that cannot be converted to an integer with stoi()

      cout<<"Enter the number of columns you want, or enter c to cancel: "<<endl;
      cin>>response;
      simulator.numberOfColumns = stoi(response); //convert number to an int since the number of columns cannot be a decimal, and store it in the simulator object for later use

      if (simulator.numberOfColumns > 0) { //the number of columns inserted must be greater than 0 since it does not make sense to have a negative amount of columns or 0 columns

        break;

      }
      else {

        cout<<"Sorry, but the number of rows must be greater than 0"<<endl;

      }

    }
    catch (invalid_argument) {

      cout<<"Sorry, but the value you entered is not a number"<<endl;

    }

  }

}

//prompts the user for how many slots should be filled with a cell in the grid
void InputManager::promptUserForPopulationDensity() {

  string response; //store the response the user gives

  //continue to ask the user for a poulation density until they insert something valid since this is needed for the similation to run
  while (true) {

    //try catch block is used to catch the error that can possibly occur if the user inserts something that cannot be converted to a float
    try {

      cout<<"Enter a decimal that is greater then 0 and less than or equal to 1"<<endl;
      cin>>response;

      simulator.populationDensity = stof(response); //converts the response to a float and stores it in the simulator object for later use

      if (simulator.populationDensity > 0) { //insures the density inputed is greater than 0

        break;

      }
      else {

        cout<<"Sorry, but the value you entered has to be greater than 0"<<endl;

      }

    }
    catch (invalid_argument) {

      cout<<"Sorry, but the value you entered cannot be converted into a decimal."<<endl;

    }


  }

}

//attempts to open the map file user inputs, read the configuration settings, and signals whether or not the file was opened successfully
bool InputManager::attemptToOpenAFile() {

  string nameOfFileToOpen; //store the name of the file the user wants to open

  cout<<"Enter the file path: "<<endl;
  cin>>nameOfFileToOpen;

  ifstream configFile(nameOfFileToOpen);

  if (configFile.is_open()) { //checks to make sure the file was opened successfully

    string line; //store the current line being read from the file

    int lineNumber = 1; //the number of the line being read
    int currentRowInGrid = 0; //keeps track of which row we are on in the current population grid so that the configuration is loaded in the correct order onto the grid

    while (getline(configFile, line)) { //while their are still lines to be read, continue reading

      if (lineNumber == 1) {

        //we are at the line that contains the number of rows
        simulator.numberOfRows = stoi(line);

      }
      else if (lineNumber == 2) {

        //we are at the line that contains the number of columns
        simulator.numberOfColumns = stoi(line);
        simulator.setUpPopulationGrids();

      }
      else {

        //populate the current generation grid with the info on the provided population grid:
        simulator.populateFirstPopulationGridFromMapFile(currentRowInGrid, line);
        currentRowInGrid++;

      }

      lineNumber++;

    }

    configFile.close();
    return true; //tell the program that the file was opened successfully

  }
  else {

    cout<<"The file you entered could not be opened, perhaps it does not exists at the specified directory or was just spelled out wrong"<<endl;
    return false; //tell the program that the file was not opened successfully

  }

}

//asks the user which boundary mode they want: classic mode, doughnut mode, or mirror mode
void InputManager::promptUserForBoundaryModeToRunIn() {

  string userResponse; //store the response the user gives as a string so that it can be converted to an int using stoi()

  //continue to ask the user for what boundary mode they want to use until they insert something that is valid, as this value will be needed for the simulation to run
  while (true) {

    //try block used to catch the error that can occur in the case the user enters something that cannot be converted to an int
    try {

      cout<<"What boundary mode do you want to run the simulation in? Enter 0 for classic mode, 1 for doughnut mode, or 2 for mirror mode"<<endl;
      cin>>userResponse;

      int numberUserEntered = stoi(userResponse);

      if ((numberUserEntered == 0) || (numberUserEntered == 1) || (numberUserEntered == 2)) {

        simulator.boundaryModeType = numberUserEntered;
        simulator.setUpNewGenerationGridForCorrectNeighborMode();
        break;

      }
      else {

        //user entered a number that has no options:
        cout<<"Sorry, the number you enter must either be 0, 1 or 2"<<endl;

      }

    }
    catch (invalid_argument) {

      cout<<"Sorry, you must enter a number"<<endl;

    }

  }

}

//asks the user if they want to press enter for each generation to appear, want a brief pause between generations, or want the generations outputed to a file
void InputManager::promptUserForSimulationVisualizerMode() {

  string userResponse; //store the response the user gives as a string to that it can be converted to a int with stoi()

  //continue to ask the user for what simulationVisualizerMode they want to use since this will be needed during the simulation
  while (true) {

    //try block used to catch the error that can occur in the case the user inputs something that cannot be converted to an int with stoi()
    try {

      cout<<"How would you like the simulation to be displayed? Enter 0 if you want a brief pause between generations, enter 1 if you want to press enter for the next generation to appear, or enter 2 to output the generations to a file"<<endl;
      cin>>userResponse;
      int numberUserEntered = stoi(userResponse);

      if (numberUserEntered == 0 || numberUserEntered == 1) {

        simulator.simulationVisualizerMode = numberUserEntered;
        break;

      }
      else if (numberUserEntered == 2) { //seperated from the other 2 cases because in this case the user will need to input a file name

        simulator.simulationVisualizerMode = numberUserEntered;
        cout<<"Enter the name for the file you want to output the generations to:"<<endl;
        cin>>simulator.nameOfFileToOutputTo;
        break;

      }
      else {

        cout<<"Sorry, the number you enter must either be 0, 1, or 2"<<endl;

      }

    }
    catch (invalid_argument) {

      cout<<"Sorry, you must enter a number"<<endl;

    }

  }

}
