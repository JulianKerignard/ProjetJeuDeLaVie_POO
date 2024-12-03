#include "GraphicalDisplay.h"
#include <iostream>

GraphicalDisplay::GraphicalDisplay(int windowWidth, int windowHeight) 
    : window(sf::VideoMode(windowWidth, windowHeight), "Game of Life") {
    window.setFramerateLimit(60);
    cellShape = sf::RectangleShape();
}

void GraphicalDisplay::initialize() {
    std::cout << "Initialisation de l'affichage graphique" << std::endl;
}

void GraphicalDisplay::update(const Grid& grid) {
    handleEvents();
    
    if (window.isOpen()) {
        window.clear(DEAD_COLOR);
        
        // Calculer la taille des cellules en fonction de la taille de la fenêtre et de la grille
        float gridWidth = static_cast<float>(window.getSize().x);
        float gridHeight = static_cast<float>(window.getSize().y);
        cellSize = std::min(gridWidth / grid.getWidth(), gridHeight / grid.getHeight());
        
        // Centrer la grille dans la fenêtre
        float offsetX = (gridWidth - (cellSize * grid.getWidth())) / 2;
        float offsetY = (gridHeight - (cellSize * grid.getHeight())) / 2;
        
        // Dessiner les cellules
        cellShape.setSize(sf::Vector2f(cellSize - 1, cellSize - 1));  // -1 pour l'espace entre les cellules
        
        for (int y = 0; y < grid.getHeight(); y++) {
            for (int x = 0; x < grid.getWidth(); x++) {
                cellShape.setPosition(offsetX + x * cellSize, offsetY + y * cellSize);
                
                const Cell& cell = grid.getCellAt(x, y);
                if (cell.isObstacleCell()) {
                    cellShape.setFillColor(OBSTACLE_COLOR);
                } else if (cell.getCurrentState() == CellState::ALIVE) {
                    cellShape.setFillColor(ALIVE_COLOR);
                } else {
                    cellShape.setFillColor(DEAD_COLOR);
                    cellShape.setOutlineColor(GRID_COLOR);
                    cellShape.setOutlineThickness(0.5f);
                }
                
                window.draw(cellShape);
            }
        }
        
        window.display();
    }
}

void GraphicalDisplay::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
            default:
                break;
        }
    }
}

void GraphicalDisplay::close() {
    if (window.isOpen()) {
        window.close();
    }
}

bool GraphicalDisplay::isWindowOpen() const {
    return window.isOpen();
}