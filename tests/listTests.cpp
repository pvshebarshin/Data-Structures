#include "../src/List.h"
#include <gtest/gtest.h>

TEST(List, simpleTest)
{
    auto* list = new List<int>();
    EXPECT_TRUE(list != nullptr);
    delete list;
}

TEST(List, constructorTest)
{
    auto* list = new List<int>(4);
    EXPECT_TRUE(list != nullptr);
    EXPECT_TRUE(list->front() == 4);
    EXPECT_TRUE(list->back() == 4);
    EXPECT_TRUE(list->get_size() == 1);
    EXPECT_FALSE(list->is_empty());
    delete list;
}

TEST(List, push_backTest)
{
    auto* list = new List<int>(6);
    list->push_back(1);
    list->push_back(44);
    list->push_back(13);
    list->push_back(666);
    EXPECT_TRUE(list->get_size() == 5);
    EXPECT_FALSE(list->is_empty());
    EXPECT_TRUE(list->front() == 6);
    EXPECT_TRUE(list->back() == 666);
    delete list;
}

TEST(List, indexTest)
{
    auto* list = new List<int>(6);
    list->push_back(1);
    list->push_back(44);
    list->push_back(13);
    list->push_back(666);
    EXPECT_TRUE((*list)[0] == 6);
    EXPECT_TRUE((*list)[1] == 1);
    EXPECT_TRUE((*list)[2] == 44);
    EXPECT_TRUE((*list)[3] == 13);
    EXPECT_TRUE((*list)[4] == 666);

    EXPECT_ANY_THROW((*list)[-11]);
    EXPECT_ANY_THROW((*list)[list->get_size()]);
    EXPECT_ANY_THROW((*list)[100000]);

    (*list)[0] = 1481;
    (*list)[list->get_size() - 1] = 10;
    EXPECT_EQ((*list)[0], 1481);
    EXPECT_EQ((*list)[list->get_size() - 1], 10);

    delete list;
}

TEST(List, copyTest)
{
    List<int> list(6);
    list.push_back(1);
    list.push_back(44);
    list.push_back(13);
    list.push_back(666);

    List<int> list1 = list;

    EXPECT_FALSE(&list == &list1);

    EXPECT_TRUE(list[0] == list1[0]);
    EXPECT_FALSE(&list[0] == &list1[0]);

    EXPECT_TRUE(list[1] == list1[1]);
    EXPECT_FALSE(&list[1] == &list1[1]);

    EXPECT_TRUE(list[2] == list1[2]);
    EXPECT_FALSE(&list[2] == &list1[2]);

    EXPECT_TRUE(list[3] == list1[3]);
    EXPECT_FALSE(&list[3] == &list1[3]);

    EXPECT_TRUE(list[4] == list1[4]);
    EXPECT_FALSE(&list[4] == &list1[4]);
}

TEST(List, equalTest)
{
    List<int> list1(6);
    list1.push_back(1);
    list1.push_back(44);
    list1.push_back(13);
    list1.push_back(666);

    List<int> list2(6);
    list2.push_back(1);
    list2.push_back(44);
    list2.push_back(13);
    list2.push_back(666);

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);
}

TEST(List, push_frontTest)
{
    List<int> list(6);
    list.push_back(1);
    list.push_back(44);
    list.push_back(13);
    list.push_back(666);
    EXPECT_EQ(list.front(), 6);
    EXPECT_EQ(list.front(), list[0]);

    list.push_front(69);
    EXPECT_EQ(list.front(), 69);
    EXPECT_EQ(list.front(), list[0]);
    EXPECT_TRUE(list.get_size() == 6);
}

TEST(List, pop_frontTest)
{
    List<int> list(6);
    list.push_back(1);
    list.push_back(44);
    EXPECT_TRUE(list.get_size() == 3);
    EXPECT_EQ(list.front(), 6);
    EXPECT_EQ(list.front(), list[0]);

    int x = list.pop_front();
    EXPECT_TRUE(list.get_size() == 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.front(), list[0]);
    EXPECT_EQ(x, 6);

    x = list.pop_front();
    EXPECT_TRUE(list.get_size() == 1);
    EXPECT_EQ(list.front(), 44);
    EXPECT_EQ(list.front(), list[0]);
    EXPECT_EQ(x, 1);

    x = list.pop_front();
    EXPECT_TRUE(list.get_size() == 0);
    EXPECT_ANY_THROW(list.front());
    EXPECT_ANY_THROW(list.back());
    EXPECT_ANY_THROW(list[0]);
    EXPECT_EQ(x, 44);
    EXPECT_ANY_THROW(list.pop_front());
}

TEST(List, pop_backTest)
{
    List<int> list(6);
    list.push_back(1);
    list.push_back(44);
    EXPECT_TRUE(list.get_size() == 3);
    EXPECT_EQ(list.back(), 44);
    EXPECT_EQ(list.back(), list[list.get_size() - 1]);

    int x = list.pop_back();
    EXPECT_TRUE(list.get_size() == 2);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.back(), list[list.get_size() - 1]);
    EXPECT_EQ(44, x);

    x = list.pop_back();
    EXPECT_TRUE(list.get_size() == 1);
    EXPECT_EQ(list.back(), 6);
    EXPECT_EQ(list.back(), list[list.get_size() - 1]);
    EXPECT_EQ(1, x);

    x = list.pop_back();
    EXPECT_TRUE(list.get_size() == 0);
    EXPECT_EQ(6, x);
    EXPECT_ANY_THROW(list.back());
    EXPECT_ANY_THROW(list[0]);
    EXPECT_ANY_THROW(list[44]);
    EXPECT_ANY_THROW(list[-44]);
}

TEST(List, clearTest)
{
    auto *list = new List<int>();
    list->push_back(1);
    list->push_back(44);
    EXPECT_EQ(2, list->get_size());

    list->clear();
    EXPECT_TRUE(list->is_empty());
    EXPECT_EQ(0, list->get_size());

    list->push_back(1);
    list->push_back(44);
    EXPECT_EQ(2, list->get_size());
    delete list;
}

TEST(List, addListTest)
{
    List<int> list(6);
    list.push_back(1);
    list.push_back(44);
    EXPECT_EQ(list.get_size(), 3);

    List<int> new_list(2);
    new_list.push_back(4);

    list.add_list(new_list);
    EXPECT_EQ(5, list.get_size());
    EXPECT_EQ(4, list.back());
    EXPECT_EQ(4, list[list.get_size() - 1]);
    EXPECT_EQ(6, list.front());
    EXPECT_EQ(6, list[0]);

    List<int> new_list2(666);
    new_list2.push_front(333);

    list.add_list(new_list2);
    EXPECT_EQ(666, list.back());

    EXPECT_EQ(2, new_list.get_size());
}