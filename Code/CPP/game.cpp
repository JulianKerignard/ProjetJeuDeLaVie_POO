#include "Game.h"
#include "ConsoleDisplay.h"
#include "GraphicalDisplay.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

// Le constructeur standard initialise le jeu à partir d'un fichier existant
Game::Game(const std::string& filePath, DisplayMode mode)
    : grid(FileHandler::loadGridFromFile(filePath)),  // Charge la grille depuis le fichier
      iterationCount(0),                              // Commence à l'itération 0
      isRunning(false),                               // Le jeu est initialement arrêté
      iterationDelay(100.0f),                         // Délai par défaut de 100ms
      lastUpdateSpeed(100.0f) {                       // Vitesse initiale de référence
    initializeDisplay(mode);                          // Configure le mode d'affichage
}

// Constructeur supportant différents types de fichiers (standard ou RLE)
Game::Game(const std::string& filePath, DisplayMode mode, FileType fileType)
    : grid(1, 1),  // Crée une grille temporaire minimale
      iterationCount(0),
      isRunning(false),
      iterationDelay(100.0f),
      lastUpdateSpeed(100.0f) {

    // Charge le fichier selon son type
    if (fileType == FileType::STANDARD) {
        grid = FileHandler::loadGridFromFile(filePath);
    } else if (fileType == FileType::RLE) {
        grid = RLEReader::loadFromFile(filePath);
    }

    initializeDisplay(mode);
}

// Constructeur avec dimensions personnalisées
Game::Game(const std::string& filePath, DisplayMode mode, FileType fileType, int width, int height)
    : grid(width, height),  // Crée une grille aux dimensions spécifiées
      iterationCount(0),
      isRunning(false),
      iterationDelay(100.0f),
      lastUpdateSpeed(100.0f) {

    // Charge la configuration si un fichier est spécifié
    if (!filePath.empty()) {
        if (fileType == FileType::STANDARD) {
            FileHandler::loadGridFromFile(filePath, grid);
        } else if (fileType == FileType::RLE) {
            RLEReader::loadFromFile(filePath, grid);
        }
    }

    initializeDisplay(mode);
}

// Configure l'affichage selon le mode choisi
void Game::initializeDisplay(DisplayMode mode) {
    switch (mode) {
        case DisplayMode::CONSOLE:
            displayManager = std::make_unique<ConsoleDisplay>();
            break;
        case DisplayMode::GRAPHICAL: {
            auto graphicalDisplay = std::make_unique<GraphicalDisplay>();
            graphicalDisplay->setGrid(&grid);
            graphicalDisplay->setIterationDelay(iterationDelay);
            displayManager = std::move(graphicalDisplay);
            break;
        }
    }
}

// Crée une nouvelle configuration avec un glider au centre
void Game::createNewConfigFile(int width, int height) {
    const std::string filename = "new_config.txt";
    std::ofstream initFile;

    // Ouvre le fichier en mode écriture, en écrasant tout contenu existant
    initFile.open(filename, std::ios::out | std::ios::trunc);

    if (!initFile.is_open()) {
        std::cerr << "Impossible de créer le fichier : " << filename << std::endl;
        std::cerr << "Vérifiez les permissions et le chemin d'accès" << std::endl;
        throw std::runtime_error("Erreur lors de la création du fichier de configuration");
    }

    try {
        // Écrit les dimensions de la grille sur la première ligne
        initFile << width << " " << height << "\n";

        // Calcule la position centrale pour le glider
        int centerX = width / 2;
        int centerY = height / 2;

        // Génère la grille ligne par ligne
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // Vérifie si la cellule actuelle fait partie du glider
                bool isGlider = (x == centerX && y == centerY-1) ||     // Tête
                              (x == centerX+1 && y == centerY) ||       // Corps
                              (x == centerX-1 && y == centerY+1) ||     // Queue gauche
                              (x == centerX && y == centerY+1) ||       // Queue milieu
                              (x == centerX+1 && y == centerY+1);       // Queue droite

                initFile << (isGlider ? "1" : "0");

                // Ajoute un espace entre les cellules sauf à la fin de la ligne
                if (x < width - 1) initFile << " ";
            }
            initFile << "\n";  // Nouvelle ligne après chaque rangée
        }

        initFile.close();
        std::cout << "Configuration créée avec succès dans : " << filename << std::endl;
    }
    catch (const std::exception& e) {
        initFile.close();
        throw std::runtime_error("Erreur lors de l'écriture de la configuration : " + std::string(e.what()));
    }
}

