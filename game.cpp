#include "Game.h"
#include "ConsoleDisplay.h"
#include "GraphicalDisplay.h"
#include <thread>
#include <chrono>

// Constructeur original
Game::Game(const std::string& filePath, DisplayMode mode)
    : grid(FileHandler::loadGridFromFile(filePath)),
      iterationCount(0),
      isRunning(false),
      iterationDelay(100) {
    initializeDisplay(mode);
}

// Nouveau constructeur simple
Game::Game(const std::string& filePath, DisplayMode mode, FileType fileType)
    : grid(1, 1),  // Initialisation temporaire
      iterationCount(0),
      isRunning(false),
      iterationDelay(100) {

    if (fileType == FileType::STANDARD) {
        grid = FileHandler::loadGridFromFile(filePath);
    } else if (fileType == FileType::RLE) {
        grid = RLEReader::loadFromFile(filePath);
    }

    initializeDisplay(mode);
}

// Constructeur avec dimensions spécifiées
Game::Game(const std::string& filePath, DisplayMode mode, FileType fileType, int width, int height)
    : grid(width, height),
      iterationCount(0),
      isRunning(false),
      iterationDelay(100) {

    if (fileType == FileType::STANDARD) {
        FileHandler::loadGridFromFile(filePath, grid);
    } else if (fileType == FileType::RLE) {
        RLEReader::loadFromFile(filePath, grid);
    }

    initializeDisplay(mode);
}

void Game::initializeDisplay(DisplayMode mode) {
    switch (mode) {
        case DisplayMode::CONSOLE:
            displayManager = std::make_unique<ConsoleDisplay>();
            break;
        case DisplayMode::GRAPHICAL: {
            auto graphicalDisplay = std::make_unique<GraphicalDisplay>();
            graphicalDisplay->setGrid(&grid);
            displayManager = std::move(graphicalDisplay);
            break;
        }
    }
}

void Game::run() {
    isRunning = true;
    displayManager->initialize();

    while (isRunning) {
        grid.updateCells();
        displayManager->update(grid);
        iterationCount++;

        if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
            if (!graphicalDisplay->isWindowOpen()) {
                isRunning = false;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(iterationDelay));
    }

    displayManager->close();
}

void Game::pause() {
    isRunning = false;
}

void Game::resume() {
    isRunning = true;
}

void Game::setIterationDelay(int ms) {
    iterationDelay = ms;
}

int Game::getCurrentIteration() const {
    return iterationCount;
}