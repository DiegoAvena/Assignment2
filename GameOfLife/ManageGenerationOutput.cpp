#include "ManageGenerationOutput.h"
#include <iostream>

using namespace std;

ManageGenerationOutput::ManageGenerationOutput() { //default constructor

}

ManageGenerationOutput::~ManageGenerationOutput() { //default destructor

}

////outputs the generated grid for the generation onto the console
void ManageGenerationOutput::outputGenerationToConsole(char** generationGrid, int generationNumber, int rows, int columns) {

  cout<<endl;
  cout<<"Generation: "<<generationNumber<<endl;

  for (int row = 0; row < rows; row++) {

    for (int column = 0; column < columns; column++) {

      cout<<generationGrid[row][column];

    }

    cout<<endl;

  }

}
