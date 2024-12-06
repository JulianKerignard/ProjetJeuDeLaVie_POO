#include "ConsoleDisplay.h"
#include <iostream>
#include <thread>
#include <chrono>

ConsoleDisplay::ConsoleDisplay() : iterationCounter(0) {
    outputFile.open("simulation_log.txt");
}

void ConsoleDisplay::initialize() {
    std::cout << "Initialisation de l'affichage console" << std::endl;
    outputFile << "Simulation du Jeu de la Vie" << std::endl;
    outputFile << "==========================" << std::endl << std::endl;
}

void ConsoleDisplay::update(const Grid& grid) {
    system("cls");  // Pour Windows (utilisez "clear" pour Linux)

    // Affichage console
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            const Cell& cell = grid.getCellAt(x, y);
            if (cell.isObstacleCell()) {
                std::cout << "2 ";
            } else if (cell.getCurrentState() == CellState::ALIVE) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }

    // Écriture dans le fichier
    outputFile << "Itération " << iterationCounter << std::endl;
    outputFile << "-------------" << std::endl;

    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            const Cell& cell = grid.getCellAt(x, y);
            if (cell.isObstacleCell()) {
                outputFile << "2 ";  // 2 pour les obstacles
            } else if (cell.getCurrentState() == CellState::ALIVE) {
                outputFile << "1 ";
            } else {
                outputFile << "0 ";
            }
        }
        outputFile << std::endl;
    }
    outputFile << std::endl;

    std::cout << "\nItération " << iterationCounter << " sauvegardée" << std::endl;

    iterationCounter++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void ConsoleDisplay::close() {
    std::cout << "Fermeture de l'affichage" << std::endl;
    std::cout << "Les " << iterationCounter << " itérations ont été sauvegardées dans 'simulation_log.txt'" << std::endl;
    outputFile.close();
}