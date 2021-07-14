#include <vector>
#include "gtest/gtest.h"
#include "Inventory.h"

TEST(InventoryTest, constructorTest) {
    Inventory i;
    EXPECT_EQ(0, i.getAllWarehouses().size());
}

TEST(InventoryTest, getWarehouseTest) {
    Inventory i;
    Warehouse w(10);
    Warehouse w2(25);
    Order t(50);
    w.addOrder(t);
    i.addWarehouse(w);
    i.addWarehouse(w2);
    EXPECT_EQ(10, i.getWarehouse(10).getWarehouseNumber());
    EXPECT_EQ(25, i.getWarehouse(25).getWarehouseNumber());
    EXPECT_EQ(1, i.getWarehouse(10).getAllOrders().size());
    EXPECT_EQ(0, i.getWarehouse(25).getAllOrders().size());
}

TEST(InventoryTest, getAllWarehousesTest) {
    Inventory i;
    Warehouse w(10);
    Warehouse w2(25);
    EXPECT_EQ(0, i.getAllWarehouses().size());

    i.addWarehouse(w);
    EXPECT_EQ(1, i.getAllWarehouses().size());
    EXPECT_EQ(10, i.getAllWarehouses()[0].getWarehouseNumber());

    i.addWarehouse(w2);
    EXPECT_EQ(2, i.getAllWarehouses().size());
    EXPECT_EQ(25, i.getAllWarehouses()[1].getWarehouseNumber());
}

TEST(InventoryTest, addWarehouseTest) {
    Inventory i;
    Warehouse w(10);
    Warehouse w2(25);
    Paper p;
    p.addQuantity(200);
    Order t(50);
    w.addOrder(t);
    w2.addStock(p.getType(), p.getQuantity());
    EXPECT_EQ(0, i.getAllWarehouses().size());

    i.addWarehouse(w);
    EXPECT_EQ(1, i.getAllWarehouses().size());
    EXPECT_EQ(10, i.getWarehouse(10).getWarehouseNumber());
    EXPECT_EQ(1, i.getWarehouse(10).getAllOrders().size());
    EXPECT_EQ(50, i.getWarehouse(10).getOrder(50).getOrderNumber());
    EXPECT_EQ(0, i.getWarehouse(10).getAllStock().size());

    i.addWarehouse(w2);
    EXPECT_EQ(2, i.getAllWarehouses().size());
    EXPECT_EQ(25, i.getWarehouse(25).getWarehouseNumber());
    EXPECT_EQ(0, i.getWarehouse(25).getAllOrders().size());
    EXPECT_EQ(1, i.getWarehouse(25).getAllStock().size());
    EXPECT_EQ(200, i.getWarehouse(25).getStock("standard").getQuantity());
}

TEST(InventoryTest, removeWarehouseTest) {
    Inventory i;
    Warehouse w(10);
    Warehouse w2(25);
    Warehouse w3(50);
    i.addWarehouse(w);
    i.addWarehouse(w2);
    i.addWarehouse(w3);
    EXPECT_EQ(3, i.getAllWarehouses().size());
    EXPECT_EQ(10, i.getAllWarehouses()[0].getWarehouseNumber());
    EXPECT_EQ(25, i.getAllWarehouses()[1].getWarehouseNumber());
    EXPECT_EQ(50, i.getAllWarehouses()[2].getWarehouseNumber());

    i.removeWarehouse(25);
    EXPECT_EQ(2, i.getAllWarehouses().size());
    EXPECT_EQ(10, i.getAllWarehouses()[0].getWarehouseNumber());
    EXPECT_EQ(50, i.getAllWarehouses()[1].getWarehouseNumber());

    i.removeWarehouse(80);
    EXPECT_EQ(2, i.getAllWarehouses().size());
    EXPECT_EQ(10, i.getAllWarehouses()[0].getWarehouseNumber());
    EXPECT_EQ(50, i.getAllWarehouses()[1].getWarehouseNumber());
}

TEST(InventoryTest, addWarehouseStockTest) {
    Inventory i;
    Warehouse w(10);
    Paper p;
    p.addQuantity(100);
    i.addWarehouse(w);
    EXPECT_EQ(0, i.getWarehouse(10).getAllStock().size());

    i.addWarehouseStock(10, p.getType(), p.getQuantity());
    EXPECT_EQ(1, i.getWarehouse(10).getAllStock().size());
    EXPECT_EQ("standard", i.getWarehouse(10).getAllStock()[0].getType());
    EXPECT_EQ(100, i.getWarehouse(10).getStock("standard").getQuantity());
    EXPECT_EQ(1000, i.getWarehouse(10).getStock("standard").getWeight());
    EXPECT_EQ(1, i.getAllWarehouseStock().size());
    EXPECT_EQ("standard", i.getAllWarehouseStock()[0].getType());
    EXPECT_EQ(100, i.getAllWarehouseStock()[0].getQuantity());
    EXPECT_EQ(1000, i.getAllWarehouseStock()[0].getWeight());
}

