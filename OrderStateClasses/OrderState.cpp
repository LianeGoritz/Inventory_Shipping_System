#include <iostream>
#include "OrderState.h"

OrderState::~OrderState()
{
    //dtor
}

void OrderState::updateStatus(Order& order, std::string st)
{
    order.status = st;
}

void OrderState::addProducts(Order& order, Paper prod)
{
    if(order.products.size() == 0)
        order.products.push_back(prod);
    else
    {
        int index = 0;
        int inOrder = 0;
        for(unsigned int i = 0; i < order.products.size(); i++)
        {
            if(order.products[i].getType() == prod.getType())
            {
                inOrder = 1;
                break;
            }
            index++;
        }
        if(inOrder == 1)
            order.products[index].addQuantity(prod.getQuantity());
        else
        {
            order.getProducts().push_back(prod);
        }
    }
}

void OrderState::removeProducts(Order& order, Paper prod)
{
    int index = 0;
    int inOrder = 0;
    for(unsigned int i = 0; i < order.products.size(); i++)
    {
        if(order.products[i].getType() == prod.getType())
        {
            inOrder = 1;
            break;
        }
        index++;
    }
    if(inOrder == 1)
    {
        if(order.products[index].getQuantity() < prod.getQuantity())
            order.products.erase(order.products.begin()+index);
        else
            order.products[index].removeQuantity(prod.getQuantity());
    }
}
/*
void OrderState::setCurrentState(Order& order, OrderState* state)
{
    OrderState* temp = order.currentState;
    order.currentState = state;

    OrderState* status1 = new InCart();
    OrderState* status2 = new Pending();
    if(state == status1)
        order.getStatus() = "In Cart";
    else if(state == status2)
        order.getStatus() = "Pending";
    else
        order.getStatus() = "Complete";
    delete status1;
    delete status2;
    delete temp;
}
*/
InCart::~InCart()
{
    //dtor
}

void InCart::addToOrder(Order& order, std::string tp, int amount)
{
    Paper temp(tp);
    temp.addQuantity(amount);
    addProducts(order, temp);
}

void InCart::removeFromOrder(Order& order, std::string tp, int amount)
{
    Paper temp(tp);
    temp.addQuantity(amount);
    removeProducts(order, temp);
}

Pending::~Pending()
{

}

void Pending::addToOrder(Order& order, std::string tp, int amount)
{
    std::cout << "This order is pending, the order cannot be changed at this time.\n";
}

void Pending::removeFromOrder(Order& order, std::string tp, int amount)
{
    std::cout << "This order is pending, the order cannot be changed at this time.\n";
}

Complete::~Complete()
{

}

void Complete::addToOrder(Order& order, std::string tp, int amount)
{
    std::cout << "This order is complete, the order cannot be changed at this time.\n";
}

void Complete::removeFromOrder(Order& order, std::string tp, int amount)
{
    std::cout << "This order is complete, the order cannot be changed at this time.\n";
}
