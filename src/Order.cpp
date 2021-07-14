#include <string>
#include <vector>
#include <algorithm>
#include "Order.h"

Order::Order(int orderNum) {
    orderNumber = orderNum;
    status = "In Cart";
    totalWeight = 0;
}

Order::~Order() {
}

int Order::getOrderNumber() {
    return orderNumber;
}

void Order::addToOrder(std::string tp, int amount) {
    Paper prod(tp);
    prod.addQuantity(amount);

    if (products.size() == 0) {
        products.push_back(prod);
        totalWeight += prod.getWeight();
    } else {
        int index = 0;
        bool inOrder = false;
        for (unsigned int i = 0; i < products.size(); i++) {
            if (products[i].getType() == tp) {
                inOrder = true;
                break;
            }
            index++;
        }
        if (inOrder == true) {
            products[index].addQuantity(prod.getQuantity());
            totalWeight += prod.getWeight();
        } else {
            products.push_back(prod);
            totalWeight += prod.getWeight();
        }
    }
}

void Order::removeFromOrder(std::string tp, int amount) {
    Paper prod(tp);
    prod.addQuantity(amount);
    int index = 0;
    int inOrder = 0;
    for (unsigned int i = 0; i < products.size(); i++) {
        if (products[i].getType() == prod.getType()) {
            inOrder = 1;
            break;
        }
        index++;
    }
    if (inOrder == 1) {
        if (products[index].getQuantity() < prod.getQuantity()) {
            products.erase(products.begin()+index);
            totalWeight -= prod.getWeight();
        } else {
            products[index].removeQuantity(prod.getQuantity());
            totalWeight -= prod.getWeight();
        }
    }
}

std::string Order::getStatus() {
    return status;
}

void Order::changeStatus(std::string st) {
    std::string temp = st;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

    if (temp.compare("pending") == 0) {
        // currentState = new Pending();
        status = "Pending";
    } else if (temp.compare("in cart") == 0) {
        //currentState = new InCart();
        status = "In Cart";
    } else if (temp.compare("complete") == 0) {
        //currentState = new Complete();
        status = "Complete";
    }
}

void Order::viewOrder() {
    std::cout << "--Order: " << orderNumber << "--\n";
    std::cout << "Status: " << status << "\n";
    std::cout << "Weight: " << totalWeight << "\n";
    if (products.size() == 0) {
        std::cout << "Empty\n";
    } else {
        std::cout << "Product:\n";
        for (unsigned int i = 0; i < products.size(); i++) {
            std::cout << products[i].getType() << "  Quantity: "
            << products[0].getQuantity() << "\n";
        }
    }
}

std::vector<Paper> Order::getProducts() {
    return products;
}

int Order::getTotalWeight() {
    return totalWeight;
}
