#include "ParkingLot.hpp"
#include "UserInputHandler.hpp"
#include "AdminInputHandler.hpp"
#include <iostream>
#include <string>
#include <algorithm> // For std::transform
#include <fstream>   // For file operations
#include <sstream>   // For string stream

// ...existing code...

ParkingLot::ParkingLot(int totalSpots) : totalRevenue(0) {
    loadFromCSV("parking_lot.csv");
    if (spots.empty()) {
        for (int i = 1; i <= totalSpots; ++i) {
            spots.push_back({std::to_string(i) + "A", false, false, 10.0, ""}); // Default hourly rate is 10.0
        }
    }
}

bool ParkingLot::reserveSpot(const std::string& spotId, const std::string& plateNumber) {
    for (auto& spot : spots) {
        if (spot.id == spotId && !spot.isReserved) {
            spot.isReserved = true;
            spot.plateNumber = plateNumber;
            saveToCSV("parking_lot.csv");
            return true;
        }
    }
    return false;
}

bool ParkingLot::releaseSpot(const std::string& spotId) {
    for (auto& spot : spots) {
        if (spot.id == spotId && spot.isReserved && !spot.isCheckedIn) {
            spot.isReserved = false;
            spot.plateNumber = "";
            saveToCSV("parking_lot.csv");
            return true;
        }
    }
    return false;
}

bool ParkingLot::checkInSpot(const std::string& spotId, const std::string& plateNumber) {
    for (auto& spot : spots) {
        if (spot.id == spotId && !spot.isCheckedIn) {
            spot.isCheckedIn = true;
            spot.isReserved = true;
            spot.plateNumber = plateNumber;
            saveToCSV("parking_lot.csv");
            return true;
        }
    }
    return false;
}

bool ParkingLot::checkOutSpot(const std::string& spotId, const std::string& plateNumber) {
    for (auto& spot : spots) {
        if (spot.id == spotId && spot.isCheckedIn) {
            spot.isCheckedIn = false;
            spot.isReserved = false;
            totalRevenue += spot.hourlyRate; // Add hourly rate to total revenue
            saveToCSV("parking_lot.csv");
            trackRevenue(plateNumber, spot.hourlyRate);
            spot.plateNumber = "";
            return true;
        }
    }
    return false;
}

double ParkingLot::calculateRevenue() const {
    return totalRevenue;
}

