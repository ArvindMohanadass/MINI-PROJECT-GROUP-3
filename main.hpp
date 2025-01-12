#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <vector>

class ParkingSpot {
public:
    std::string id;
    bool isReserved;
    bool isCheckedIn;
    double hourlyRate;
    std::string plateNumber; // Add car plate number
    // ...existing code...
};

class ParkingLot {
public:
    ParkingLot(int totalSpots);
    bool reserveSpot(const std::string& spotId, const std::string& plateNumber);
    bool releaseSpot(const std::string& spotId);
    bool checkInSpot(const std::string& spotId, const std::string& plateNumber);
    bool checkOutSpot(const std::string& spotId, const std::string& plateNumber);
    double calculateRevenue() const;
    void displayMenu();
    void handleUserInput();
    void enterMenu();
    void displayAvailableSpots() const;
    void displayAdminMenu();
    void handleAdminInput();
    void addParkingSpot(const std::string& spotId, double hourlyRate);
    void removeParkingSpot(const std::string& spotId);
    std::string findAvailableSpot() const;
    void endProgram() const;
    void saveToCSV(const std::string& filename) const;
    void loadFromCSV(const std::string& filename);
    void checkReservations() const;
    void trackRevenue(const std::string& plateNumber, double amount) const;
    void displayRevenue(); // Remove const qualifier
    void displayTotalRevenue() const; // Add method to display total revenue from revenue.csv in a table format for the admin with an option to go back to the admin menu
    // ...existing code...
private:
    std::vector<ParkingSpot> spots;
    double totalRevenue;
    const std::string adminCarNumberPlate = "ADMIN123"; // Example admin car number plate
    // ...existing code...
};

#endif // MAIN_HPP
