#include <fstream>
#include <vector>
#include <iostream>

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

struct Coordinate
{
    int x, y;
};

bool operator==(const Coordinate& p1, const Coordinate& p2)
{
    return (p1.x == p2.x) && (p1.y == p2.y);
}

class CityGrid{
    private:
        Direction currentDirection;
        Coordinate coordinate;
        std::vector<Coordinate> coordinates;
        std::vector<Coordinate>::iterator it;

        bool findCoordinate(Coordinate coordinate){
            bool found;
            it = find (coordinates.begin(), coordinates.end(), coordinate);
            if (it != coordinates.end()) {
                printf("Already visited this coordinate, (%d, %d)\n", coordinate.x, coordinate.y);
                printf("Easter Bunny HQ is %d blocks away! \n", abs(coordinate.x) + abs(coordinate.y));
                found = true;
            }
            else {
                std::cout << "Havent visited this coordinate.\n";
                found = false;
            }
            return found;
        }
        void handleXCoordinate( int moves, bool add ){
            if (add){
                for ( int x = getX() + 1; x <= getX() + moves ; x++) {
                    Coordinate coordinate = {x, getY()};
                    if (findCoordinate(coordinate)) {
                        exit(0);
                    } else {
                        // Not there yet lets add the visited coordinate
                        coordinates.push_back(coordinate);
                    }
                }
            }
            else{
                for ( int x = getX() - 1; x >= getX() - moves ; x--) {
                    Coordinate coordinate = {x, getY()};
                    if (findCoordinate(coordinate)) {
                        exit(0);
                    } else {
                        // Not there yet lets add the visited coordinate
                        coordinates.push_back(coordinate);
                    }
                }
            }
        };
        void handleYCoordinate( int moves, bool add ){
            if (add){
                for ( int y = getY() + 1; y <= getY() + moves ; y++) {
                    Coordinate coordinate = {getX(), y};
                    if (findCoordinate(coordinate)) {
                        exit(0);
                    } else {
                        // Not there yet lets add the visited coordinate
                        coordinates.push_back(coordinate);
                    }
                }
            }
            else{
                for ( int y = getY() - 1; y >= getY() - moves ; y--) {
                    Coordinate coordinate = {getX(), y};
                    if (findCoordinate(coordinate)) {
                        exit(0);
                    } else {
                        // Not there yet lets add the visited coordinate
                        coordinates.push_back(coordinate);
                    }
                }
            }
        };
    public:
        CityGrid(){
            Direction currentDirection = Direction::NORTH;
            Coordinate coordinate = { .x=0, .y=0};
            std::vector<Coordinate> coordinates = {coordinate};
        }
        void moveRight( int moves ){
            printf("Move to the right, %d times\n", moves);
            switch ( currentDirection ) {
                case Direction::NORTH:
                    handleXCoordinate(moves, true);
                    coordinate.x += moves;
                    currentDirection = Direction::EAST;
                    break;
                case Direction::SOUTH:
                    handleXCoordinate(moves, false);
                    coordinate.x -= moves;
                    currentDirection = Direction::WEST;
                    break;
                case Direction::EAST:
                    handleYCoordinate(moves,false);
                    coordinate.y -= moves;
                    currentDirection = Direction::SOUTH;
                    break;
                case Direction::WEST:
                    handleYCoordinate(moves,true);
                    coordinate.y += moves;
                    currentDirection = Direction::NORTH;
                    break;
            }
        };
        void moveLeft( int moves ){
            printf("Move to the left, %d times\n", moves);
            switch ( currentDirection ) {
                case Direction::NORTH:
                    handleXCoordinate(moves,false);
                    coordinate.x -= moves;
                    currentDirection = Direction::WEST;
                    break;
                case Direction::SOUTH:
                    handleXCoordinate(moves,true);
                    coordinate.x += moves;
                    currentDirection = Direction::EAST;
                    break;
                case Direction::EAST:
                    handleYCoordinate(moves,true);
                    coordinate.y += moves;
                    currentDirection = Direction::NORTH;
                    break;
                case Direction::WEST:
                    handleYCoordinate(moves,false);
                    coordinate.y -= moves;
                    currentDirection = Direction::SOUTH;
                    break;
            }
        };
        int getX(){
            return coordinate.x;
        };
        int getY(){
            return coordinate.y;
        };
        void addInitCoor(){
            Coordinate coordinate = {0, 0};
            coordinates.push_back(coordinate);
        };

};

int main()
{
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

    // Create city grid;
    CityGrid grid;

    // Wasnt able to initialize with single coordinate at 0,0
    grid.addInitCoor();

    // parse the line
    token = strtok(buf, DELIMITER); // first token
    while ( token != NULL ) {
        printf( "%s\n", token );
        // Parse the direction and # of moves
        if ( strncmp( token, "Rx", 1 ) == 0) {
            token++; // Move pointer to the integer
            int moves = stoi( token );
            grid.moveRight(moves);
        }
        else if ( strncmp( token, "Lx", 1 ) == 0 ) {
            token++; // Move the pointer to the integer
            int moves = stoi( token ); // Convert string to int value
            grid.moveLeft(moves);
        }
        token = strtok( NULL, DELIMITER );
    }
    printf("New position: ( %d, %d ) \n", grid.getX(), grid.getY() );
    //printf("Easter Bunny HQ is %d blocks away! \n", abs(grid.getX()) + abs(grid.getY()));
}