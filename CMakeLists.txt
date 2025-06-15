cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SchiffeVersenken)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
)

set(common_sources
        src/Board.cpp
        src/Board.hpp
        src/Player.cpp
        src/Player.hpp
        src/Random_player.cpp
        src/Random_player.hpp
        src/Human_player.cpp
        src/Human_player.hpp
        src/Cheating_player.cpp
        src/Cheating_player.hpp
        src/GameController.cpp
        src/GameController.hpp
)

# Executable
add_executable(tasks
        ${common_sources}
        src/SchiffeVersenken.cpp
)

add_executable(tournament
        ${common_sources}
        src/Tournament.cpp
)

# Fetch Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.3.2
)
FetchContent_MakeAvailable(Catch2)

# Build Tests
enable_testing()
add_executable(tests
        ${common_sources}
        src/board.test.cpp
        src/random_player.test.cpp
        src/human_player.test.cpp
        src/cheating_player.test.cpp
        src/util.test.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE src)

# Register Tests
add_test(tests ./tests)
set_property(TEST tests PROPERTY ENVIRONMENT "CTEST_OUTPUT_ON_FAILURE=1")
