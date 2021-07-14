#include <vector>
//#include <sstream>
#include "gtest/gtest.h"
#include "Warehouse.h"

TEST(WarehouseTest, constructorTest) {
    Warehouse w(10);
    EXPECT_EQ(10, w.getWarehouseNumber());

    Warehouse w2(302);
    EXPECT_EQ(302, w2.getWarehouseNumber());
}

TEST(WarehouseTest, getWarehouseNumberTest) {
    Warehouse w(20);
    EXPECT_EQ(20, w.getWarehouseNumber());

    w.setWarehouseNumber(340);
    EXPECT_EQ(340, w.getWarehouseNumber());
}

TEST(WarehouseTest, setWarehouseNumberTest) {
    Warehouse w(20);
    EXPECT_EQ(20, w.getWarehouseNumber());

    w.setWarehouseNumber(340);
    EXPECT_EQ(340, w.getWarehouseNumber());

    w.setWarehouseNumber(-10);
    EXPECT_EQ(340, w.getWarehouseNumber());
}

TEST(WarehouseTest, getStockTest) {
    Paper p;
    p.addQuantity(20);
    Warehouse w(10);
    w.addStock(p.getType(), p.getQuantity());
    EXPECT_EQ("standard", w.getStock("standard").getType());
    EXPECT_EQ(20, w.getStock("standard").getQuantity());
    EXPECT_EQ(200, w.getStock("standard").getWeight());

    Paper p2("wide");
    p2.addQuantity(10);
    w.addStock(p2.getType(), p2.getQuantity());
    EXPECT_EQ("wide", w.getStock("wide").getType());
    EXPECT_EQ(10, w.getStock("wide").getQuantity());
    EXPECT_EQ(100, w.getStock("wide").getWeight());
}

TEST(WarehouseTest, getAllStockTest) {
    Paper p("thicc");
    p.addQuantity(55);
    Paper p2("wide");
    p2.addQuantity(12);
    Warehouse w(15);
    EXPECT_EQ(0, w.getAllStock().size());

    w.addStock(p.getType(), p.getQuantity());
    w.addStock(p2.getType(), p2.getQuantity());
    EXPECT_EQ(2, w.getAllStock().size());
    EXPECT_EQ("thicc", w.getAllStock()[0].getType());
    EXPECT_EQ("wide", w.getAllStock()[1].getType());
    EXPECT_EQ(55, w.getAllStock()[0].getQuantity());
    EXPECT_EQ(12, w.getAllStock()[1].getQuantity());
    EXPECT_EQ(550, w.getAllStock()[0].getWeight());
    EXPECT_EQ(120, w.getAllStock()[1].getWeight());

    std::vector<Paper> test = w.getAllStock();

    EXPECT_TRUE(test[0].getType() == w.getAllStock()[0].getType());
    EXPECT_TRUE(test[1].getType() == w.getAllStock()[1].getType());
    EXPECT_TRUE(test[0].getQuantity() == w.getAllStock()[0].getQuantity());
    EXPECT_TRUE(test[1].getQuantity() == w.getAllStock()[1].getQuantity());
    EXPECT_TRUE(test[0].getWeight() == w.getAllStock()[0].getWeight());
    EXPECT_TRUE(test[1].getWeight() == w.getAllStock()[1].getWeight());
    EXPECT_TRUE(test.size() == w.getAllStock().size());
}

TEST(WarehouseTest, addStockTest) {
    Paper p;
    p.addQuantity(20);
    Paper p2("thicc");
    p2.addQuantity(26);
    Warehouse w(20);
    EXPECT_EQ(0, w.getAllStock().size());

    w.addStock(p2.getType(), p2.getQuantity());
    EXPECT_EQ(1, w.getAllStock().size());
    EXPECT_EQ("thicc", w.getAllStock()[0].getType());
    EXPECT_EQ(26, w.getAllStock()[0].getQuantity());
    EXPECT_EQ(260, w.getAllStock()[0].getWeight());

    w.addStock(p2.getType(), 23);
    EXPECT_EQ(1, w.getAllStock().size());
    EXPECT_EQ(49, w.getAllStock()[0].getQuantity());
    EXPECT_EQ(490, w.getAllStock()[0].getWeight());

    w.addStock(p2.getType(), -10);
    EXPECT_EQ(49, w.getAllStock()[0].getQuantity());
    EXPECT_EQ(490, w.getAllStock()[0].getWeight());

    w.addStock(p.getType(), p.getQuantity());
    EXPECT_EQ(2, w.getAllStock().size());
    EXPECT_EQ("standard", w.getAllStock()[1].getType());
    EXPECT_EQ(20, w.getAllStock()[1].getQuantity());
    EXPECT_EQ(200, w.getAllStock()[1].getWeight());
}

