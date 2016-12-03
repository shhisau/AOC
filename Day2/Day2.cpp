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
  int numPad [3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9 } };
  Position currPosition = {.x=1, .y=1}; // Start at 5
public:
  int getX(){
    return currPosition.x;
  };
  int getY(){
    return currPosition.y;
  };
  void moveX( int moves ){
    currPosition.x += moves;
  }
  void moveY(int moves ){
    currPosition.y += moves;
  }
  int getNumber(){
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
        if(bathroomPad.getY() != 0){
          bathroomPad.moveY(-1);
        }
      } else if (*currChar == 'D') {
        if(bathroomPad.getY() != 2){
          bathroomPad.moveY(1);
        }
      } else if (*currChar == 'L'){
        if(bathroomPad.getX() != 0){
          bathroomPad.moveX(-1);
        }
      } else if (*currChar == 'R'){
        if(bathroomPad.getX() != 2){
          bathroomPad.moveX(1);
        }
      }
      // move current char pointer to next
      currChar++;
    }
    cout << bathroomPad.getNumber();
  }

}
