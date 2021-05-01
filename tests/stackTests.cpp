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
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(Stack, PushPopTest)
{
    Stack<int> st;
    EXPECT_TRUE(st.is_empty());

    int v1 = 402;
    int v2 = 103;
    int v3 = 6067;

    st.push(v1);
    EXPECT_FALSE(st.is_empty());
    st.push(v2);
    st.push(v3);
    EXPECT_FALSE(st.is_empty());
    EXPECT_EQ(st.pop(), v3);
    EXPECT_FALSE(st.is_empty());
    EXPECT_EQ(st.pop(), v2);
    EXPECT_EQ(st.pop(), v1);
    EXPECT_TRUE(st.is_empty());
}

TEST(Stack, OverFlowTest)
{
    Stack<long long> st(1);

    EXPECT_TRUE(st.is_empty());
    EXPECT_FALSE(st.is_full());

    st.push(421);
    EXPECT_FALSE(st.is_empty());
    EXPECT_TRUE(st.is_full());

    EXPECT_THROW(st.push(113), std::logic_error);
}

TEST(Stack, PopNothingTest)
{
    Stack<double> st;

    EXPECT_TRUE(st.is_empty());
    EXPECT_FALSE(st.is_full());
    EXPECT_THROW(st.pop(), std::logic_error);
}

TEST(Stack, TopTest)
{
    Stack<int> st;
    EXPECT_TRUE(st.is_empty());
    EXPECT_FALSE(st.is_full());

    int v1 = 412;
    st.push(v1);
    EXPECT_FALSE(st.is_empty());
    EXPECT_EQ(st.top(), v1);
    EXPECT_FALSE(st.is_empty());
    EXPECT_EQ(st.pop(), v1);
    EXPECT_TRUE(st.is_empty());
}

TEST(Stack, ClearTest)
{
    Stack<int> st(5);
    EXPECT_TRUE(st.is_empty());
    EXPECT_FALSE(st.is_full());

    st.push(2);
    EXPECT_FALSE(st.is_empty());
    EXPECT_FALSE(st.is_full());

    st.push(113);
    EXPECT_FALSE(st.is_empty());

    st.clear();
    EXPECT_TRUE(st.is_empty());
    EXPECT_FALSE(st.is_full());
}

TEST(Stack, SizeTest)
{
    Stack<int> st(5);
    st.push(5);
    st.push(2);
    st.push(32);
    EXPECT_EQ(st.size(), 3);
}

TEST(Stack, CompoundTest)
{
    Stack<int> st1(10);
    Stack<int> st2(4);
    st1.push(1);
    st1.push(2);
    st1.push(3);

    st2.push(4);
    st2.push(5);
    st2.push(6);
    st1.compound(st2);
    EXPECT_EQ(st1.size(), 6);
}