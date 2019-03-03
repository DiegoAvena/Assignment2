#include "FileOutputManager.h"
#include <iostream>
using namespace std;

//default constructor
FileOutputManager::FileOutputManager() {

}

//opens the file to write to
void FileOutputManager::openFileForWriting(string nameOfFileToWriteTo) {

  fileToWriteTo.open(nameOfFileToWriteTo, ios::trunc); //I use trunc so that if the current file being written into has stuff in it, it gets cleared

}

//destructor, makes sure the file being written to is closed if it was opened
FileOutputManager::~FileOutputManager() {

  if (fileToWriteTo.is_open()) {

    fileToWriteTo.close();

  }

}

//writes the contents of the generation grid provided onto the specified file
void FileOutputManager::writeGenerationToFile(int generationNumber, char** generationGridToWriteToFile, int rowsInGrid, int columnsInGrid) {

  if (generationNumber > 0) { //skip a line before printing the next generation

    fileToWriteTo << endl;

  }

  fileToWriteTo << "Generation " << generationNumber << endl;

  for (int row = 0; row < rowsInGrid; row++) {

    for (int column = 0; column < columnsInGrid; column++) {

      fileToWriteTo << generationGridToWriteToFile[row][column];

    }

    fileToWriteTo << endl;

  }

}
