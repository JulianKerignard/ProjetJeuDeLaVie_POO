#ifndef GRAPHICAL_DISPLAY_H
#define GRAPHICAL_DISPLAY_H

#include "DisplayManager.h"
#include <SFML/Graphics.hpp>

class GraphicalDisplay : public DisplayManager {
private:
    sf::RenderWindow window;
    float cellSize;
    sf::RectangleShape cellShape;
    
    // Couleurs pour les différents états
    const sf::Color ALIVE_COLOR = sf::Color::White;
    const sf::Color DEAD_COLOR = sf::Color::Black;
    const sf::Color GRID_COLOR = sf::Color(50, 50, 50);
    const sf::Color OBSTACLE_COLOR = sf::Color::Red;

    void drawGrid(const Grid& grid);
    void handleEvents();

public:
    GraphicalDisplay(int windowWidth = 800, int windowHeight = 600);
    void initialize() override;
    void update(const Grid& grid) override;
    void close() override;
    bool isWindowOpen() const;
};

#endif // GRAPHICAL_DISPLAY_H