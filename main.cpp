#include "tests/stackTests.cpp"
#include "tests/listTests.cpp"
#include "tests/BSTTests.cpp"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}