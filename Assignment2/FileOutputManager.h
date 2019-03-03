#include <fstream>

/*

-This class is responsible for writing the generations
to a file of the name the user has chosen in the case that they
choose to write the generations to a file.

*/
class FileOutputManager {

private:
  std::ofstream fileToWriteTo; //The file that will be written to

public:
  FileOutputManager(); //default constructor
  ~FileOutputManager(); //destructor
  void writeGenerationToFile(int generationNumber, char** generationGridToWriteToFile, int rowsInGrid, int columnsInGrid); //writes the contents of the generation grid provided onto the specified file
  void openFileForWriting(std::string nameOfFileToWriteTo); //opens the file to write to

};
