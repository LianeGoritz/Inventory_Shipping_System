#include <string>
#include <vector>
#include "Warehouse.h"
#include "Exceptions.h"

Warehouse::Warehouse(int wNum) {
    warehouseNumber = wNum;
}

Warehouse::~Warehouse() {
    //ship.~Shipping();
}

int Warehouse::getWarehouseNumber() {
    return warehouseNumber;
}

void Warehouse::setWarehouseNumber(int wNum) {
    if (wNum > 0) {
    warehouseNumber = wNum;
    }
}

void Warehouse::viewWarehouse() {
    std::cout << "\n------Warehouse Number " << warehouseNumber
    << "------\n";
    std::cout << "Current Orders:\n";
    if (orders.size() == 0) {
        std::cout << "\nEmpty\n";
    } else {
        for (unsigned int i = 0; i < orders.size(); i++) {
            std::cout << "\n";
            orders[i].viewOrder();
        }
    }

    std::cout << "\nCurrent Stock:\n\n";
    if (stock.size() == 0) {
        std::cout << "Empty\n";
    } else {
        for (unsigned int i = 0; i < stock.size(); i++) {
            std::cout <<"Paper Type: " << stock[i].getType()
            << "     Amount: " << stock[i].getQuantity() << "\n";
        }
    }
}

Paper Warehouse::getStock(std::string tp) {
    int index = 0;

    for (unsigned int i = 0; i < stock.size(); i++) {
        if (stock[i].getType() == tp) {
            break;
        }
        index++;
    }
    if (stock[index].getType() == tp) {
        return stock[index];
    } else {
        throw invalid_argument_error("Error: No such stock exists here!");
    }
}

std::vector<Paper> Warehouse::getAllStock() {
    return stock;
}

void Warehouse::viewStock() {
    std::cout << "\n------Warehouse Number " << warehouseNumber
    << "------\n";
    std::cout << "\nCurrent Stock:\n\n";
    if (stock.size() == 0) {
        std::cout << "Empty\n";
    } else {
        for (unsigned int i = 0; i < stock.size(); i++) {
            std::cout <<"Paper Type: " << stock[i].getType()
            << "     Amount: " << stock[i].getQuantity() << "\n";
        }
    }
}

void Warehouse::addStock(std::string tp, int amount) {
    int index = 0;
    bool haveStock = false;

    for (unsigned int i = 0; i < stock.size(); i++) {
        if (stock[i].getType() == tp) {
            haveStock = true;
            break;
        }
        index++;
    }
    if (haveStock == true) {
        stock[index].addQuantity(amount);
    } else {
        Paper temp(tp);
        temp.addQuantity(amount);
        stock.push_back(temp);
    }
}

void Warehouse::removeStock(std::string tp, int amount) {
    int index = 0;
    bool haveStock = false;

    for (unsigned int i = 0; i < stock.size(); i++) {
        if (stock[i].getType() == tp) {
            haveStock = true;
            break;
        }
        index++;
    }

    if ((haveStock == true)) {
        if (stock[index].getQuantity() > amount) {
            stock[index].removeQuantity(amount);
        } else {
            stock.erase(stock.begin()+index);
        }
    }
}

Order Warehouse::getOrder(int orderNum) {
    int index = getOrderIndex(orderNum);

    if (index != -1) {
        return orders[index];
    } else {
        throw invalid_argument_error("Error: No such order exists here!");
    }
}

std::vector<Order> Warehouse::getAllOrders() {
    return orders;
}

void Warehouse::viewOrders() {
    std::cout << "\n------Warehouse Number " << warehouseNumber
    << "------\n";
    std::cout << "Current Orders:\n";
    if (orders.size() == 0) {
        std::cout << "\nEmpty\n";
    } else {
        for (unsigned int i = 0; i < orders.size(); i++) {
            orders[i].viewOrder();
        }
    }
}

void Warehouse::addOrder(Order ord) {
    bool duplicateOrder = false;
    for (unsigned int i = 0; i < orders.size(); i++) {
        if (orders[i].getOrderNumber() == ord.getOrderNumber())
            duplicateOrder = true;
    }
    if (duplicateOrder == false) {
        orders.push_back(ord);
    }
}

void Warehouse::removeOrder(int orderNum) {
    int index = getOrderIndex(orderNum);

    if (index != -1) {
        orders.erase(orders.begin()+index);
    }
}

void Warehouse::submitOrder(int orderNum) {
    int index = getOrderIndex(orderNum);

    if (index != -1) {
        if (orders[index].getStatus().compare("in cart") != 0) {
            orders[index].changeStatus("pending");
            std::cout << "\nOrder " << orders[index].getOrderNumber()
            << " has been successfully submitted.\n";
        } else {
            std::cout << "\nOrder " << orders[index].getOrderNumber()
            << " has already been submitted.\n";
        }
    }
}

void Warehouse::cancelOrder(int orderNum) {
    int index = getOrderIndex(orderNum);

    if (index != -1) {
        if ((orders[index].getStatus().compare("In Cart") == 0) ||
            (orders[index].getStatus().compare("Pending") == 0)) {
            std::cout << "\nOrder " << orders[index].getOrderNumber()
                << " has been successfully cancelled.\n";
            orders.erase(orders.begin()+index);
        } else {
            std::cout << "\nOrder " << orders[index].getOrderNumber()
            << " could not be cancelled, order is already complete.\n";
        }
    }
}

void Warehouse::shipOrder(int orderNum) {
    int index = getOrderIndex(orderNum);

    if (index != -1) {
        if (orders[index].getStatus().compare("Complete") == 0) {
            Shipping ship;
            ship.ship(orders[index]);
            orders.erase(orders.begin()+index);
        } else {
            std::cout << "\nOrder " << orders[index].getOrderNumber()
            << " could not be shipped, order is incomplete.\n";
        }
    }
}

void Warehouse::changeOrderStatus(int orderNum, std::string st) {
    int index = getOrderIndex(orderNum);

    if (index != -1) {
        orders[index].changeStatus(st);
    } else {
        return;
    }
}

int Warehouse::getOrderIndex(int orderNum) {
    int index = 0;

    for (unsigned int i = 0; i < orders.size(); i++) {
        if (orderNum == orders[i].getOrderNumber()) {
            break;
        }
        index++;
    }
    if (index < orders.size()) {
        return index;
    } else {
        return -1;
    }
}
