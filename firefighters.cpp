#include <iostream>
#include <vector>
#include <string>

class Map {
public:
    // Constructor to initialize the 2D vector with a given size and initial value
    Map(int size, const std::string& initialValue) : mapSize(size), mapVector(size, std::vector<std::string>(size, initialValue)) {}

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
        //std::cout.flush(); // Ensure the output is immediately displayed JARRED, why should I add this line?
    }

    // Method to set a specific cell in the 2D vector
    void set(int row, int col, const std::string& value) {
        if (row >= 0 && row < mapSize && col >= 0 && col < mapSize) {
            mapVector[row][col] = value;
        } else {
            std::cerr << "Index out of bounds" << std::endl;
        }
    }
    

private:
    int mapSize; // Size of the 2D vector
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
    std::cout << "Welcome to FireFighters! Choose your map size (Max 50):";
    std::cin >> mapSize;
    mapSize = mapSize > 50 ? 50 : mapSize;

    Map map(mapSize, "-");

    map.print();

    while(true){
        std::cout << "Start a fire?:";
        std::cin >> mapSize;
        std::cout << std::endl; // JARRED: if i switch this line with the one above my program will start looping infinitely

        map.print();
        
        // add a fire to the bottom right

        // add a firefighter to the top left

        // have the firefighter go to the fire
    }


    return 0;
}