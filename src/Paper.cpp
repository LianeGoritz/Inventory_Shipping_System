#include <string>
#include <algorithm>
#include "Paper.h"

Paper::Paper() {
    type = "standard";
    quantity = 0;
    weight = 0;
}

Paper::Paper(std::string tp) {
    std::string temp = tp;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    type = temp;
    quantity = 0;
    weight = 0;
}

Paper::~Paper() {
    //dtor
}

std::string Paper::getType() {
    return type;
}

void Paper::setType(std::string tp) {
    std::string temp = tp;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    type = temp;
}

int Paper::getQuantity() {
    return quantity;
}

void Paper::addQuantity(int amount) {
    if (amount >= 0) {
        quantity += amount;
        weight = quantity * 10;
    }
}

void Paper::removeQuantity(int amount) {
    if (amount >= 0) {
        quantity -= amount;
        weight = quantity * 10;
    }
}

int Paper::getWeight() {
    return weight;
}
