#include "ClassicModeManager.h"
#include <iostream>

using namespace std;

ClassicModeManager::ClassicModeManager() { //default constructor

}

ClassicModeManager::~ClassicModeManager() { //destructor

}

//overrides a method in Generic boundary mode to check the amount of neighbors the current location has using the correct rules for classic mode
void ClassicModeManager::checkTheAmountOfNeighborsThisLocationHas(char** previousGenerationGrid, int rows, int columns) {

  int currentRowUnderInspection = currentRow - 1; //the current row being inspected for neighbors
  int currentColumnUnderInspection = currentColumn - 1; //the current column being inspected for neighbors
  amountOfNeighborsThisCellHas = 0;

  for (int i = 0; i < 9; i++) { //loop 9 times because there are 9 spots in the 3x3 grid

    if ((currentRowUnderInspection != currentRow) || (currentColumnUnderInspection != currentColumn)) {

      //if the location being looked at is out of bounds, then this location is skipped according to the rules of classic mode
      if (((currentColumnUnderInspection >= 0) && (currentColumnUnderInspection < columns)) && ((currentRowUnderInspection >= 0) && (currentRowUnderInspection < rows))) {

        if (previousGenerationGrid[currentRowUnderInspection][currentColumnUnderInspection] == 'X') {

          amountOfNeighborsThisCellHas++;

        }

      }

    }

    /*

    A representation of the 3x3 matrix of adjacent neighbors:

    0|1|2
    -----
    3|4|5
    -----
    6|7|8

    where each integer represents which neighbor we are checking for each i iteration

    From this image, it is clear that when i == 2 or i == 5 or i == 8, we are on the last column
    of the current row, so not only does the column need to be reset back to its initial value, but the current row
    under inspection also needs to be incremented to the next row. The if statement below handles this

    */
    if ((i == 2) || (i == 5) || (i == 8)) {

      currentRowUnderInspection++;
      currentColumnUnderInspection -= 2;
      //cout<<"Switching current row under inspection to "<<currentRowUnderInspection<<"and current column under inspection to"<<currentColumnUnderInspection<<endl;

    }
    else {

      currentColumnUnderInspection++;

    }

  }

}
