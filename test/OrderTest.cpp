#include "gtest/gtest.h"
#include "Order.h"

TEST(OrderTest, constructorTest) {
    Order t(10);
    EXPECT_EQ(10, t.getOrderNumber());
    EXPECT_EQ("In Cart", t.getStatus());
    EXPECT_EQ(0, t.getTotalWeight());
}

TEST(OrderTest, getOrderNumberTest) {
    Order t(5);
    EXPECT_EQ(5, t.getOrderNumber());

    Order t2(200);
    EXPECT_EQ(200, t2.getOrderNumber());
}

TEST(OrderTest, addToOrderTest) {
    Paper p;
    p.addQuantity(10);
    Order t(5);
    t.addToOrder(p.getType(), p.getQuantity());
    EXPECT_EQ("standard", t.getProducts()[0].getType());
    EXPECT_EQ(10, t.getProducts()[0].getQuantity());
    EXPECT_EQ(100, t.getTotalWeight());
    EXPECT_NE(0, t.getProducts().size());

    int testSize = t.getProducts().size();

    t.addToOrder(p.getType(), 5);
    EXPECT_EQ(15, t.getProducts()[0].getQuantity());
    EXPECT_TRUE(t.getProducts().size() == testSize);
}

TEST(OrderTest, removeFromOrderTest) {
    Paper p;
    p.addQuantity(10);
    Order t(5);
    t.addToOrder(p.getType(), p.getQuantity());
    EXPECT_NE(0, t.getProducts().size());

    t.removeFromOrder(p.getType(), 5);
    EXPECT_EQ(5, t.getProducts()[0].getQuantity());

    t.removeFromOrder(p.getType(), 6);
    EXPECT_EQ(0, t.getProducts().size());
}

TEST(OrderTest, getStatusTest) {
    Order t(20);
    EXPECT_EQ("In Cart", t.getStatus());

    t.changeStatus("complete");
    EXPECT_EQ("Complete", t.getStatus());
}

TEST(OrderTest, changeStatusTest) {
    Order t(20);
    EXPECT_EQ("In Cart", t.getStatus());

    t.changeStatus("complete");
    EXPECT_EQ("Complete", t.getStatus());

    t.changeStatus("winning");
    EXPECT_EQ("Complete", t.getStatus());
}

TEST(OrderTest, getProductsTest) {
    Paper p;
    p.addQuantity(10);
    Order t(5);
    t.addToOrder(p.getType(), p.getQuantity());
    EXPECT_EQ("standard", t.getProducts()[0].getType());
    EXPECT_EQ(10, t.getProducts()[0].getQuantity());
}

TEST(OrderTest, getTotalWeightTest) {
    Paper p;
    p.addQuantity(10);
    Order t(5);
    EXPECT_EQ(0, t.getTotalWeight());

    t.addToOrder(p.getType(), p.getQuantity());
    EXPECT_EQ(100, t.getTotalWeight());

    t.addToOrder(p.getType(), 5);
    EXPECT_EQ(150, t.getTotalWeight());
}
