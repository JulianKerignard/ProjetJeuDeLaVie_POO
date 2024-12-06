#include "DisplayManager.h"
#include <iostream>
#include <thread>
#include <chrono>

class test_ConsoleDisplay : public DisplayManager {
public:
    void initialize() override {
        std::cout << "Initialisation de l'affichage console" << std::endl;
    }

    void update(const Grid& grid) override {
        system("cls");  // Effacer la console
        for (int y = 0; y < grid.getHeight(); y++) {
            for (int x = 0; x < grid.getWidth(); x++) {
                if (grid.getCellAt(x, y).getCurrentState() == CellState::ALIVE) {
                    std::cout << "1";
                } else {
                    std::cout << "2 ";
                }
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void close() override {
        std::cout << "Fermeture de l'affichage" << std::endl;
    }
};