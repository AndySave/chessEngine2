cmake_minimum_required(VERSION 3.17)
project(chessEngine2)

#Version of C++
set(CMAKE_CXX_STANDARD 17)

add_executable(
        chessEngine2 src/main/main.cpp

        src/definitions/std_typedef.h
        src/definitions/board.cpp
        src/definitions/board.h
        src/definitions/nonSlidersAttacks.cpp
        src/definitions/nonSlidersAttacks.h
        src/definitions/slidersAttacks.cpp
        src/definitions/slidersAttacks.h
        src/definitions/zobristKey.cpp
        src/definitions/zobristKey.h
        src/definitions/moveGeneration.cpp
        src/definitions/moveGeneration.h
        src/definitions/move.cpp
        src/definitions/move.h

        src/evaluation/mainEvaluation.cpp
        src/evaluation/mainEvaluation.h
        src/evaluation/pieceTables.cpp
        src/evaluation/pieceTables.h
        src/evaluation/mobility.cpp
        src/evaluation/mobility.h

        src/search/main_search.cpp
        src/search/main_search.h
        src/search/move_ordering.cpp
        src/search/move_ordering.h
        src/search/hash_table.cpp
        src/search/hash_table.h

        src/ui/terminal_ui.cpp
        src/ui/terminal_ui.h
        src/ui/uci.cpp
        src/ui/uci.h

        src/utils/bitops.cpp
        src/utils/bitops.h
        src/utils/fen.cpp
        src/utils/fen.h
        src/utils/helpers.cpp
        src/utils/helpers.h
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
add_executable(
        test1 tests/test1.cpp

        src/definitions/move.cpp
        src/definitions/move.h
        src/definitions/std_typedef.h
        src/utils/helpers.cpp
        src/utils/helpers.h
        )
target_link_libraries(test1 gtest_main)

#Test 2
add_executable(
        test2 tests/test2.cpp

        src/definitions/slidersAttacks.cpp
        src/definitions/slidersAttacks.h
        src/definitions/std_typedef.h
        src/utils/bitops.cpp
        src/utils/bitops.h

        )
target_link_libraries(test2 gtest_main)

#Test: tests/definitions/perft.cpp
add_executable(
        test_defintions_perft tests/definitions/perft.cpp

        src/definitions/std_typedef.h
        src/definitions/board.cpp
        src/definitions/board.h
        src/definitions/nonSlidersAttacks.cpp
        src/definitions/nonSlidersAttacks.h
        src/definitions/slidersAttacks.cpp
        src/definitions/slidersAttacks.h
        src/definitions/zobristKey.cpp
        src/definitions/zobristKey.h
        src/definitions/moveGeneration.cpp
        src/definitions/moveGeneration.h
        src/definitions/move.cpp
        src/definitions/move.h

        src/evaluation/mainEvaluation.cpp
        src/evaluation/mainEvaluation.h
        src/evaluation/pieceTables.cpp
        src/evaluation/pieceTables.h

        src/search/main_search.cpp
        src/search/main_search.h
        src/search/move_ordering.cpp
        src/search/move_ordering.h
        src/search/hash_table.cpp
        src/search/hash_table.h

        src/ui/terminal_ui.cpp
        src/ui/terminal_ui.h
        src/ui/uci.cpp
        src/ui/uci.h

        src/utils/bitops.cpp
        src/utils/bitops.h
        src/utils/fen.cpp
        src/utils/fen.h
        src/utils/helpers.cpp
        src/utils/helpers.h
)

target_link_libraries(test_defintions_perft gtest_main)

include(GoogleTest)

gtest_discover_tests(test1)
gtest_discover_tests(test2)
gtest_discover_tests(test_defintions_perft)