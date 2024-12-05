cmake_minimum_required(VERSION 3.25)
project(ProjetCaca)

set(CMAKE_CXX_STANDARD 20)

# Définir le chemin vers SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Ajouter l'exécutable
add_executable(ProjetCaca
        Code/CPP/main.cpp
        Code/CPP/Cell.cpp
        Code/CPP/Grid.cpp
        Code/CPP/game.cpp
        Code/CPP/FileHandler.cpp
        Code/CPP/DisplayManager.cpp
        Code/CPP/ConsoleDisplay.cpp
        Code/CPP/GraphicalDisplay.cpp
        Code/CPP/ThreadPool.cpp
        Code/CPP/RleReader.cpp
        # Ajout de tous les fichiers headers
        Code/Headers/Cell.h
        Code/Headers/Grid.h
        Code/Headers/Game.h
        Code/Headers/FileHandler.h
        Code/Headers/DisplayManager.h
        Code/Headers/ConsoleDisplay.h
        Code/Headers/GraphicalDisplay.h
        Code/Headers/ThreadPool.h
        Code/Headers/RleReader.h
)

# Ajouter le dossier des headers aux chemins d'inclusion
target_include_directories(ProjetCaca PRIVATE
        ${CMAKE_SOURCE_DIR}/Code/Headers
        ${CMAKE_SOURCE_DIR}/Code
)

# Lier SFML
target_link_libraries(ProjetCaca sfml-system sfml-window sfml-graphics)