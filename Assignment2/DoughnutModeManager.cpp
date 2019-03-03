#include "DoughnutModeManager.h"
#include <iostream>

using namespace std;

DoughnutModeManager::DoughnutModeManager() { //default constructor

}

DoughnutModeManager::~DoughnutModeManager() { //default destructor

}

//overrides a method in Generic boundary mode to check the amount of neighbors the current location has using the correct rules for doughnut mode
void DoughnutModeManager::checkTheAmountOfNeighborsThisLocationHas(char** previousGenerationGrid, int rows, int columns) {

  //start at the top left corner of the "3x3" grid of adjacent neighbors:
  int currentRowUnderInspection = currentRow - 1; //the current row being inspected for neighbors
  int currentColumnUnderInspection = currentColumn - 1; //the current column being inspected for neighbors

  amountOfNeighborsThisCellHas = 0;

  /*

  For calculations for references off the grid in doughnut mode, I came up with this: (currentRowUnderInspection + rows) % rows for rows,
  and (currentColumnUnderInspection + columns) % columns for columns.

  Doing this insures that the
  locations under inspection that are off the grid get
  wrapped around correctly according to doughnut mode, and using mod
  operator works for locations that are in the grid since it will not change their value if they are not
  off the grid, which is exactly what is needed.

  */
  for (int i = 0; i < 9; i++) {

    if ((currentRowUnderInspection != currentRow) || (currentColumnUnderInspection != currentColumn)) {

      if (previousGenerationGrid[(currentRowUnderInspection + rows) % rows][(currentColumnUnderInspection + columns) % columns] == 'X') {

        amountOfNeighborsThisCellHas++;

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
