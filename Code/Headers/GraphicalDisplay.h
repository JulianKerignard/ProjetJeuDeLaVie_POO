#ifndef GRAPHICAL_DISPLAY_H
#define GRAPHICAL_DISPLAY_H

#include "DisplayManager.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

class GraphicalDisplay : public DisplayManager {
private:
    // Éléments de la fenêtre et du rendu
    sf::RenderWindow window;      // Fenêtre principale SFML
    sf::RenderTexture buffer;     // Buffer de rendu pour le double buffering
    float cellSize;               // Taille d'une cellule en pixels
    Grid* grid;                   // Pointeur vers la grille du jeu

    // États et paramètres
    bool isDrawing;               // État du dessin
    float iterationSpeed;         // Vitesse de simulation en ms

    // Interface graphique
    sf::Font font;                // Police pour le texte
    sf::Text helpText;            // Texte d'aide
    sf::Text fpsText;             // Affichage des FPS
    sf::RectangleShape cellShape; // Forme pour dessiner les cellules
    sf::Clock fpsClock;           // Horloge pour les FPS
    float lastFPS;                // Dernier compte de FPS

    // Couleurs
    const sf::Color ALIVE_COLOR = sf::Color::White;
    const sf::Color DEAD_COLOR = sf::Color::Black;
    const sf::Color GRID_COLOR = sf::Color(50, 50, 50);
    const sf::Color OBSTACLE_COLOR = sf::Color::Red;

    // Méthodes privées
    void handleEvents();          // Gestion des événements
    void drawCell(float x, float y, float size, sf::Color color, bool drawOutline = false);
    bool isCellVisible(float x, float y, float windowWidth, float windowHeight) const;
    void updateFPS();             // Mise à jour des FPS
    void drawInterface(const Grid& grid);  // Dessin de l'interface

public:
    // Constructeur et méthodes principales
    GraphicalDisplay(int windowWidth = 1920, int windowHeight = 1080);
    void initialize() override;
    void update(const Grid& grid) override;
    void close() override;
    bool isWindowOpen() const;
    void setGrid(Grid* g) { grid = g; }

    // Contrôle de la vitesse
    void setIterationDelay(float delay) { iterationSpeed = std::clamp(delay, 50.0f, 1000.0f); }
    float getIterationSpeed() const { return iterationSpeed; }
};

#endif // GRAPHICAL_DISPLAY_H