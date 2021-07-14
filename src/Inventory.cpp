#include <string>
#include <vector>
#include "Inventory.h"
#include "Exceptions.h"

Inventory::Inventory() {
    //ctor
}

Inventory::~Inventory() {
    //dtor
}

Warehouse Inventory::getWarehouse(int wNum) {
    int index = getWarehouseIndex(wNum);

    if (index != -1) {
        return warehouses[index];
    } else {
        throw invalid_argument_error("Error: No such warehouse exists!");
    }
}

std::vector<Warehouse> Inventory::getAllWarehouses() {
    return warehouses;
}

void Inventory::addWarehouse(Warehouse w) {
    bool alreadyAdded = false;
    for (unsigned int i = 0; i < warehouses.size(); i++) {
        if (warehouses[i].getWarehouseNumber() == w.getWarehouseNumber())
            alreadyAdded = true;
    }
    if (alreadyAdded == false) {
        warehouses.push_back(w);
    }
    if (w.getAllStock().size() != 0) {
        if (allStock.size() != 0) {
            for (unsigned int i = 0; i < w.getAllStock().size(); i++) {
                for (unsigned int j = 0; j < allStock.size(); j++) {
                    if (w.getAllStock()[i].getType() == allStock[j].getType())
                        allStock[j].addQuantity
                        (w.getAllStock()[i].getQuantity());
                    else
                        allStock.push_back(w.getAllStock()[i]);
                }
            }
        } else {
            for (unsigned int i = 0; i < w.getAllStock().size(); i++) {
                allStock.push_back(w.getAllStock()[i]);
            }
        }
    }
}

void Inventory::removeWarehouse(int wNum) {
    int index = getWarehouseIndex(wNum);

    if (index != -1) {
        std::vector<Paper> temp = warehouses[index].getAllStock();
        for (unsigned int i = 0; i < warehouses[index].getAllStock().size();
         i++) {
            if ((index > 0) && (index < warehouses.size() - 1))
                warehouses[0].addStock(warehouses[index].getAllStock()[i]
                .getType(), warehouses[index].getAllStock()[i].getQuantity());
            else
                warehouses[warehouses.size()-1].addStock(warehouses[index]
                .getAllStock()[i].getType(), warehouses[index].getAllStock()[i]
                .getQuantity());
        }
        warehouses.erase(warehouses.begin()+index);
    }
}

void Inventory::addWarehouseStock(int wNum, std::string tp, int amount) {
    int index = getWarehouseIndex(wNum);
    bool inStock = false;

    if (index != -1) {
        int placement = 0;
        warehouses[index].addStock(tp, amount);
        for (unsigned int i = 0; i < allStock.size(); i++) {
            if (allStock[i].getType() == tp) {
                inStock = true;
                break;
            }
            placement++;
        }
        if (inStock == true) {
            allStock[placement].addQuantity(amount);
        } else {
            Paper temp(tp);
            temp.addQuantity(amount);
            allStock.push_back(temp);
        }
    }
}

void Inventory::removeWarehouseStock(int wNum, std::string tp, int amount) {
    int index = getWarehouseIndex(wNum);

    if (index != -1) {
        warehouses[index].removeStock(tp, amount);
        for (unsigned int i = 0; i < allStock.size(); i++) {
            if (allStock[i].getType() == tp) {
                if (allStock[i].getQuantity() > amount) {
                    allStock[i].removeQuantity(amount);
                } else {
                    allStock.erase(allStock.begin()+i);
                }
                break;
            }
        }
    }
}

void Inventory::viewAllStock() {
    std::cout<< "------Inventory------\n";
    std::cout << "\nCurrent Stock:\n\n";
    if (allStock.size() == 0) {
        std::cout << "Empty\n";
    } else {
        for (unsigned int i = 0; i < allStock.size(); i++) {
            std::cout << "Paper Type: " << allStock[i].getType() <<
            "     Amount: " << allStock[i].getQuantity() << "\n";
        }
    }
}

void Inventory::viewCurrentStock(std::string tp) {
    std::cout << "--Current Stock of: " << tp << "--\n";
    //int index = 0;
    for (unsigned int i = 0; i < warehouses.size(); i++) {
        //list warehouses who have which amount of the stock in a list
        for (unsigned int j = 0; j < warehouses[i].getAllStock().size(); j++) {
            if (warehouses[i].getAllStock()[j].getType() == tp) {
                std::cout<< "Warehouse " << warehouses[i].getWarehouseNumber()
                << "   Amount: " << warehouses[i].getAllStock()[j].getQuantity()
                << "\n";
            }
        }
    }
}

void Inventory::viewAllWarehouses() {
    std::cout<< "------Inventory------\n";
    std::cout<< "Warehouses:\n\n";
    if (warehouses.size() == 0) {
        std::cout << "No Warehouses\n";
    } else {
        for (unsigned int i = 0; i < warehouses.size(); i++) {
            std::cout << "Warehouse " << warehouses[i].getWarehouseNumber()
            << "\n";
        }
    }
}

int Inventory::getWarehouseIndex(int wNum) {
    int index = 0;

    for (unsigned int i = 0; i < warehouses.size(); i++) {
        if (warehouses[i].getWarehouseNumber() == wNum) {
            break;
        }
        index++;
    }
    if (index < warehouses.size()) {
        return index;
    } else {
        return -1;
    }
}

std::vector<Paper> Inventory::getAllWarehouseStock() {
    return allStock;
}

void Inventory::viewInventory() {
    std::cout<< "------Inventory------\n";
    std::cout<< "Warehouses:\n\n";
    if (warehouses.size() == 0) {
        std::cout << "No Warehouses\n";
    } else {
        for (unsigned int i = 0; i < warehouses.size(); i++) {
            std::cout << "Warehouse " << warehouses[i].getWarehouseNumber()
            << "\n";
        }
    }
    std::cout << "\nCurrent Stock:\n\n";
    if (allStock.size() == 0) {
        std::cout << "Empty\n";
    } else {
        for (unsigned int i = 0; i < allStock.size(); i++) {
            std::cout << "Paper Type: " << allStock[i].getType() <<
            "     Amount: " << allStock[i].getQuantity() << "\n";
        }
    }
}
