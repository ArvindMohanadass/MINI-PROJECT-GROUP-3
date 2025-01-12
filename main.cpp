#include "ParkingLot.hpp"
#include "UserInputHandler.hpp"
#include "AdminInputHandler.hpp"

int main() {
    ParkingLot lot(100); // Create a parking lot with 100 spots
    lot.enterMenu();     // Start the menu interaction
    return 0;            // Exit the program
}