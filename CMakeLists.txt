cmake_minimum_required(VERSION 3.17)
project(chessEngine2)

#Version of C++
set(CMAKE_CXX_STANDARD 17)

add_executable(
        ce2-t src/main/main.cpp
        )

#Including Google Tests
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#TESTING (Google Tests)
enable_testing()

#Test 1
add_executable(test1 tests/test1.cpp)
target_link_libraries(test1 gtest_main)

#Test 2
add_executable(test2 tests/test2.cpp)
target_link_libraries(test2 gtest_main)

include(GoogleTest)

gtest_discover_tests(test1)
gtest_discover_tests(test2)