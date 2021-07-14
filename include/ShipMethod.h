#ifndef SHIPMETHOD_H
#define SHIPMETHOD_H

#include <iostream>

class ShipMethod {
 public:
    virtual void method(int orderWeight) = 0;
};

class ShipTruck : public ShipMethod {
 public:
    void method(int orderWeight);
};

class ShipAir : public ShipMethod {
 public:
    void method(int orderWeight);
};

class ShipTrain : public ShipMethod {
 public:
    void method(int orderWeight);
};

class ShipShip : public ShipMethod {
 public:
    void method(int orderWeight);
};
#endif // SHIPMETHOD_H
