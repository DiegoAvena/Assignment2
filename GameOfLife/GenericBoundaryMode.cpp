#include "GenericBoundaryMode.h"
#include <iostream>

using namespace std;

GenericBoundaryMode::GenericBoundaryMode() { //default constructor

}

GenericBoundaryMode::~GenericBoundaryMode() { //destructor

}

void GenericBoundaryMode::deleteGrid() { //deallocates the new generation grid to prevent memory leak

  for (int i = 0; i < rowsInArray; i++) {

    delete[] newGenerationGrid[i]; //delete the arrays stored in each row of the 2d array

  }

  delete[] newGenerationGrid; //delete the array of rows

}

//dynamically allocates the 2d array that will represents the new generation grid
void GenericBoundaryMode::initializeNewGenerationGrid(int rows, int columns) {

  newGenerationGrid = new char* [rows];
  rowsInArray = rows;

  for (int i = 0; i < rows; i++) {

    newGenerationGrid[i] = new char[columns];

  }

}

//generates the next generation grid by using the correct neighbor calculation method
void GenericBoundaryMode::generateNextGeneration(char** previousGenerationGrid, int rows, int columns) {

  amountOfCellsThatWillDieInTheUpcommingGeneration = 0;
  amountOfCellsThatWillBeBornInTheUpcommingGeneration = 0;

  for (int row = 0; row < rows; row++) {

    for (int column = 0; column < columns; column++) {

      currentRow = row;
      currentColumn = column;
      thingInCurrentSlot = previousGenerationGrid[row][column];

      checkTheAmountOfNeighborsThisLocationHas(previousGenerationGrid, rows, columns);

      if (determineIfACellShouldDie()) {

        //a cell will die
        amountOfCellsThatWillDieInTheUpcommingGeneration++;
        newGenerationGrid[currentRow][currentColumn] = '-'; //simulate the death of a cell by changing X to -

      }
      else if (determineIfACellShouldBeBorn()) {

        //a cell will be born
        amountOfCellsThatWillBeBornInTheUpcommingGeneration++;
        newGenerationGrid[currentRow][currentColumn] = 'X'; //simulate the birth of a cell by changing - to X

      }
      else {

        //keep the thing in the current slot of the current generation grid in the new generation grid, nothing will die or be born in this location
        newGenerationGrid[currentRow][currentColumn] = thingInCurrentSlot;

      }

    }

  }

}

//determines if a cell should die due to loneliness or overcrowding
bool GenericBoundaryMode::determineIfACellShouldDie() {

  if (thingInCurrentSlot == '-') {

    //this slot was empty, no cell will die since there is nothing to kill
    return false;

  }
  else {

    //there is a cell in our current location we are checking the neighbors of:
    if (amountOfNeighborsThisCellHas <= 1) {

      //a location that has a cell in it and has 1 or fewer neighbors will have its cell die due to loneliness
      return true;

    }
    else if (amountOfNeighborsThisCellHas >= 4) {

      //a location that has a cell in it and has 4 or more neighbors will have its cell die due to overcrowding
      return true;

    }
    else {

      /*

      there are no other ways a location with a cell can have its cell die, so at this point
      the cell in this location is not dying in the next generation

      */
      return false;

    }

  }

}

//determines if a cell should be born if the current location is empty and there are 3 neighbors
bool GenericBoundaryMode::determineIfACellShouldBeBorn() {

  if (amountOfNeighborsThisCellHas == 3) {

    //a location with 3 neighbors will have a cell born if there is no cell
    //in this location yet, if there is a cell in this location then that cell lives on

    if (thingInCurrentSlot == '-') {

      //current location is empty, a new cell will be born
      return true;

    }
    else {

      return false;

    }

  }
  return false;

}

/*

-a method that will be overriden by classes that
calculates the amount of neighbors a
location has based on the rules of
the boundary mode in use

*/
void GenericBoundaryMode::checkTheAmountOfNeighborsThisLocationHas(char** previousGenerationGrid, int rows, int columns) {

}
