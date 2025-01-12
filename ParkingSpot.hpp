#ifndef PARKINGSPOT_HPP
#define PARKINGSPOT_HPP

#include <string>

class ParkingSpot {
public:
    std::string id;
    bool isReserved;
    bool isCheckedIn;
    double hourlyRate;
    std::string plateNumber; // Add car plate number
};

#endif // PARKINGSPOT_HPP
