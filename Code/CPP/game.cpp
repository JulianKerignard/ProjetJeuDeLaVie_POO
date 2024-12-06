#include "Game.h"
#include "ConsoleDisplay.h"
#include "GraphicalDisplay.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>

// Constructeur standard
Game::Game(const std::string& filePath, DisplayMode mode)
    : grid(FileHandler::loadGridFromFile(filePath)),
      iterationCount(0),
      maxIterations(0),
      isRunning(false),
      iterationDelay(100.0f),
      lastUpdateSpeed(100.0f) {
    initializeDisplay(mode);
}

// Constructeur avec choix du type de fichier
Game::Game(const std::string& filePath, DisplayMode mode, FileType fileType)
    : grid(1, 1),  // Initialisation temporaire avec une petite grille
      iterationCount(0),
      maxIterations(0),
      isRunning(false),
      iterationDelay(100.0f),
      lastUpdateSpeed(100.0f) {

    try {
        if (fileType == FileType::STANDARD) {
            grid = FileHandler::loadGridFromFile(filePath);  // Gère .txt et .cells
        } else if (fileType == FileType::RLE) {
            grid = RLEReader::loadFromFile(filePath);  // Gère .rle
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement du fichier : " << e.what() << std::endl;
        throw;
    }

    initializeDisplay(mode);
}

// Constructeur avec dimensions spécifiées
Game::Game(const std::string& filePath, DisplayMode mode, FileType fileType, int width, int height)
    : grid(width, height),
      iterationCount(0),
      maxIterations(0),
      isRunning(false),
      iterationDelay(100.0f),
      lastUpdateSpeed(100.0f) {

    if (!filePath.empty()) {
        try {
            if (fileType == FileType::STANDARD) {
                FileHandler::loadGridFromFile(filePath, grid);
            } else if (fileType == FileType::RLE) {
                RLEReader::loadFromFile(filePath, grid);
            }
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors du chargement du fichier : " << e.what() << std::endl;
            throw;
        }
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
            graphicalDisplay->setIterationDelay(iterationDelay);
            graphicalDisplay->setMaxIterations(maxIterations);
            displayManager = std::move(graphicalDisplay);
            break;
        }
        default:
            throw std::invalid_argument("Mode d'affichage invalide");
    }
}

void Game::createNewConfigFile(int width, int height) {
    const std::string filename = "new_config.txt";
    std::ofstream initFile(filename);

    if (!initFile.is_open()) {
        throw std::runtime_error("Impossible de créer le fichier : " + filename);
    }

    try {
        initFile << width << " " << height << "\n";

        int centerX = width / 2;
        int centerY = height / 2;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bool isGlider = (x == centerX && y == centerY-1) ||
                               (x == centerX+1 && y == centerY) ||
                               (x == centerX-1 && y == centerY+1) ||
                               (x == centerX && y == centerY+1) ||
                               (x == centerX+1 && y == centerY+1);

                initFile << (isGlider ? "1" : "0");
                if (x < width - 1) initFile << " ";
            }
            initFile << "\n";
        }

        initFile.close();
        std::cout << "Configuration créée avec succès dans : " << filename << std::endl;
    }
    catch (...) {
        initFile.close();
        throw std::runtime_error("Erreur lors de l'écriture dans le fichier");
    }
}

