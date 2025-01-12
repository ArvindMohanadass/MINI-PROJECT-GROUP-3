#include "ParkingLot.hpp"
#include "MenuDisplay.hpp"
#include <iostream>

void MenuDisplay::displayMenu(ParkingLot& lot) {
    std::cout << "=========================\n";
    std::cout << "|    Parking Lot Menu   |\n";
    std::cout << "=========================\n";
    std::cout << "| 1. Reserve a Spot     |\n";
    std::cout << "| 2. Release a Spot     |\n";
    std::cout << "| 3. Check In           |\n";
    std::cout << "| 4. Check Out          |\n";
    std::cout << "| 5. Check Reservations |\n";
    std::cout << "| 6. Exit               |\n";
    std::cout << "=========================\n";
}

void MenuDisplay::displayAdminMenu(ParkingLot& lot) {
    std::cout << "=========================\n";
    std::cout << "|      Admin Menu       |\n";
    std::cout << "=========================\n";
    std::cout << "| 1. View All Spots     |\n";
    std::cout << "| 2. Calculate Revenue  |\n";
    std::cout << "| 3. Add Parking Spot   |\n";
    std::cout << "| 4. Remove Parking Spot|\n";
    std::cout << "| 5. View Revenue Table |\n";
    std::cout << "| 6. Exit to Main Menu  |\n";
    std::cout << "| 7. End Program        |\n";
    std::cout << "=========================\n";
}