// Interface utilisateur principale
void Game::userInterface() {
    try {
        std::string filename;
        int choice, displayChoice;
        float iterationDelay;

        // Menu de sélection du mode d'affichage
        std::cout << "Mode d'affichage:" << std::endl;
        std::cout << "1. Mode Console" << std::endl;
        std::cout << "2. Mode Graphique" << std::endl;
        std::cout << "Votre choix (1 ou 2): ";
        std::cin >> displayChoice;

        DisplayMode mode = (displayChoice == 1) ? DisplayMode::CONSOLE : DisplayMode::GRAPHICAL;

        // Menu principal
        std::cout << "\nJeu de la vie" << std::endl;
        std::cout << "1. Utiliser un fichier existant (standard)" << std::endl;
        std::cout << "2. Utiliser un fichier RLE (Mode Graphique uniquement)" << std::endl;
        std::cout << "3. Créer une nouvelle configuration" << std::endl;
        std::cout << "Votre choix (1, 2 ou 3): ";
        std::cin >> choice;

        if (choice == 1) {
            // Chargement d'un fichier standard existant
            std::cout << "Entrez le nom du fichier (ex: init.txt): ";
            std::cin >> filename;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            Game game(filename, mode, FileType::STANDARD);
            game.setIterationDelay(iterationDelay);
            game.run();
        }
        else if (choice == 2 && mode == DisplayMode::GRAPHICAL) {
            // Chargement d'un fichier RLE
            std::cout << "Entrez le nom du fichier RLE (ex: glider.rle): ";
            std::cin >> filename;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            Game game(filename, mode, FileType::RLE);
            game.setIterationDelay(iterationDelay);
            game.run();
        }
        else if (choice == 3) {
            // Création d'une nouvelle configuration
            int width, height;
            std::cout << "Largeur de la grille: ";
            std::cin >> width;
            std::cout << "Hauteur de la grille: ";
            std::cin >> height;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            try {
                // Crée d'abord une configuration temporaire
                Game tempGame("", mode, FileType::STANDARD);
                tempGame.createNewConfigFile(width, height);

                std::cout << "Configuration créée, chargement en cours..." << std::endl;

                // Crée ensuite le jeu avec la nouvelle configuration
                Game game("new_config.txt", mode, FileType::STANDARD);
                game.setIterationDelay(iterationDelay);
                game.run();
            }
            catch (const std::exception& e) {
                std::cerr << "Erreur: " << e.what() << std::endl;
                throw; // Propage l'erreur pour une gestion uniforme
            }
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

// Boucle principale du jeu
void Game::run() {
    isRunning = true;
    displayManager->initialize();
    std::cout << "Démarrage de la simulation (délai: " << iterationDelay << "ms)" << std::endl;

    while (isRunning) {
        // Vérifie l'état de la fenêtre et met à jour la vitesse en mode graphique
        if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
            if (!graphicalDisplay->isWindowOpen()) {
                isRunning = false;
                break;
            }

            // Synchronise la vitesse avec l'affichage graphique
            float currentSpeed = graphicalDisplay->getIterationSpeed();
            if (currentSpeed != lastUpdateSpeed) {
                iterationDelay = currentSpeed;
                lastUpdateSpeed = currentSpeed;
                std::cout << "Vitesse mise à jour: " << iterationDelay << "ms" << std::endl;
            }
        }

        // Met à jour et affiche l'état du jeu
        grid.updateCells();
        displayManager->update(grid);
        iterationCount++;

        // Attend le délai configuré avant la prochaine itération
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(iterationDelay)));
    }

    displayManager->close();
}

// Méthodes de contrôle du jeu
void Game::pause() {
    isRunning = false;
    std::cout << "Jeu en pause" << std::endl;
}

void Game::resume() {
    isRunning = true;
    std::cout << "Reprise du jeu" << std::endl;
}

void Game::setIterationDelay(float ms) {
    iterationDelay = std::clamp(ms, 50.0f, 1000.0f);
    lastUpdateSpeed = iterationDelay;

    if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
        graphicalDisplay->setIterationDelay(iterationDelay);
        std::cout << "Vitesse de simulation réglée à " << iterationDelay << "ms" << std::endl;
    }
}

void Game::updateIterationDelay(float delta) {
    float newDelay = std::clamp(iterationDelay + delta, 50.0f, 1000.0f);

    if (newDelay != iterationDelay) {
        iterationDelay = newDelay;
        lastUpdateSpeed = iterationDelay;

        if (auto* graphicalDisplay = dynamic_cast<GraphicalDisplay*>(displayManager.get())) {
            graphicalDisplay->setIterationDelay(iterationDelay);
            std::cout << "Vitesse mise à jour à " << iterationDelay << "ms" << std::endl;
        }
    }
}

// Accesseur pour le compteur d'itérations
int Game::getCurrentIteration() const {
    return iterationCount;
}