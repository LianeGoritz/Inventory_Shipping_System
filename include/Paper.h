#ifndef PAPER_H
#define PAPER_H

#include <string>
#include <vector>
#include <algorithm>

#include "Product.h"

class Paper : public Product {
 public:
    Paper();
    Paper(std::string tp);
    virtual ~Paper();

    std::string getType();

    void setType(std::string tp);

    int getQuantity();

    void addQuantity(int amount);

    void removeQuantity(int amount);

    int getWeight();

 private:
    std::string type;
    int quantity;
    int weight;
};

#endif // PAPER_H
