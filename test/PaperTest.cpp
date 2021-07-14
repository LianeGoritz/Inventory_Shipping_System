#include "gtest/gtest.h"
#include "Paper.h"

TEST(PaperTest, constructorTest) {
    Paper p;
    EXPECT_EQ("standard", p.getType());
    EXPECT_EQ(0, p.getQuantity());
    EXPECT_EQ(0, p.getWeight());
}

TEST(PaperTest, overLoadedConstructorTest) {
    Paper p("wide");
    EXPECT_EQ("wide", p.getType());
    EXPECT_EQ(0, p.getQuantity());
    EXPECT_EQ(0, p.getWeight());

    Paper p2("thin");
    EXPECT_EQ("thin", p2.getType());
    EXPECT_EQ(0, p2.getQuantity());
    EXPECT_EQ(0, p2.getWeight());
}

TEST(PaperTest, getTypeTest) {
    Paper p("thicc");
    EXPECT_EQ("thicc", p.getType());

    Paper p2("sparkly");
    EXPECT_EQ("sparkly", p2.getType());
}

TEST(PaperTest, setTypeTest) {
    Paper p;
    EXPECT_EQ("standard", p.getType());
    p.setType("thicc");
    EXPECT_EQ("thicc", p.getType());
}

TEST(PaperTest, getQuantityTest) {
    Paper p;
    p.addQuantity(100);
    EXPECT_EQ(100, p.getQuantity());
    p.addQuantity(10);
    EXPECT_EQ(110, p.getQuantity());
}

TEST(PaperTest, addQuantityTest) {
    Paper p;
    p.addQuantity(10);
    EXPECT_EQ(10, p.getQuantity());
    p.addQuantity(20);
    EXPECT_EQ(30, p.getQuantity());
    p.addQuantity(-10);
    EXPECT_EQ(30, p.getQuantity());
}

TEST(PaperTest, removeQuantityTest) {
    Paper p;
    p.addQuantity(50);
    EXPECT_EQ(50, p.getQuantity());
    p.removeQuantity(10);
    EXPECT_EQ(40, p.getQuantity());
    p.removeQuantity(-10);
    EXPECT_EQ(40, p.getQuantity());
}

TEST(PaperTest, getWeightTest) {
    Paper p;
    EXPECT_EQ(0, p.getWeight());
    p.addQuantity(10);
    EXPECT_EQ(100, p.getWeight());
    p.addQuantity(20);
    EXPECT_EQ(300, p.getWeight());
}
