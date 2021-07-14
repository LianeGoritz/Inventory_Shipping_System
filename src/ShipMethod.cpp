#include "ShipMethod.h"

void ShipTruck::method(int orderWeight) {
    std::cout << " has been shipped by Truck.\n";
}

void ShipAir::method(int orderWeight) {
    std::cout << " has been shipped by Air.\n";
}

void ShipTrain::method(int orderWeight) {
    std::cout << " has been shipped by Train.\n";
}

void ShipShip::method(int orderWeight) {
    std::cout << " has been shipped by Ship.\n";
}
