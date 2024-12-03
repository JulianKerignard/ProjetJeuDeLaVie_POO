#include "Game.h"
#include "ConsoleDisplay.h"
#include "GraphicalDisplay.h"
#include <thread>
#include <chrono>

Game::Game(const std::string& filePath, DisplayMode mode)
    : grid(FileHandler::loadGridFromFile(filePath)),
      iterationCount(0),
      isRunning(false),
      iterationDelay(100) {

    switch (mode) {
        case DisplayMode::CONSOLE:
            displayManager = std::make_unique<ConsoleDisplay>();
        break;
        case DisplayMode::GRAPHICAL:
            displayManager = std::make_unique<GraphicalDisplay>();
        break;
    }
}

void Game::run() {
    isRunning = true;
    displayManager->initialize();

    while (isRunning) {
        grid.updateCells();
        displayManager->update(grid);
        iterationCount++;

        // Pour l'affichage graphique, vérifions si la fenêtre est toujours ouverte
        if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
            if (!graphicalDisplay->isWindowOpen()) {
                isRunning = false;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(iterationDelay));
    }
}

void Game::pause() {
    isRunning = false;
}

void Game::resume() {
    isRunning = true;
}

// Ajout de l'implémentation manquante
void Game::setIterationDelay(int ms) {
    iterationDelay = ms;
}

int Game::getCurrentIteration() const {
    return iterationCount;
}