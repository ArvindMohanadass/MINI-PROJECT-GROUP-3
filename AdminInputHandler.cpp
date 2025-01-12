#include "AdminInputHandler.hpp"
#include "MenuDisplay.hpp"
#include <iostream>

void AdminInputHandler::handleAdminInput(ParkingLot& lot) {
    int choice;
    std::string spotId;
    double hourlyRate;
    while (true) {
        MenuDisplay::displayAdminMenu(lot);
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                for (const auto& spot : lot.spots) {
                    std::cout << "Spot ID: " << spot.id << ", Reserved: " << (spot.isReserved ? "Yes" : "No") << ", Checked In: " << (spot.isCheckedIn ? "Yes" : "No") << ", Plate Number: " << spot.plateNumber << "\n";
                }
                break;
            case 2:
                std::cout << "Total Revenue: $" << lot.calculateRevenue() << std::endl;
                break;
            case 3:
                std::cout << "Enter new spot ID: ";
                std::cin >> spotId;
                std::cout << "Enter hourly rate for new spot: ";
                std::cin >> hourlyRate;
                lot.addParkingSpot(spotId, hourlyRate);
                std::cout << "Parking spot added successfully.\n";
                lot.saveToCSV("parking_lot.csv");
                break;
            case 4:
                std::cout << "Enter spot ID to remove: ";
                std::cin >> spotId;
                lot.removeParkingSpot(spotId);
                std::cout << "Parking spot removed successfully.\n";
                lot.saveToCSV("parking_lot.csv");
                break;
            case 5:
                lot.displayRevenue();
                break;
            case 6:
                lot.enterMenu(); // Return to car number plate entry
                return;
            case 7:
                lot.endProgram(); // End the program
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
