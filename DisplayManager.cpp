#include "DisplayManager.h"
#include <iostream>
#include <thread>
#include <chrono>

class ConsoleDisplay : public DisplayManager {
public:
    void initialize() override {
        std::cout << "Initialisation de l'affichage console" << std::endl;
    }

    void update(const Grid& grid) override {
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

    void close() override {
        std::cout << "Fermeture de l'affichage" << std::endl;
    }
};