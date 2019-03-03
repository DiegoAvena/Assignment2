#include "InputManager.h"
#include <stdlib.h>  //for access to srand
#include <time.h>   //for access to time()

int main(int argc, char const *argv[]) {

  srand(time(NULL));
  InputManager userInputManager;
  userInputManager.promptUserForGameSettings();

}
