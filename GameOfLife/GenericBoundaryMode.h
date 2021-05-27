/*

For the information on guards I referenced: https://www.learncpp.com/cpp-tutorial/header-guards/

guards are included since this class is going to be
inherited by other classes, so this prevents
an error that prevents compiling due to
multiple definitions

*/

#ifndef GENERIC_BOUNDARY_MODE_H
#define GENERIC_BOUNDARY_MODE_H

#include <iostream>

/*

This class is responsible for defining
all of the general behaviors of each boundary mode class
that inherits from it

*/
class GenericBoundaryMode {

//I use protected so that classes that inherit from this class can see these items but still restrict access to outside classes
protected:

  /*

  -a method that will be overriden by classes that
  calculates the amount of neighbors a
  location has based on the rules of
  the boundary mode in use

  */
  virtual void checkTheAmountOfNeighborsThisLocationHas(char** previousGenerationGrid, int rows, int columns);

  bool determineIfACellShouldDie(); //determines if a cell should die due to loneliness or overcrowding
  bool determineIfACellShouldBeBorn(); //determines if a cell should be born if the current location is empty and there are 3 neighbors

  int currentRow; //keeps track of the current row that neighbors are being checked for
  int currentColumn; //keeps track of the current column that neighbors are being checked for

  char thingInCurrentSlot; //keeps track of the item stored at the current location we are checking the neighbors of

  int amountOfNeighborsThisCellHas; //keeps track of how many neighbors have been calculated for the current location

  int amountOfCellsAliveInNewGeneration; //keeps track of how many cells are alive in the new generation for determining population stability or exitinction later

  int rowsInArray;//keeps track of how many rows are in the array so that the 2d array for the new population grid can be deallocated later

public:
  GenericBoundaryMode(); //default constructor
  ~GenericBoundaryMode(); //destructor
  void generateNextGeneration(char** previousGenerationGrid, int rows, int columns); //generates the next generation grid by using the correct neighbor calculation method
  void initializeNewGenerationGrid(int rows, int columns); //dynamically allocates the 2d array that will represents the new generation grid
  void deleteGrid(); //deallocates the new generation grid to prevent memory leak
  char** newGenerationGrid; //the 2d array that will represent the new population grid
  int amountOfCellsThatWillDieInTheUpcommingGeneration; //keeps track of the amount of cells that will die in the next generation for determining population stability later
  int amountOfCellsThatWillBeBornInTheUpcommingGeneration; //keeps track of the amount of cells that will be born in the next generation for determining population stability later

};

#endif
