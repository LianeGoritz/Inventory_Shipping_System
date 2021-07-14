#include "Shipping.h"

Shipping::~Shipping() {
    delete shipme;
}

void Shipping::ship(Order ord) {
    int weight = ord.getTotalWeight();

    if (weight <= 100) {
        shipme = new ShipTruck();
    } else if ((weight > 100) && (weight <= 1000)) {
        shipme = new ShipAir();
    } else if ((weight > 1000) && (weight <= 10000)) {
        shipme = new ShipTrain();
    } else {
        shipme = new ShipShip();
    }
    std::cout << "\nOrder " << ord.getOrderNumber();
    shipme->method(weight);
}