void ParkingLot::displayMenu() {
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

void ParkingLot::handleUserInput() {
    int choice;
    std::string spotId, plateNumber;
    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                displayAvailableSpots();
                std::cout << "Enter your car number plate: ";
                std::cin >> plateNumber;
                std::cout << "Enter spot ID to reserve: ";
                std::cin >> spotId;
                if (reserveSpot(spotId, plateNumber)) {
                    std::cout << "Spot reserved successfully.\n";
                } else {
                    std::cout << "Failed to reserve spot.\n";
                }
                break;
            case 2:
                std::cout << "Enter spot ID to release: ";
                std::cin >> spotId;
                if (releaseSpot(spotId)) {
                    std::cout << "Spot released successfully.\n";
                } else {
                    std::cout << "Failed to release spot.\n";
                }
                break;
            case 3:
                displayAvailableSpots();
                std::cout << "Enter your car number plate: ";
                std::cin >> plateNumber;
                std::cout << "Enter spot ID to check in (or -1 to auto-assign): ";
                std::cin >> spotId;
                if (spotId == "-1") {
                    spotId = findAvailableSpot();
                    if (!spotId.empty() && checkInSpot(spotId, plateNumber)) {
                        std::cout << "Checked in successfully to spot ID " << spotId << ".\n";
                    } else {
                        std::cout << "Failed to check in. No available spots.\n";
                    }
                } else if (checkInSpot(spotId, plateNumber)) {
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
                if (checkOutSpot(spotId, plateNumber)) {
                    std::cout << "Checked out successfully.\n";
                } else {
                    std::cout << "Failed to check out.\n";
                }
                break;
            case 5:
                checkReservations();
                break;
            case 6:
                enterMenu(); // Return to car number plate entry
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void ParkingLot::enterMenu() {
    std::string carNumberPlate;
    std::cout << "Enter your car number plate: ";
    std::cin >> carNumberPlate;
    std::transform(carNumberPlate.begin(), carNumberPlate.end(), carNumberPlate.begin(), ::toupper);
    if (carNumberPlate == adminCarNumberPlate) {
        std::cout << "Welcome, Admin!\n";
        handleAdminInput();
    } else {
        std::cout << "Welcome, car number plate " << carNumberPlate << "!\n";
        handleUserInput();
    }
}

void ParkingLot::displayAvailableSpots() const {
    std::cout << "Available spots: ";
    for (const auto& spot : spots) {
        if (!spot.isReserved) {
            std::cout << spot.id << " ";
        }
    }
    std::cout << std::endl;
}

void ParkingLot::displayAdminMenu() {
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

void ParkingLot::handleAdminInput() {
    int choice;
    std::string spotId;
    double hourlyRate;
    while (true) {
        displayAdminMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                for (const auto& spot : spots) {
                    std::cout << "Spot ID: " << spot.id << ", Reserved: " << (spot.isReserved ? "Yes" : "No") << ", Checked In: " << (spot.isCheckedIn ? "Yes" : "No") << ", Plate Number: " << spot.plateNumber << "\n";
                }
                break;
            case 2:
                std::cout << "Total Revenue: $" << calculateRevenue() << std::endl;
                break;
            case 3:
                std::cout << "Enter new spot ID: ";
                std::cin >> spotId;
                std::cout << "Enter hourly rate for new spot: ";
                std::cin >> hourlyRate;
                addParkingSpot(spotId, hourlyRate);
                std::cout << "Parking spot added successfully.\n";
                saveToCSV("parking_lot.csv");
                break;
            case 4:
                std::cout << "Enter spot ID to remove: ";
                std::cin >> spotId;
                removeParkingSpot(spotId);
                std::cout << "Parking spot removed successfully.\n";
                saveToCSV("parking_lot.csv");
                break;
            case 5:
                displayRevenue();
                break;
            case 6:
                enterMenu(); // Return to car number plate entry
                return;
            case 7:
                endProgram(); // End the program
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void ParkingLot::addParkingSpot(const std::string& spotId, double hourlyRate) {
    spots.push_back({spotId, false, false, hourlyRate, ""});
}

void ParkingLot::removeParkingSpot(const std::string& spotId) {
    auto it = std::remove_if(spots.begin(), spots.end(), [&](const ParkingSpot& spot) {
        return spot.id == spotId;
    });
    if (it != spots.end()) {
        if (it->isReserved) {
            totalRevenue -= it->hourlyRate; // Adjust revenue if spot is reserved
        }
        spots.erase(it, spots.end());
    }
}

std::string ParkingLot::findAvailableSpot() const {
    for (const auto& spot : spots) {
        if (!spot.isReserved) {
            return spot.id;
        }
    }
    return ""; // No available spots
}

void ParkingLot::endProgram() const {
    std::cout << "Ending program. Goodbye!\n";
    exit(0);
}

void ParkingLot::saveToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "id,isReserved,isCheckedIn,hourlyRate,plateNumber\n";
        for (const auto& spot : spots) {
            file << spot.id << "," << spot.isReserved << "," << spot.isCheckedIn << "," << spot.hourlyRate << "," << spot.plateNumber << "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

void ParkingLot::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Skip header line
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string token;
            ParkingSpot spot;
            std::getline(ss, token, ',');
            spot.id = token;
            std::getline(ss, token, ',');
            spot.isReserved = std::stoi(token);
            std::getline(ss, token, ',');
            spot.isCheckedIn = std::stoi(token);
            std::getline(ss, token, ',');
            spot.hourlyRate = std::stod(token);
            std::getline(ss, token, ',');
            spot.plateNumber = token;
            spots.push_back(spot);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
}

void ParkingLot::checkReservations() const {
    std::cout << "Reserved spots: ";
    for (const auto& spot : spots) {
        if (spot.isReserved) {
            std::cout << spot.id << " ";
        }
    }
    std::cout << std::endl;
}

void ParkingLot::trackRevenue(const std::string& plateNumber, double amount) const {
    std::ofstream file("revenue.csv", std::ios::app);
    if (file.is_open()) {
        file << plateNumber << "," << amount << "\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for writing: revenue.csv" << std::endl;
    }
}

void ParkingLot::displayRevenue() {
    std::ifstream file("revenue.csv");
    if (file.is_open()) {
        std::string line;
        std::cout << "=========================\n";
        std::cout << "|    Revenue Table      |\n";
        std::cout << "=========================\n";
        std::cout << "| Plate Number | Amount |\n";
        std::cout << "=========================\n";
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string plateNumber, amount;
            std::getline(ss, plateNumber, ',');
            std::getline(ss, amount, ',');
            std::cout << "| " << plateNumber << " | $" << amount << " |\n";
        }
        std::cout << "=========================\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for reading: revenue.csv" << std::endl;
    }
    std::cout << "Press any key to return to the admin menu...";
    std::cin.ignore();
    std::cin.get();
    handleAdminInput();
}

// ...existing code...

int main() {
    ParkingLot lot(100); // Create a parking lot with 100 spots
    lot.enterMenu();
    return 0;
}