TEST(WarehouseTest, removeStockTest) {
    Paper p;
    p.addQuantity(350);
    Paper p2("thin");
    p2.addQuantity(30);
    Warehouse w(10);

    w.addStock(p.getType(), p.getQuantity());
    w.addStock(p2.getType(), p2.getQuantity());

    w.removeStock(p.getType(), 50);
    EXPECT_EQ(2, w.getAllStock().size());
    EXPECT_EQ(300, w.getStock("standard").getQuantity());
    EXPECT_EQ(30, w.getStock("thin").getQuantity());

    w.removeStock(p.getType(), 300);
    EXPECT_EQ(1, w.getAllStock().size());
    EXPECT_EQ(30, w.getStock("thin").getQuantity());

    w.removeStock(p2.getType(), -10);
    EXPECT_EQ(1, w.getAllStock().size());
    EXPECT_EQ(30, w.getStock("thin").getQuantity());
}

TEST(WarehouseTest, getOrderTest) {
    Paper p;
    p.addQuantity(20);
    Order t(250);
    t.addToOrder(p.getType(), p.getQuantity());
    Warehouse w(10);
    w.addOrder(t);

    EXPECT_EQ(250, w.getOrder(250).getOrderNumber());
    EXPECT_EQ(200, w.getOrder(250).getTotalWeight());
    EXPECT_EQ("In Cart", w.getOrder(250).getStatus());
}

TEST(WarehouseTest, getAllOrdersTest) {
    Paper p;
    p.addQuantity(20);
    Paper p2("thicc");
    p2.addQuantity(25);
    Order t(250);
    Order t2(15);
    t.addToOrder(p.getType(), p.getQuantity());
    t.addToOrder(p2.getType(), p2.getQuantity());
    t2.addToOrder(p2.getType(), p2.getQuantity());
    t2.changeStatus("complete");
    Warehouse w(10);
    EXPECT_EQ(0, w.getAllOrders().size());

    w.addOrder(t);
    w.addOrder(t2);
    EXPECT_EQ(2, w.getAllOrders().size());
    EXPECT_EQ(250, w.getAllOrders()[0].getOrderNumber());
    EXPECT_EQ(15, w.getAllOrders()[1].getOrderNumber());
    EXPECT_EQ(450, w.getAllOrders()[0].getTotalWeight());
    EXPECT_EQ(250, w.getAllOrders()[1].getTotalWeight());
    EXPECT_EQ("In Cart", w.getAllOrders()[0].getStatus());
    EXPECT_EQ("Complete", w.getAllOrders()[1].getStatus());

    std::vector<Order> test = w.getAllOrders();

    EXPECT_TRUE(test[0].getOrderNumber() ==
                w.getAllOrders()[0].getOrderNumber());
    EXPECT_TRUE(test[1].getOrderNumber() ==
                w.getAllOrders()[1].getOrderNumber());
    EXPECT_TRUE(test[0].getTotalWeight() ==
                w.getAllOrders()[0].getTotalWeight());
    EXPECT_TRUE(test[1].getTotalWeight() ==
                w.getAllOrders()[1].getTotalWeight());
    EXPECT_TRUE(test[0].getStatus() == w.getAllOrders()[0].getStatus());
    EXPECT_TRUE(test[1].getStatus() == w.getAllOrders()[1].getStatus());
    EXPECT_TRUE(test.size() == w.getAllOrders().size());
}

TEST(WarehouseTest, addOrderTest) {
    Paper p;
    p.addQuantity(10);
    Paper p2("thicc");
    p2.addQuantity(35);
    Order t(50);
    Order t2(100);
    t.addToOrder(p.getType(), p.getQuantity());
    t2.addToOrder(p2.getType(), p2.getQuantity());
    t2.changeStatus("pending");
    Warehouse w(350);
    EXPECT_EQ(0, w.getAllOrders().size());

    w.addOrder(t);
    EXPECT_EQ(1, w.getAllOrders().size());
    EXPECT_EQ(50, w.getAllOrders()[0].getOrderNumber());
    EXPECT_EQ(100, w.getAllOrders()[0].getTotalWeight());
    EXPECT_EQ("In Cart", w.getAllOrders()[0].getStatus());

    w.addOrder(t);
    EXPECT_EQ(1, w.getAllOrders().size());
    EXPECT_EQ(50, w.getAllOrders()[0].getOrderNumber());
    EXPECT_EQ(100, w.getAllOrders()[0].getTotalWeight());
    EXPECT_EQ("In Cart", w.getAllOrders()[0].getStatus());

    w.addOrder(t2);
    EXPECT_EQ(2, w.getAllOrders().size());
    EXPECT_EQ(100, w.getAllOrders()[1].getOrderNumber());
    EXPECT_EQ(350, w.getAllOrders()[1].getTotalWeight());
    EXPECT_EQ("Pending", w.getAllOrders()[1].getStatus());
}

