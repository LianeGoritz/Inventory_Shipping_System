#ifndef SHIPPING_H
#define SHIPPING_H

#include <iostream>

#include "Order.h"
#include "ShipMethod.h"

class Shipping {
 public:
    virtual ~Shipping();
    void ship(Order ord);


 private:
    ShipMethod* shipme;
};
#endif // SHIPPING_H
