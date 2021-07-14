#ifndef WAITLIST_H
#define WAITLIST_H

#include <vector>

#include "Order.h"

class Waitlist {
 public:
    Waitlist();
    virtual ~Waitlist();

    void addToWaitlist(int orderNum);
    void removeFromWaitlist(int orderNum);
    std::vector<Order> getWaitlist();

 private:
    std::vector<Order> waitOrders;
};

#endif // WAITLIST_H
