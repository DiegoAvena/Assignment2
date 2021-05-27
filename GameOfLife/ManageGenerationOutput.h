#include <iostream>

/*

This class is responsible for outputing each generation to the console for the user to see

*/

class ManageGenerationOutput {

public:
  ManageGenerationOutput(); //default constructor
  ~ManageGenerationOutput(); //default destructor
  void outputGenerationToConsole(char** generationGrid, int generationNumber, int rows, int columns); //outputs the generated grid for the generation onto the console

};
