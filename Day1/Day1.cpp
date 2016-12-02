#include <fstream>

/*
 * Advent of Code Puzzle 1
 * Where is the Easter Bunny HQ?
 * Author: Cesilia Esquivel
 * 2016
 */

using namespace std;

const int BUFFER_SIZE = 1024;
const char* const DELIMITER = " ";

enum class Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

int main()
{
    // We start at ( 0, 0 )
    int x, y = 0;
    Direction direction = Direction::NORTH;

    // Create a file reading object
    ifstream file;
    file.open("/Users/Cesilia/Development/AdventofCode/Day1/sample.txt"); // open a file
    if (!file.good()) {
        return 1; // exit if file not found
    }

    // read an file into memory
    char buf[BUFFER_SIZE];
    file.get(buf, BUFFER_SIZE);

    // char pointer
    const char* token;

    // parse the line
    token = strtok(buf, DELIMITER); // first token
    while ( token != NULL ) {
        printf( "%s\n", token );
        // Parse the direction and # of moves
        if ( strncmp( token, "Rx", 1 ) == 0) {
            token++; // Move pointer to the integer
            int moves = stoi( token );
            printf("Move to the right, %d times\n", moves);
            switch ( direction ) {
                case Direction::NORTH:
                    x += moves;
                    direction = Direction::EAST;
                    break;
                case Direction::SOUTH:
                    x -= moves;
                    direction = Direction::WEST;
                    break;
                case Direction::EAST:
                    y -= moves;
                    direction = Direction::SOUTH;
                    break;
                case Direction::WEST:
                    y += moves;
                    direction = Direction::NORTH;
                    break;
            }
        }
        else if ( strncmp( token, "Lx", 1 ) == 0 ) {
            token++; // Move the pointer to the integer
            int moves = stoi( token ); // Convert string to int value
            printf("Move to the left, %d times\n", moves);
            switch ( direction ) {
                case Direction::NORTH:
                    x -= moves;
                    direction = Direction::WEST;
                    break;
                case Direction::SOUTH:
                    x += moves;
                    direction = Direction::EAST;
                    break;
                case Direction::EAST:
                    y += moves;
                    direction = Direction::NORTH;
                    break;
                case Direction::WEST:
                    y -= moves;
                    direction = Direction::SOUTH;
                    break;
            }
        }
        token = strtok( NULL, DELIMITER );
    }
    printf("New position: ( %d, %d ) \n", x, y );
    x = abs(x);
    y = abs(y);
    printf("Easter Bunny HQ is %d blocks away! \n", x + y);
}