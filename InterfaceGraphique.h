#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"

class GraphicalInterface {
private:
    sf::RenderWindow window;
    Grid& gameGrid;

public:
    GraphicalInterface(Grid& grid);
    
    void drawGrid();
    void handleEvents();
    void updateDisplay();
    void setIterationSpeed(int speed);
};