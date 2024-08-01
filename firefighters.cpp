#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

const std::string background = "\u{1F3E0}";
const std::string fire = "\u{1F525}";
const std::string firefighter = "\u{1F9D1}";

// Define a struct to hold row and column indices
struct Position {
    int x;
    int y;
};

class Map {
public:
    // Constructor to initialize the 2D vector with a given size and initial value
    Map(int size) : mapSize(size), mapVector(size, std::vector<std::string>(size, background)) {}

    // Method to set the map back to the default background
    void clearMap() {
        for(int row = 0; row < mapSize; row++){
            for(int col = 0; col < mapSize; col++){
                mapVector[row][col] = background; 
            }
        }
    }

    // Method to print the 2D vector
    void print() const {
        clearConsole();
        for (const auto& row : mapVector) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl; // Add an extra newline for better readability between prints
        std::cout.flush(); // JARRED: why should I have this line?
    }

    // Method to set a specific cell in the 2D vector
    void findFire() {

        // TODO: feels like I need error checking here
        while(firefighterPos.x != firePos.x || firefighterPos.y != firePos.y){
            Position oldPos = firefighterPos;
            // Move Firefighter one position closer, always move X first
            if(firefighterPos.x != firePos.x){
                firefighterPos.x = firefighterPos.x > firePos.x ? firefighterPos.x-1 : firefighterPos.x+1;
            }
            else{
                firefighterPos.y = firefighterPos.y > firePos.y ? firefighterPos.y-1 : firefighterPos.y+1;
            }

            // update the game screen
            clear(oldPos.y, oldPos.x);
            updateFirefighter();
            print();

            // wait for a set amount of time at 30FPS-ish
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        }
        std::cout << std::endl << "Fire EXTINGUISHED" << std::endl;
    }

    // Method to start a fire on the map
    // TODO: Start on a random location, right now it just starts bottom left
    void startFire() {
        firePos.x = mapSize-1;
        firePos.y = mapSize-1;
        set(firePos.y, firePos.x, fire);
    }

    // Method to add a firefighter!
    void addFirefighter(int row, int col, const std::string& value) {
        firefighterPos.x = col;
        firefighterPos.y = row;
        set(firefighterPos.y, firefighterPos.x, firefighter);
    }

    void updateFirefighter() {
        set(firefighterPos.y, firefighterPos.x, firefighter);
    }

    // Method to set a specific cell in the 2D vector
    void set(int row, int col, const std::string& value) {
        if (row >= 0 && row < mapSize && col >= 0 && col < mapSize) {
            mapVector[row][col] = value;
        } else {
            std::cerr << "Index out of bounds" << std::endl;
        }
    }

    // Method to clear a specific cell in the 2D vector
    void clear(int row, int col) {
        if (row >= 0 && row < mapSize && col >= 0 && col < mapSize) {
            mapVector[row][col] = background;
        } else {
            std::cerr << "Index out of bounds" << std::endl;
        }
    }

private:
    int mapSize; // Size of the 2D vector
    Position firePos; // Location of the fire
    Position firefighterPos; // location of the firefighter
    std::vector< std::vector<std::string> > mapVector; // 2D vector of strings

    // Method to clear the console (platform-dependent)
    void clearConsole() const {
        // Use the appropriate command for your operating system
        #if defined(_WIN32)
            system("cls");
        #else
            system("clear");
        #endif
    }
};

int main() {

    // Get map size
    int mapSize;
    std::string userIn = "";
    std::cout << "Welcome to FireFighters! Choose your map size (Min 2, Max 30):";
    std::cin >> mapSize;
    mapSize = mapSize < 2 ? 2 : mapSize;
    mapSize = mapSize > 30 ? 30 : mapSize;

    Map map(mapSize);

    while(true){
        map.clearMap();
        map.print();

        std::cout << "Start a fire? (Any Key + Enter):";
        std::cin >> userIn;
        std::cout << std::endl; // JARRED: if i switch this line with the one above my program will start looping infinitely

        // add a fire to the bottom right
        map.startFire();

        // add a firefighter to the top left
        map.addFirefighter(0, 0, firefighter);

        // have the firefighter go to the fire
        map.findFire();
    }

    return 0;
}