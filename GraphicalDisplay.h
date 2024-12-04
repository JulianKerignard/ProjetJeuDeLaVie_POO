#ifndef GRAPHICAL_DISPLAY_H
#define GRAPHICAL_DISPLAY_H

#include "DisplayManager.h"
#include <SFML/Graphics.hpp>

class GraphicalDisplay : public DisplayManager {
private:
    sf::RenderWindow window;
    sf::RenderTexture buffer;
    float cellSize;
    Grid* grid;
    bool isDrawing;
    sf::Font font;
    sf::Text helpText;
    sf::RectangleShape cellShape;  // Réutilisable pour toutes les cellules

    const sf::Color ALIVE_COLOR = sf::Color::White;
    const sf::Color DEAD_COLOR = sf::Color::Black;
    const sf::Color GRID_COLOR = sf::Color(50, 50, 50);
    const sf::Color OBSTACLE_COLOR = sf::Color::Red;

    void handleEvents();
    void drawCell(float x, float y, float size, sf::Color color, bool drawOutline = false);
    bool isCellVisible(float x, float y, float windowWidth, float windowHeight) const;

public:
    GraphicalDisplay(int windowWidth = 1920, int windowHeight = 1080);
    void initialize() override;
    void update(const Grid& grid) override;
    void close() override;
    bool isWindowOpen() const;
    void setGrid(Grid* g) { grid = g; }
};

#endif // GRAPHICAL_DISPLAY_H