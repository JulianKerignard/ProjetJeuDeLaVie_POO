#include "ConsoleDisplay.h"
#include <iostream>
#include <thread>
#include <chrono>

void ConsoleDisplay::initialize() {
    std::cout << "Initialisation de l'affichage console" << std::endl;
}

void ConsoleDisplay::update(const Grid& grid) {
    system("cls");  // Pour Windows (utilisez "clear" pour Linux)
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            if (grid.getCellAt(x, y).getCurrentState() == CellState::ALIVE) {
                std::cout << "■ ";
            } else {
                std::cout << "□ ";
            }
        }
        std::cout << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void ConsoleDisplay::close() {
    std::cout << "Fermeture de l'affichage" << std::endl;
}