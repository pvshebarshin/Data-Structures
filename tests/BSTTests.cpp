#include "../src/AVL_BST.h"
#include <gtest/gtest.h>

TEST(BST, simpleTest)
{
    AVL_BST<int>* tree = new AVL_BST<int>();
    EXPECT_TRUE(tree != nullptr);
    delete tree;
}

TEST(BST, contains_and_constructorTest)
{
    AVL_BST<float>* tree = new AVL_BST<float>(3.14f);
    EXPECT_FALSE(tree == nullptr);
    EXPECT_TRUE(tree->contains(3.14f));
    delete tree;
}

TEST(AVL_BST, contains_and_addTest)
{
    AVL_BST<double>* tree = new AVL_BST<double>(3.14);
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

    tree->display();
    delete tree;
}

TEST(AVL_BST, isEmptyTest)
{
    AVL_BST<long>* tree = new AVL_BST<long>();
    EXPECT_TRUE(tree->isEmpty());

    tree->add(1234567890);
    EXPECT_FALSE(tree->isEmpty());

    tree = new AVL_BST<long>();
    EXPECT_TRUE(tree->isEmpty());

    tree = new AVL_BST<long>(98765432);
    EXPECT_FALSE(tree->isEmpty());
}