#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Paper.h"

class Order {
 public:
    Order(int orderNum);
    virtual ~Order();

    int getOrderNumber();
    void addToOrder(std::string tp, int amount);
    void removeFromOrder(std::string tp, int amount);
    std::string getStatus();
    void viewOrder();
    std::vector<Paper> getProducts();
    void changeStatus(std::string st);
    int getTotalWeight();

 private:
    int orderNumber;
    std::string status;
    std::vector<Paper> products;
    int totalWeight;
};

#endif // ORDER_H
