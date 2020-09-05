#include "../src/Stack.h"
#include <gtest/gtest.h>

TEST(Stack, simpleTest)
{
    Stack<int>* stack = new Stack<int>(10);
    EXPECT_TRUE(stack != nullptr);
    delete stack;
}

TEST(Stack, EmtpyFullTest)
{
    Stack<float> stack(10);
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
}

TEST(Stack, PushPopTest)
{
    Stack<int> st;
    EXPECT_TRUE(st.isEmpty());

    int v1 = 402;
    int v2 = 103;
    int v3 = 6067;

    st.push(v1);
    EXPECT_FALSE(st.isEmpty());
    st.push(v2);
    st.push(v3);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_EQ(st.pop(), v3);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_EQ(st.pop(), v2);
    EXPECT_EQ(st.pop(), v1);
    EXPECT_TRUE(st.isEmpty());
}

TEST(Stack, OverFlowTest)
{
    Stack<long long> st(1);

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    st.push(421);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_TRUE(st.isFull());

    EXPECT_THROW(st.push(113), std::logic_error);
}

TEST(Stack, PopNothingTest)
{
    Stack<double> st;

    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());
    EXPECT_THROW(st.pop(), std::logic_error);
}

TEST(IntStack, TopTest)
{
    Stack<int> st;
    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    int v1 = 412;
    st.push(v1);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_EQ(st.top(), v1);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_EQ(st.pop(), v1);
    EXPECT_TRUE(st.isEmpty());
}

TEST(IntStack, ClearTest)
{
    Stack<int> st(5);
    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    st.push(2);
    EXPECT_FALSE(st.isEmpty());
    EXPECT_FALSE(st.isFull());

    st.push(113);
    EXPECT_FALSE(st.isEmpty());

    st.clear();
    EXPECT_TRUE(st.isEmpty());
    EXPECT_FALSE(st.isFull());
}