cmake_minimum_required(VERSION 3.25)
project(JeuDeLaVieBase)

set(CMAKE_CXX_STANDARD 20)

# Définir le chemin vers SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Ajouter l'exécutable principal
add_executable(JeuDeLaVieBase
        Code/CPP/main.cpp
        Code/CPP/Cell.cpp
        Code/CPP/Grid.cpp
        Code/CPP/Game.cpp
        Code/CPP/FileHandler.cpp
        Code/CPP/DisplayManager.cpp
        Code/CPP/ConsoleDisplay.cpp
        Code/CPP/GraphicalDisplay.cpp
        Code/CPP/ThreadPool.cpp
        Code/CPP/RleReader.cpp
)

# Ajouter le dossier des headers aux chemins d'inclusion
target_include_directories(JeuDeLaVieBase PRIVATE
        ${CMAKE_SOURCE_DIR}/Code/Headers
        ${CMAKE_SOURCE_DIR}/Code
)

# Lier SFML à l'exécutable principal
target_link_libraries(JeuDeLaVieBase sfml-system sfml-window sfml-graphics)

# Ajouter Google Test
add_subdirectory(libs/googletest)

# Créer une bibliothèque partagée pour les fichiers du projet
add_library(JeuDeLaVieBaseLib
        Code/CPP/Cell.cpp
        Code/CPP/Grid.cpp
        Code/CPP/Game.cpp
        Code/CPP/FileHandler.cpp
        Code/CPP/DisplayManager.cpp
        Code/CPP/ConsoleDisplay.cpp
        Code/CPP/GraphicalDisplay.cpp
        Code/CPP/ThreadPool.cpp
        Code/CPP/RleReader.cpp
)

# Ajouter le dossier des headers pour la bibliothèque
target_include_directories(JeuDeLaVieBaseLib PRIVATE
        ${CMAKE_SOURCE_DIR}/Code/Headers
)

# Lier SFML à la bibliothèque
target_link_libraries(JeuDeLaVieBaseLib sfml-system sfml-window sfml-graphics)

# Créer un exécutable pour les tests
add_executable(GameOfLifeTests
        tests/test_FileHandler.cpp
        tests/test_Cell.cpp
        tests/test_Game.cpp
        tests/test_Grid.cpp
        tests/test_GraphicalDisplay.cpp
        tests/test_ThreadPool.cpp
        tests/test_ConsoleDisplay.cpp
        tests/test_RleReader.cpp
        tests/test_DisplayManager.cpp
)

# Ajouter les dossiers d'inclusion aux tests
target_include_directories(GameOfLifeTests PRIVATE
        ${CMAKE_SOURCE_DIR}/Code/Headers
        ${CMAKE_SOURCE_DIR}/Code
        ${CMAKE_SOURCE_DIR}/tests
        ${CMAKE_SOURCE_DIR}/libs/googletest/googletest/include
)

# Définir le macro UNIT_TEST pour les tests
target_compile_definitions(GameOfLifeTests PRIVATE UNIT_TEST)

# Lier Google Test aux tests
target_link_libraries(GameOfLifeTests gtest gtest_main)

# Lier la bibliothèque du projet aux tests
target_link_libraries(GameOfLifeTests JeuDeLaVieBaseLib)