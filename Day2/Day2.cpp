#include <fstream>
#include <iostream>

//
// Created by Cesilia Esquivel on 12/2/16.
//
char *buffer;
const int BUFFER_SIZE = 1024;
const char *const DELIMITER = " ";
using namespace std;

struct Position {
  int x, y;
};

class NumPad {
private:
  char numPad [5][5] = { {0,0,'5',0,0,},{0,'A','6','2',0},{'D','B','7','3','1'},{0,'C','8','4',0,},{0,0,'9',0,0} };
  Position currPosition = {.x=-0, .y=2}; // Start at 5
public:
  int getX(){
    return currPosition.x;
  };
  int getY(){
    return currPosition.y;
  };
  void moveX( int moves ){
    if( moves > 0 ){
      // Moving right...
      if( getNumber() != '1' && getNumber() != '4'  && getNumber() != '9' &&
          getNumber() != 'C' && getNumber() != 'D' ){
        currPosition.x += moves;
      }
    } else{
      // Move left
      if( getNumber() != '1' && getNumber() != '2' && getNumber() != '5' &&
          getNumber() != 'A' && getNumber() != 'D' ){
        currPosition.x += moves;
      }
    }

  }
  void moveY(int moves ){
    if ( moves > 0 ){
      // Move up...
      if ( getNumber() != '5' && getNumber() != '2' && getNumber() != '1' &&
           getNumber() != '4' && getNumber() != '9' ){
        currPosition.y += moves;
      }
    } else {
      // Move down...
      if ( getNumber() != '5' && getNumber() != 'A' && getNumber() != 'D' &&
           getNumber() != 'C' && getNumber() != '9' ){
        currPosition.y += moves;
      }
    }
  }
  char getNumber(){
    return numPad[currPosition.x][currPosition.y];
  }
};

int main() {
  // Create a file reading object
  ifstream file;
  file.open("/Users/Cesilia/Development/AdventofCode/Day2/sample.txt"); // open a file
  if (!file.good()) {
    return 1; // exit if file not found
  }

  buffer = static_cast<char*>(malloc(BUFFER_SIZE));
  NumPad bathroomPad;

  while(!file.eof()){
    // read in number line into memory
    file.getline(buffer, BUFFER_SIZE);

    // char pointer
    char *currChar = &buffer[0];
    while( *currChar != '\0' ) {
      if (*currChar == 'U') {
        bathroomPad.moveY(1);
      } else if (*currChar == 'D') {
        bathroomPad.moveY(-1);

      } else if (*currChar == 'L'){
        bathroomPad.moveX(-1);

      } else if (*currChar == 'R'){
        bathroomPad.moveX(1);
      }
      // move current char pointer to next
      currChar++;
    }
    cout << bathroomPad.getNumber() << endl;
  }
}
