#include "ParkingLot.hpp"
#include "UserInputHandler.hpp"
#include "AdminInputHandler.hpp"
#include <iostream>
#include <fstream>   // For file operations
#include <sstream>   // For string stream
#include <algorithm> // For std::transform

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

void ParkingLot::displayAvailableSpots() const {
    std::cout << "Available spots: ";
    for (const auto& spot : spots) {
        if (!spot.isReserved) {
            std::cout << spot.id << " ";
        }
    }
    std::cout << std::endl;
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

void ParkingLot::handleUserInput() {
    UserInputHandler::handleUserInput(*this);
}

void ParkingLot::handleAdminInput() {
    AdminInputHandler::handleAdminInput(*this);
}
