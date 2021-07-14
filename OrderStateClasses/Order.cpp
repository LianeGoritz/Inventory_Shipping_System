#include <iostream>
#include <algorithm>
#include "Order.h"

Order::Order(int orderNum)
{
    orderNumber = orderNum;
    currentState = new InCart();
    status = "In Cart";
}

Order::Order(const Order& order)
{
    orderNumber = order.orderNumber;
    status = order.status;

    if(status == "in cart")
        currentState = new InCart();
    else if (status == "pending")
        currentState = new Pending();
    else if (status == "complete")
        currentState = new Complete();
}

Order::~Order()
{
    delete currentState;
}

int Order::getOrderNumber()
{
    return orderNumber;
}

void Order::addToOrder(std::string tp, int amount)
{
    currentState->addToOrder(*this, tp, amount);
}

void Order::removeFromOrder(std::string tp, int amount)
{
    currentState->removeFromOrder(*this, tp, amount);
}

std::string Order::getStatus()
{
    return status;
}
//*****************************************************************
void Order::changeStatus(std::string st)
{
    std::string temp = st;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

    if(temp == "pending")
    {
        currentState = new Pending();
        status = "Pending";
    }
    else if(temp == "in Cart")
    {
        currentState = new InCart();
        status = "In Cart";
    }
    else if (temp == "complete")
    {
        currentState = new Complete();
        status = "Complete";
    }
}

void Order::viewOrder()
{
    std::cout << "--Order: " << orderNumber << "--\n";
    std::cout << "Status: " << status << "\n";
    if(products.size() == 0)
        std::cout << "Empty\n";
    else
    {
        for(unsigned int i = 0; i < products.size(); i++)
            std::cout << "Product: " << products[0].getType() << "  Quantity: " << products[0].getQuantity() << "\n";
    }
}

std::vector<Paper> Order::getProducts()
{
    return products;
}

OrderState* Order::getCurrentState()
{
    return currentState;
}
