#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "ConsoleDisplay.h"
#include "GraphicalDisplay.h"
#include "FileHandler.h"
#include "RleReader.h"
#include <memory>
#include <string>
#include <algorithm>

// Modes d'affichage disponibles
enum class DisplayMode {
    CONSOLE,    // Mode console texte
    GRAPHICAL   // Mode interface graphique SFML
};

// Types de fichiers supportés
enum class FileType {
    STANDARD,   // Format texte standard
    RLE         // Format Run Length Encoding
};

class Game {
private:
    Grid grid;                                      // La grille du jeu
    std::unique_ptr<DisplayManager> displayManager; // Gestionnaire d'affichage
    int iterationCount;                            // Nombre d'itérations actuelles
    int maxIterations;                             // Nombre maximum d'itérations
    bool isRunning;                                // État d'exécution
    float iterationDelay;                          // Délai entre itérations (ms)
    float lastUpdateSpeed;                         // Dernière vitesse connue

    void initializeDisplay(DisplayMode mode);       // Initialise l'affichage

public:
    // Constructeurs
    Game(const std::string& filePath, DisplayMode mode);
    Game(const std::string& filePath, DisplayMode mode, FileType fileType);
    Game(const std::string& filePath, DisplayMode mode, FileType fileType, int width, int height);

    // Interface utilisateur et création de configuration
    static void userInterface();
    static void createNewConfigFile(int width, int height);

    // Méthodes de contrôle
    void run();
    void pause();
    void resume();
    void setIterationDelay(float ms);
    void updateIterationDelay(float delta);
    void setMaxIterations(int max) { maxIterations = max; }

    // Accesseurs
    int getCurrentIteration() const;
    float getIterationDelay() const { return iterationDelay; }
    bool isGameRunning() const { return isRunning; }
};

#endif // GAME_H