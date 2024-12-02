cmake_minimum_required(VERSION 3.29)
project(ProjetJeuDelaVBio)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjetJeuDelaVBio main.cpp
        GameManager.cpp
        GameManager.h
        Grid.cpp
        Grid.h
        Cell.cpp
        Cell.h)