TEST(WarehouseTest, removeOrderTest) {
    Paper p;
    p.addQuantity(10);
    Paper p2("thicc");
    p2.addQuantity(35);
    Order t(50);
    Order t2(100);
    t.addToOrder(p.getType(), p.getQuantity());
    t2.addToOrder(p2.getType(), p2.getQuantity());
    t2.changeStatus("pending");
    Warehouse w(350);
    EXPECT_EQ(0, w.getAllOrders().size());

    w.addOrder(t);
    w.addOrder(t2);
    EXPECT_EQ(2, w.getAllOrders().size());

    w.removeOrder(50);
    EXPECT_EQ(1, w.getAllOrders().size());
    EXPECT_EQ(100, w.getAllOrders()[0].getOrderNumber());

    w.removeOrder(300);
    EXPECT_EQ(1, w.getAllOrders().size());
    EXPECT_EQ(100, w.getAllOrders()[0].getOrderNumber());

    w.removeOrder(100);
    EXPECT_EQ(0, w.getAllOrders().size());
}
//come back to these when order design pattern is implemented
/*
TEST(WarehouseTest, submitOrderTest)
{
    Paper p;
    p.addQuantity(25);
    Order t(30);
    Order t2(20);
    Order t3(25);
    t.addToOrder(p.getType(), p.getQuantity());
    t2.addToOrder(p.getType(), p.getQuantity());
    t3.addToOrder(p.getType(), p.getQuantity());
    t2.changeStatus("pending");
    t2.changeStatus("complete");
    Warehouse w(10);
    w.addOrder(t);
    w.addOrder(t2);
    w.addOrder(t3);

    //come back to this when order design pattern is implemented
    //std::ostringstream out;
    //out << w.submitOrder(30);
    //EXPECT_EQ("Order 30 has been successfully cancelled.", out.str());
}

TEST(WarehouseTest, cancelOrderTest)
{

}
*/

TEST(WarehouseTest, shipOrderTest) {
    Paper p;
    p.addQuantity(25);
    Order t(30);
    Order t2(20);
    Order t3(25);
    t.addToOrder(p.getType(), p.getQuantity());
    t2.addToOrder(p.getType(), p.getQuantity());
    t3.addToOrder(p.getType(), p.getQuantity());
    t2.changeStatus("pending");
    t3.changeStatus("complete");
    Warehouse w(10);
    w.addOrder(t);
    w.addOrder(t3);
    w.addOrder(t2);
    EXPECT_EQ(3, w.getAllOrders().size());
    EXPECT_EQ(30, w.getAllOrders()[0].getOrderNumber());
    EXPECT_EQ(25, w.getAllOrders()[1].getOrderNumber());
    EXPECT_EQ(20, w.getAllOrders()[2].getOrderNumber());

    w.shipOrder(30);
    EXPECT_EQ(3, w.getAllOrders().size());
    EXPECT_EQ(30, w.getAllOrders()[0].getOrderNumber());
    EXPECT_EQ(25, w.getAllOrders()[1].getOrderNumber());
    EXPECT_EQ(20, w.getAllOrders()[2].getOrderNumber());

    w.shipOrder(20);
    EXPECT_EQ(3, w.getAllOrders().size());
    EXPECT_EQ(30, w.getAllOrders()[0].getOrderNumber());
    EXPECT_EQ(25, w.getAllOrders()[1].getOrderNumber());
    EXPECT_EQ(20, w.getAllOrders()[2].getOrderNumber());

    w.shipOrder(25);
    EXPECT_EQ(2, w.getAllOrders().size());
    EXPECT_EQ(30, w.getAllOrders()[0].getOrderNumber());
    EXPECT_EQ(20, w.getAllOrders()[1].getOrderNumber());
}

TEST(WarehouseTest, changeOrderTest) {
    Paper p;
    p.addQuantity(25);
    Order t(30);
    t.addToOrder(p.getType(), p.getQuantity());
    Warehouse w(10);
    w.addOrder(t);
    EXPECT_EQ("In Cart", w.getOrder(30).getStatus());

    w.changeOrderStatus(20, "complete");
    EXPECT_EQ("In Cart", w.getOrder(30).getStatus());

    w.changeOrderStatus(30, "complete");
    EXPECT_EQ("Complete", w.getOrder(30).getStatus());
}

TEST(WarehouseTest, getOrderIndexTest) {
    Paper p;
    p.addQuantity(25);
    Order t(30);
    Order t2(20);
    Order t3(25);
    t.addToOrder(p.getType(), p.getQuantity());
    t2.addToOrder(p.getType(), p.getQuantity());
    t3.addToOrder(p.getType(), p.getQuantity());
    t2.changeStatus("pending");
    t3.changeStatus("complete");
    Warehouse w(10);
    w.addOrder(t);
    w.addOrder(t2);
    w.addOrder(t3);

    EXPECT_EQ(0, w.getOrderIndex(30));
    EXPECT_EQ(1, w.getOrderIndex(20));
    EXPECT_EQ(2, w.getOrderIndex(25));
    EXPECT_EQ(-1, w.getOrderIndex(50));
}
