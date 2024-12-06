cmake_minimum_required(VERSION 3.25)
project(JeuDeLaVieBase)

set(CMAKE_CXX_STANDARD 20)

# Define the path to SFML
set(SFML_DIR "/usr/lib/x86_64-linux-gnu/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# List of source files for the main executable
set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Code/CPP/main.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/Cell.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/Grid.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/game.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/FileHandler.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/DisplayManager.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/ConsoleDisplay.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/GraphicalDisplay.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/ThreadPool.cpp
        ${CMAKE_SOURCE_DIR}/Code/CPP/RleReader.cpp
)

# Check if all source files exist
foreach(SOURCE_FILE ${SOURCE_FILES})
    if(NOT EXISTS ${SOURCE_FILE})
        message(FATAL_ERROR "Cannot find source file: ${SOURCE_FILE}")
    endif()
endforeach()

# Add the main executable
add_executable(JeuDeLaVieBase ${SOURCE_FILES})

# Add the headers directory to the include paths
target_include_directories(JeuDeLaVieBase PRIVATE
        ${CMAKE_SOURCE_DIR}/Code/Headers
        ${CMAKE_SOURCE_DIR}/Code
)

# Link SFML to the main executable
target_link_libraries(JeuDeLaVieBase sfml-system sfml-window sfml-graphics)

# Add Google Test
add_subdirectory(libs/googletest)

# Create a shared library for the project files
add_library(JeuDeLaVieBaseLib ${SOURCE_FILES})

# Add the headers directory for the library
target_include_directories(JeuDeLaVieBaseLib PRIVATE
        ${CMAKE_SOURCE_DIR}/Code/Headers
)

# Link SFML to the library
target_link_libraries(JeuDeLaVieBaseLib sfml-system sfml-window sfml-graphics)

# Create an executable for the tests
add_executable(GameOfLifeTests
        ${CMAKE_SOURCE_DIR}/tests/test_FileHandler.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_Cell.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_Game.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_Grid.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_GraphicalDisplay.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_ThreadPool.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_ConsoleDisplay.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_RleReader.cpp
        ${CMAKE_SOURCE_DIR}/tests/test_DisplayManager.cpp
)

# Add the include directories to the tests
target_include_directories(GameOfLifeTests PRIVATE
        ${CMAKE_SOURCE_DIR}/Code/Headers
        ${CMAKE_SOURCE_DIR}/Code
        ${CMAKE_SOURCE_DIR}/tests
        ${CMAKE_SOURCE_DIR}/libs/googletest/googletest/include
)

# Define the UNIT_TEST macro for the tests
target_compile_definitions(GameOfLifeTests PRIVATE UNIT_TEST)

# Link Google Test to the tests
target_link_libraries(GameOfLifeTests gtest gtest_main)

# Link the project library to the tests
target_link_libraries(GameOfLifeTests JeuDeLaVieBaseLib)
