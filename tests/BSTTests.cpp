#include "../src/AVL_BST.h"
#include <gtest/gtest.h>

TEST(AVL_BST, simpleTest)
{
    auto* tree = new AVL_BST<int>();
    EXPECT_TRUE(tree != nullptr);
    delete tree;
}

TEST(AVL_BST, contains_and_constructorTest)
{
    auto* tree = new AVL_BST<float>(3.14f);
    EXPECT_FALSE(tree == nullptr);
    EXPECT_TRUE(tree->contains(3.14f));
    delete tree;
}

TEST(AVL_BST, contains_and_addTest)
{
    auto* tree = new AVL_BST<double>(3.14);
    EXPECT_TRUE(tree->contains(3.14));
    tree->add(1);
    tree->add(55);
    tree->add(-55);
    tree->add(2.72);
    tree->add(-0.9999);
    tree->add(0.0001);
    tree->add(999);

    EXPECT_TRUE(tree->contains(2.72));
    EXPECT_TRUE(tree->contains(1));
    EXPECT_TRUE(tree->contains(-0.9999));
    EXPECT_TRUE(tree->contains(999));
    EXPECT_TRUE(tree->contains(0.0001));
    EXPECT_TRUE(tree->contains(55));
    EXPECT_TRUE(tree->contains(-55));

    EXPECT_FALSE(tree->contains(15678));
    EXPECT_FALSE(tree->contains(-2));
    EXPECT_FALSE(tree->contains(0.45678));

    delete tree;
}

TEST(AVL_BST, isEmptyTest)
{
    auto* tree = new AVL_BST<long>();
    EXPECT_TRUE(tree->is_empty());

    tree->add(1234567890);
    EXPECT_FALSE(tree->is_empty());

    tree = new AVL_BST<long>();
    EXPECT_TRUE(tree->is_empty());

    tree = new AVL_BST<long>(98765432);
    EXPECT_FALSE(tree->is_empty());
}

TEST(AVL_BST, removeTest)
{
    auto* tree = new AVL_BST<double>(3.14);
    EXPECT_TRUE(tree->contains(3.14));
    tree->add(1);
    tree->add(55);
    tree->add(-55);
    tree->add(2.72);
    tree->add(-0.9999);
    tree->add(0.0001);
    tree->add(999);

    EXPECT_TRUE(tree->contains(2.72));
    EXPECT_TRUE(tree->contains(1));
    EXPECT_TRUE(tree->contains(999));

    tree->remove(1);
    tree->remove(999);


    EXPECT_FALSE(tree->contains(1));
    EXPECT_FALSE(tree->contains(999));

    delete tree;
}