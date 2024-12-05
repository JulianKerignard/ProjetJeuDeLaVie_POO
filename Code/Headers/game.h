#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "ConsoleDisplay.h"
#include "GraphicalDisplay.h"
#include "FileHandler.h"
#include "RLEReader.h"
#include <memory>
#include <string>
#include <algorithm>

// Définit les modes d'affichage disponibles
enum class DisplayMode {
    CONSOLE,    // Mode console texte
    GRAPHICAL   // Mode interface graphique SFML
};

// Définit les types de fichiers supportés
enum class FileType {
    STANDARD,   // Format texte standard
    RLE         // Format Run Length Encoding
};

class Game {
private:
    Grid grid;                                      // La grille du jeu
    std::unique_ptr<DisplayManager> displayManager; // Gestionnaire d'affichage polymorphique
    int iterationCount;                            // Compte les itérations du jeu
    bool isRunning;                                // État d'exécution du jeu
    float iterationDelay;                          // Délai entre les itérations (en ms)
    float lastUpdateSpeed;                         // Dernière vitesse connue

    // Initialise le mode d'affichage approprié
    void initializeDisplay(DisplayMode mode);

public:
    // Constructeurs
    Game(const std::string& filePath, DisplayMode mode);
    Game(const std::string& filePath, DisplayMode mode, FileType fileType);
    Game(const std::string& filePath, DisplayMode mode, FileType fileType, int width, int height);

    // Interface utilisateur statique
    static void userInterface();

    // Crée un nouveau fichier de configuration avec les dimensions spécifiées
    static void createNewConfigFile(int width, int height);

    // Méthodes de contrôle
    void run();                               // Lance la boucle principale
    void pause();                             // Met le jeu en pause
    void resume();                            // Reprend le jeu
    void setIterationDelay(float ms);         // Définit le délai entre les itérations
    void updateIterationDelay(float delta);   // Modifie le délai d'itération

    // Accesseurs
    int getCurrentIteration() const;
    float getIterationDelay() const { return iterationDelay; }
    bool isGameRunning() const { return isRunning; }
};

#endif // GAME_H