#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <vector>
#include <iostream>

#include "Order.h"
#include "Shipping.h"

class Warehouse {
 public:
    Warehouse(int wNum);
    virtual ~Warehouse();

    int getWarehouseNumber();

    void setWarehouseNumber(int wNum);

    void viewWarehouse();

    Paper getStock(std::string tp);

    std::vector<Paper> getAllStock();

    void viewStock();

    void addStock(std::string tp, int amount);

    void removeStock(std::string tp, int amount);

    Order getOrder(int orderNum);

    std::vector<Order> getAllOrders();

    void viewOrders();

    void addOrder(Order ord);

    void removeOrder(int orderNum);

    void submitOrder(int orderNum);

    void cancelOrder(int orderNum);

    void shipOrder(int orderNum);

    void changeOrderStatus(int orderNum, std::string st);

    int getOrderIndex(int orderNum);

 private:
    int warehouseNumber;
    std::vector<Paper> stock;
    std::vector<Order> orders;
};

#endif // WAREHOUSE_H
