cmake_minimum_required(VERSION 3.25)
project(ProjetCaca)

set(CMAKE_CXX_STANDARD 20)

# Définir le chemin vers SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Ajouter l'exécutable
add_executable(ProjetCaca
        main.cpp
        Cell.cpp
        Grid.cpp
        Game.cpp
        FileHandler.cpp
        DisplayManager.cpp
        ConsoleDisplay.cpp
        GraphicalDisplay.cpp
        ThreadPool.cpp
        ThreadPool.h
        RleReader.cpp
        RleReader.h
)

# Lier SFML
target_link_libraries(ProjetCaca sfml-system sfml-window sfml-graphics)