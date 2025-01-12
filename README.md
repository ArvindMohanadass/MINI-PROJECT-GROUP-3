# MINI-PROJECT-GROUP-3
# Parking Lot Management System

This Parking Lot Management System allows users to reserve, check in, and check out parking spots. It also provides an admin interface to manage parking spots and view revenue.

## User Functions

### 1. Reserve a Spot
- **Description**: Allows a user to reserve a parking spot.
- **Steps**:
  1. Enter your car number plate.
  2. Enter the spot ID you want to reserve.
  3. If the spot is available, it will be reserved for you.

### 2. Release a Spot
- **Description**: Allows a user to release a reserved parking spot.
- **Steps**:
  1. Enter the spot ID you want to release.
  2. If the spot is reserved and not checked in, it will be released.

### 3. Check In
- **Description**: Allows a user to check in to a reserved parking spot.
- **Steps**:
  1. Enter your car number plate.
  2. Enter the spot ID you want to check in to (or enter `-1` to auto-assign an available spot).
  3. If the spot is available, you will be checked in.

### 4. Check Out
- **Description**: Allows a user to check out from a parking spot.
- **Steps**:
  1. Enter your car number plate.
  2. Enter the spot ID you want to check out from.
  3. If you are checked in, you will be checked out and the hourly rate will be added to the total revenue.

### 5. Check Reservations
- **Description**: Displays all reserved parking spots.
- **Steps**:
  1. Select the option to check reservations.
  2. All reserved spots will be displayed.

### 6. Exit
- **Description**: Exits the user menu and returns to the car number plate entry.

## Admin Functions

### 1. View All Spots
- **Description**: Displays all parking spots with their status (reserved, checked in, plate number).
- **Steps**:
  1. Select the option to view all spots.
  2. All spots with their status will be displayed.

### 2. Calculate Revenue
- **Description**: Displays the total revenue generated from checked out spots.
- **Steps**:
  1. Select the option to calculate revenue.
  2. The total revenue will be displayed.

### 3. Add Parking Spot
- **Description**: Allows the admin to add a new parking spot.
- **Steps**:
  1. Enter the new spot ID.
  2. Enter the hourly rate for the new spot.
  3. The new spot will be added to the system.

### 4. Remove Parking Spot
- **Description**: Allows the admin to remove an existing parking spot.
- **Steps**:
  1. Enter the spot ID you want to remove.
  2. The spot will be removed from the system.

### 5. View Revenue Table
- **Description**: Displays a table of all revenue entries with plate numbers and amounts.
- **Steps**:
  1. Select the option to view the revenue table.
  2. The revenue table will be displayed.

### 6. Exit to Main Menu
- **Description**: Exits the admin menu and returns to the car number plate entry.

### 7. End Program
- **Description**: Ends the program.
- **Steps**:
  1. Select the option to end the program.
  2. The program will terminate.

## Files

### `ParkingSpot.hpp`
- Defines the `ParkingSpot` class with attributes like `id`, `isReserved`, `isCheckedIn`, `hourlyRate`, and `plateNumber`.

### `ParkingLot.hpp`
- Defines the `ParkingLot` class with methods to manage parking spots and handle user/admin input.

### `ParkingLot.cpp`
- Implements the methods defined in `ParkingLot.hpp`.

### `UserInputHandler.hpp` and `UserInputHandler.cpp`
- Defines and implements the `UserInputHandler` class to handle user input.

### `AdminInputHandler.hpp` and `AdminInputHandler.cpp`
- Defines and implements the `AdminInputHandler` class to handle admin input.

### `MenuDisplay.hpp` and `MenuDisplay.cpp`
- Defines and implements the `MenuDisplay` class to display user and admin menus.

### `main.cpp`
- The main entry point of the program that initializes the parking lot and starts the menu.

### `parking_lot.csv`
- A CSV file that stores the parking spot data.

### `revenue.csv`
- A CSV file that stores the revenue data.

## How to Run

1. Compile the program using a C++ compiler.
2. Run the executable.
3. Follow the on-screen instructions to interact with the system.
4. Make sure task.json is configured to run all cpp files. You can copy and paste
the task.json from below.

# task.json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe build active file",
            "command": "C:\\msys64\\mingw64\\bin\\g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task generated by Debugger."
        }
    ],
    "version": "2.0.0"
}
