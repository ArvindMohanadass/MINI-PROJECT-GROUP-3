#ifndef MENUDISPLAY_HPP
#define MENUDISPLAY_HPP

#include "ParkingLot.hpp"

class MenuDisplay {
public:
    static void displayMenu(ParkingLot& lot);
    static void displayAdminMenu(ParkingLot& lot);
};

#endif // MENUDISPLAY_HPP
