#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <vector>

#include "Warehouse.h"
#include "Order.h"
#include "Paper.h"
#include "Shipping.h"

class Inventory {
 public:
    Inventory();
    virtual ~Inventory();

    Warehouse getWarehouse(int wNum);
    std::vector<Warehouse> getAllWarehouses();
    void addWarehouse(Warehouse w);
    void removeWarehouse(int wNum);
    void addWarehouseStock(int wNum, std::string tp, int amount);
    void removeWarehouseStock(int wNum, std::string tp, int amount);
    void viewAllStock();
    void viewCurrentStock(std::string tp);
    void viewAllWarehouses();
    int getWarehouseIndex(int wNum);
    std::vector<Paper> getAllWarehouseStock();
    void viewInventory();

 private:
    std::vector<Warehouse> warehouses;
    std::vector<Paper> allStock;
};

#endif // INVENTORY_H
