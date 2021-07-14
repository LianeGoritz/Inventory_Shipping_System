#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
 public:
    virtual std::string getType() = 0;

    virtual void setType(std::string tp) = 0;

    virtual int getQuantity() = 0;

    virtual void addQuantity(int amount) = 0;

    virtual void removeQuantity(int amount) = 0;

    virtual int getWeight() = 0;
};

#endif // PRODUCT_H
