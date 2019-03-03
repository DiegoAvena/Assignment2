#include "MirrorModeManager.h"
#include <iostream>
#include <math.h>

using namespace std;

MirrorModeManager::MirrorModeManager() { //default constructor

}

MirrorModeManager::~MirrorModeManager() { //default destructor

}

//calculates the amount of neighbors the current location has using the correct boundary mode rules
void MirrorModeManager::checkTheAmountOfNeighborsThisLocationHas(char** previousGenerationGrid, int rows, int columns) {

  //start at the top left corner of the "3x3" grid of adjacent neighbors:
  int currentRowUnderInspection = currentRow - 1; //the current row being inspected for neighbors
  int currentColumnUnderInspection = currentColumn - 1; //the current column being inspected for neighbors

  amountOfNeighborsThisCellHas = 0;

  /*

  For calculations for references off the grid in mirror mode, I came up with this: abs(1 - abs(value))

  Doing abs(1 - abs(value)) insures that the
  locations under inspection that are off the grid get
  reflected back into the grid and that
  this reflection is checked for a neighbor, as required by mirror mode.

  NOTE THOUGH: abs(1 - abs(value)) should not be used for locations that are not off the grid for obvious reasons
  (this will change the location when it should not be changed since it is perfectly on the grid)

  */

  for (int i = 0; i < 9; i++) {

    if ((currentRowUnderInspection != currentRow) || (currentColumnUnderInspection != currentColumn)) {

      if (((currentRowUnderInspection < 0) || (currentRowUnderInspection > (rows - 1))) && ((currentColumnUnderInspection < 0) || (currentColumnUnderInspection > (columns - 1)))) {

        //both the column and row are out of bounds:
        if (previousGenerationGrid[abs(1 - abs(currentRowUnderInspection))][abs(1 - abs(currentColumnUnderInspection))] == 'X') {

          amountOfNeighborsThisCellHas++;

        }

      }
      else if (((currentRowUnderInspection < 0) || (currentRowUnderInspection > (rows - 1))) && ((currentColumnUnderInspection >= 0) && (currentColumnUnderInspection < columns))) {

        //only the row is out of bounds, not the column:
        if (previousGenerationGrid[abs(1 - abs(currentRowUnderInspection))][currentColumnUnderInspection] == 'X') {

          amountOfNeighborsThisCellHas++;

        }

      }
      else if (((currentRowUnderInspection >= 0) && (currentRowUnderInspection < rows)) && ((currentColumnUnderInspection < 0) || (currentColumnUnderInspection > (columns - 1)))) {

        //only the column is out of bounds, not the row:
        if (previousGenerationGrid[currentRowUnderInspection][abs(1 - abs(currentColumnUnderInspection))] == 'X') {

          amountOfNeighborsThisCellHas++;

        }

      }
      else {

        //we are in bounds, safe to check the array:
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

    }
    else {

      currentColumnUnderInspection++;

    }

  }

}
