#include <iostream>
#include "Paper.h"
#include "Order.h"
#include "Warehouse.h"
#include "Inventory.h"

using namespace std;

int main() {
    Paper p;
    p.addQuantity(10);

    Paper p2("thicc");
    p2.addQuantity(300);
    //std::cout << p2.getType();

    Order test(100);
    test.addToOrder(p.getType(), p.getQuantity());

    Order test2(25);
    test2.addToOrder(p.getType(), p.getQuantity());
    test2.addToOrder(p2.getType(), p2.getQuantity());
    //test2.viewOrder();
    //std::cout << test2.getProducts()[1].getType();

    Warehouse w(10);
    w.addOrder(test);
    w.addOrder(test2);
    w.viewOrders();
    w.viewWarehouse();
    /*
        w.changeOrderStatus(test.getOrderNumber(), "complete");
        w.cancelOrder(test.getOrderNumber());
        w.viewOrders();
        w.shipOrder(test2.getOrderNumber());
        w.changeOrderStatus(test2.getOrderNumber(), "complete");
        w.viewOrders();
        w.shipOrder(test2.getOrderNumber());
        w.shipOrder(test.getOrderNumber());
        w.viewOrders();
        //w.addStock(p.getType(), p.getQuantity());
        //w.viewStock();
        //w.removeStock(p.getType(), 5);
        //w.viewStock();

        //Warehouse q(14);
        //Warehouse m(20);
    */
    Inventory i;
    //i.viewAllWarehouses();
    i.addWarehouse(w);
    //i.addWarehouse(m);
    //i.getWarehouse(10).viewStock();
    //i.getWarehouse(20).viewStock();
    i.removeWarehouse(10);
    //i.getWarehouse(20).viewStock();
    i.viewAllWarehouses();
    i.addWarehouseStock(20, "wide", 20);
    //i.getWarehouse(20).viewStock();
    i.removeWarehouseStock(20, "wide", 2);
    //i.getWarehouse(20).viewStock();
    //i.viewAllStock();
    i.viewCurrentStock("wide");
    return 0;
}