TEST(InventoryTest, removeWarehouseStockTest) {
    Inventory i;
    Warehouse w(10);
    Paper p;
    Paper p2("wide");
    p.addQuantity(100);
    p2.addQuantity(50);
    i.addWarehouse(w);
    i.addWarehouseStock(10, p.getType(), p.getQuantity());
    i.addWarehouseStock(10, p2.getType(), p2.getQuantity());
    EXPECT_EQ(2, i.getWarehouse(10).getAllStock().size());
    EXPECT_EQ(100, i.getWarehouse(10).getStock("standard").getQuantity());
    EXPECT_EQ(50, i.getWarehouse(10).getStock("wide").getQuantity());
    EXPECT_EQ(2, i.getAllWarehouseStock().size());
    EXPECT_EQ(100, i.getAllWarehouseStock()[0].getQuantity());
    EXPECT_EQ(50, i.getAllWarehouseStock()[1].getQuantity());

    i.removeWarehouseStock(10, "standard", 30);
    EXPECT_EQ(2, i.getWarehouse(10).getAllStock().size());
    EXPECT_EQ(70, i.getWarehouse(10).getStock("standard").getQuantity());
    EXPECT_EQ(50, i.getWarehouse(10).getStock("wide").getQuantity());
    EXPECT_EQ(2, i.getAllWarehouseStock().size());
    EXPECT_EQ(70, i.getAllWarehouseStock()[0].getQuantity());
    EXPECT_EQ(50, i.getAllWarehouseStock()[1].getQuantity());

    i.removeWarehouseStock(10, "thicc", 30);
    EXPECT_EQ(2, i.getWarehouse(10).getAllStock().size());
    EXPECT_EQ(70, i.getWarehouse(10).getStock("standard").getQuantity());
    EXPECT_EQ(50, i.getWarehouse(10).getStock("wide").getQuantity());
    EXPECT_EQ(2, i.getAllWarehouseStock().size());
    EXPECT_EQ(70, i.getAllWarehouseStock()[0].getQuantity());
    EXPECT_EQ(50, i.getAllWarehouseStock()[1].getQuantity());

    i.removeWarehouseStock(15, "standard", 30);
    EXPECT_EQ(2, i.getWarehouse(10).getAllStock().size());
    EXPECT_EQ(70, i.getWarehouse(10).getStock("standard").getQuantity());
    EXPECT_EQ(50, i.getWarehouse(10).getStock("wide").getQuantity());
    EXPECT_EQ(2, i.getAllWarehouseStock().size());
    EXPECT_EQ(70, i.getAllWarehouseStock()[0].getQuantity());
    EXPECT_EQ(50, i.getAllWarehouseStock()[1].getQuantity());

    i.removeWarehouseStock(10, "standard", 70);
    EXPECT_EQ(1, i.getWarehouse(10).getAllStock().size());
    EXPECT_EQ(50, i.getWarehouse(10).getStock("wide").getQuantity());
    EXPECT_EQ(1, i.getAllWarehouseStock().size());
    EXPECT_EQ(50, i.getAllWarehouseStock()[0].getQuantity());
}

TEST(InventoryTest, getWarehouseIndexTest) {
    Inventory i;
    Warehouse w(10);
    Warehouse w2(250);
    Warehouse w3(5);
    i.addWarehouse(w);
    i.addWarehouse(w2);
    i.addWarehouse(w3);
    EXPECT_EQ(0, i.getWarehouseIndex(10));
    EXPECT_EQ(1, i.getWarehouseIndex(250));
    EXPECT_EQ(2, i.getWarehouseIndex(5));
}

TEST(InventoryTest, getAllWarehouseStockTest) {
    Inventory i;
    Warehouse w(10);
    Paper p;
    Paper p2("wide");
    p.addQuantity(100);
    p2.addQuantity(50);
    i.addWarehouse(w);
    EXPECT_EQ(0, i.getAllWarehouseStock().size());

    i.addWarehouseStock(10, p.getType(), p.getQuantity());
    i.addWarehouseStock(10, p2.getType(), p2.getQuantity());
    EXPECT_EQ(2, i.getAllWarehouseStock().size());
    EXPECT_EQ("standard", i.getAllWarehouseStock()[0].getType());
    EXPECT_EQ("wide", i.getAllWarehouseStock()[1].getType());
    EXPECT_EQ(100, i.getAllWarehouseStock()[0].getQuantity());
    EXPECT_EQ(50, i.getAllWarehouseStock()[1].getQuantity());
    EXPECT_EQ(1000, i.getAllWarehouseStock()[0].getWeight());
    EXPECT_EQ(500, i.getAllWarehouseStock()[1].getWeight());

    std::vector<Paper> test = i.getAllWarehouseStock();
    EXPECT_EQ(i.getAllWarehouseStock().size(), test.size());
    EXPECT_EQ(i.getAllWarehouseStock()[0].getType(), test[0].getType());
    EXPECT_EQ(i.getAllWarehouseStock()[1].getType(), test[1].getType());
    EXPECT_EQ(i.getAllWarehouseStock()[0].getQuantity(), test[0].getQuantity());
    EXPECT_EQ(i.getAllWarehouseStock()[1].getQuantity(), test[1].getQuantity());
    EXPECT_EQ(i.getAllWarehouseStock()[0].getWeight(), test[0].getWeight());
    EXPECT_EQ(i.getAllWarehouseStock()[1].getWeight(), test[1].getWeight());
}