void Game::userInterface() {
    try {
        std::string filename;
        int choice, displayChoice;
        float iterationDelay;
        int maxIterations;

        // Menu de sélection du mode d'affichage
        std::cout << "Mode d'affichage:" << std::endl;
        std::cout << "1. Mode Console" << std::endl;
        std::cout << "2. Mode Graphique" << std::endl;
        std::cout << "Votre choix (1 ou 2): ";
        std::cin >> displayChoice;

        // Configuration du nombre d'itérations
        std::cout << "Nombre d'itérations (0 pour infini): ";
        std::cin >> maxIterations;

        DisplayMode mode = (displayChoice == 1) ? DisplayMode::CONSOLE : DisplayMode::GRAPHICAL;

        std::cout << "\nJeu de la vie" << std::endl;
        std::cout << "1. Utiliser un fichier existant (.txt ou .cells)" << std::endl;
        std::cout << "2. Utiliser un fichier RLE" << std::endl;
        std::cout << "3. Créer une nouvelle configuration" << std::endl;
        std::cout << "Votre choix (1, 2 ou 3): ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Entrez le nom du fichier (ex: pattern.txt, pattern.cells): ";
            std::cin >> filename;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            Game game(filename, mode, FileType::STANDARD);
            game.setIterationDelay(iterationDelay);
            game.setMaxIterations(maxIterations);
            game.run();
        }
        else if (choice == 2) {
            std::cout << "Entrez le nom du fichier RLE (ex: pattern.rle): ";
            std::cin >> filename;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            Game game(filename, mode, FileType::RLE);
            game.setIterationDelay(iterationDelay);
            game.setMaxIterations(maxIterations);
            game.run();
        }
        else if (choice == 3) {
            int width, height;
            std::cout << "Largeur de la grille: ";
            std::cin >> width;
            std::cout << "Hauteur de la grille: ";
            std::cin >> height;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            createNewConfigFile(width, height);
            Game game("new_config.txt", mode, FileType::STANDARD);
            game.setIterationDelay(iterationDelay);
            game.setMaxIterations(maxIterations);
            game.run();
        }
        else {
            throw std::runtime_error("Choix invalide");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        std::cout << "Appuyez sur Entrée pour quitter...";
        std::cin.get();
        std::cin.get();
    }
}

void Game::run() {
    isRunning = true;
    displayManager->initialize();
    std::cout << "Démarrage avec délai : " << iterationDelay << "ms" << std::endl;
    if (maxIterations > 0) {
        std::cout << "Nombre maximum d'itérations : " << maxIterations << std::endl;
    } else {
        std::cout << "Mode infini activé" << std::endl;
    }

    while (isRunning) {
        if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
            if (!graphicalDisplay->isWindowOpen()) {
                isRunning = false;
                break;
            }

            float currentSpeed = graphicalDisplay->getIterationSpeed();
            if (currentSpeed != lastUpdateSpeed) {
                iterationDelay = currentSpeed;
                lastUpdateSpeed = currentSpeed;
            }

            graphicalDisplay->setIterationCount(iterationCount);
            displayManager->update(grid);

            if (!graphicalDisplay->isPaused()) {
                grid.updateCells();
                iterationCount++;

                if (maxIterations > 0 && iterationCount >= maxIterations) {
                    std::cout << "Nombre maximum d'itérations atteint (" << maxIterations << ")" << std::endl;
                    isRunning = false;
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(iterationDelay)));
            }
        } else {
            grid.updateCells();
            displayManager->update(grid);
            iterationCount++;

            if (maxIterations > 0 && iterationCount >= maxIterations) {
                std::cout << "Nombre maximum d'itérations atteint (" << maxIterations << ")" << std::endl;
                isRunning = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(iterationDelay)));
        }
    }
    displayManager->close();
}

void Game::pause() {
    if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
        graphicalDisplay->togglePause();
    }
}

void Game::resume() {
    if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
        graphicalDisplay->togglePause();
    }
}

void Game::setIterationDelay(float ms) {
    iterationDelay = std::clamp(ms, 50.0f, 1000.0f);
    lastUpdateSpeed = iterationDelay;

    if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
        graphicalDisplay->setIterationDelay(iterationDelay);
    }
}

void Game::updateIterationDelay(float delta) {
    float newDelay = std::clamp(iterationDelay + delta, 50.0f, 1000.0f);
    if (newDelay != iterationDelay) {
        iterationDelay = newDelay;
        lastUpdateSpeed = iterationDelay;

        if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
            graphicalDisplay->setIterationDelay(iterationDelay);
        }
    }
}

int Game::getCurrentIteration() const {
    return iterationCount;
}
