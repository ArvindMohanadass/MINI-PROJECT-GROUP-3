#include "ParkingLot.hpp"
#include "UserInputHandler.hpp"
#include "MenuDisplay.hpp"
#include <iostream>
#include <algorithm> // For std::transform

void UserInputHandler::handleUserInput(ParkingLot& lot) {
    int choice;
    std::string spotId, plateNumber;
    while (true) {
        MenuDisplay::displayMenu(lot);
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                lot.displayAvailableSpots();
                std::cout << "Enter your car number plate: ";
                std::cin >> plateNumber;
                std::cout << "Enter spot ID to reserve: ";
                std::cin >> spotId;
                if (lot.reserveSpot(spotId, plateNumber)) {
                    std::cout << "Spot reserved successfully.\n";
                } else {
                    std::cout << "Failed to reserve spot.\n";
                }
                break;
            case 2:
                std::cout << "Enter spot ID to release: ";
                std::cin >> spotId;
                if (lot.releaseSpot(spotId)) {
                    std::cout << "Spot released successfully.\n";
                } else {
                    std::cout << "Failed to release spot.\n";
                }
                break;
            case 3:
                lot.displayAvailableSpots();
                std::cout << "Enter your car number plate: ";
                std::cin >> plateNumber;
                std::cout << "Enter spot ID to check in (or -1 to auto-assign): ";
                std::cin >> spotId;
                if (spotId == "-1") {
                    spotId = lot.findAvailableSpot();
                    if (!spotId.empty() && lot.checkInSpot(spotId, plateNumber)) {
                        std::cout << "Checked in successfully to spot ID " << spotId << ".\n";
                    } else {
                        std::cout << "Failed to check in. No available spots.\n";
                    }
                } else if (lot.checkInSpot(spotId, plateNumber)) {
                    std::cout << "Checked in successfully.\n";
                } else {
                    std::cout << "Failed to check in.\n";
                }
                break;
            case 4:
                std::cout << "Enter your car number plate: ";
                std::cin >> plateNumber;
                std::cout << "Enter spot ID to check out: ";
                std::cin >> spotId;
                if (lot.checkOutSpot(spotId, plateNumber)) {
                    std::cout << "Checked out successfully.\n";
                } else {
                    std::cout << "Failed to check out.\n";
                }
                break;
            case 5:
                lot.checkReservations();
                break;
            case 6:
                lot.enterMenu(); // Return to car number plate entry
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
