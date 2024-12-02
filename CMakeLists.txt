cmake_minimum_required(VERSION 3.25)
project(JeuDeLaVieBase)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(JeuDeLaVieBase main.cpp)

target_link_libraries(JeuDeLaVieBase sfml-graphics)

add_executable(JeuDeLaVieBase main.cpp
        Grid.cpp
        Grid.h
        Cell.cpp
        Cell.h
        GameManager.cpp
        GameManager.h
        InterfaceGraphique.cpp
        InterfaceGraphique.h)
