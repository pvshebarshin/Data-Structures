include_directories(../src)

include_directories(.)

add_executable(tests
        # test sources
        listTests.cpp
        stackTests.cpp
        BSTTests.cpp
        # task sources
        ../src/List.h
        ../src/Stack.h
        # gtest sources
        gtest/gtest-all.cc
        gtest/gtest_main.cc)

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()