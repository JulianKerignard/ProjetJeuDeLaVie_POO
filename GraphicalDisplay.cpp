#include "GraphicalDisplay.h"
#include <iostream>
#include <sstream>

GraphicalDisplay::GraphicalDisplay(int windowWidth, int windowHeight)
    : window(sf::VideoMode(windowWidth, windowHeight), "Game of Life"),
      cellSize(10.0f),
      isDrawing(false),
      grid(nullptr) {

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    buffer.create(windowWidth, windowHeight);
    cellShape.setSize(sf::Vector2f(cellSize - 1, cellSize - 1));

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erreur de chargement de la police" << std::endl;
    }
    helpText.setFont(font);
    helpText.setCharacterSize(14);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(10, 10);
}

void GraphicalDisplay::initialize() {
    std::cout << "Initialisation de l'affichage graphique" << std::endl;
}

bool GraphicalDisplay::isCellVisible(float x, float y, float windowWidth, float windowHeight) const {
    return x >= -cellSize && x <= windowWidth && y >= -cellSize && y <= windowHeight;
}

void GraphicalDisplay::drawCell(float x, float y, float size, sf::Color color, bool drawOutline) {
    cellShape.setPosition(x, y);
    cellShape.setSize(sf::Vector2f(size - 1, size - 1));
    cellShape.setFillColor(color);

    if (drawOutline) {
        cellShape.setOutlineThickness(0.5f);
        cellShape.setOutlineColor(GRID_COLOR);
    } else {
        cellShape.setOutlineThickness(0);
    }

    buffer.draw(cellShape);
}

void GraphicalDisplay::update(const Grid& grid) {
    handleEvents();

    if (window.isOpen()) {
        buffer.clear(DEAD_COLOR);

        float gridWidth = static_cast<float>(window.getSize().x);
        float gridHeight = static_cast<float>(window.getSize().y);
        cellSize = std::min(gridWidth / grid.getWidth(), gridHeight / grid.getHeight());

        float offsetX = (gridWidth - (cellSize * grid.getWidth())) / 2;
        float offsetY = (gridHeight - (cellSize * grid.getHeight())) / 2;

        // Calculer la zone visible
        int startX = std::max(0, static_cast<int>(-offsetX / cellSize));
        int startY = std::max(0, static_cast<int>(-offsetY / cellSize));
        int endX = std::min(grid.getWidth(), static_cast<int>((gridWidth - offsetX) / cellSize) + 1);
        int endY = std::min(grid.getHeight(), static_cast<int>((gridHeight - offsetY) / cellSize) + 1);

        // Dessiner seulement les cellules visibles
        for (int y = startY; y < endY; y++) {
            for (int x = startX; x < endX; x++) {
                float posX = offsetX + x * cellSize;
                float posY = offsetY + y * cellSize;

                if (isCellVisible(posX, posY, gridWidth, gridHeight)) {
                    const Cell& cell = grid.getCellAt(x, y);
                    if (cell.isObstacleCell()) {
                        drawCell(posX, posY, cellSize, OBSTACLE_COLOR);
                    } else if (cell.getCurrentState() == CellState::ALIVE) {
                        drawCell(posX, posY, cellSize, ALIVE_COLOR);
                    } else {
                        drawCell(posX, posY, cellSize, DEAD_COLOR, true);
                    }
                }
            }
        }

        // Affichage des contrôles avec info sur la taille
        std::stringstream controls;
        controls << "Controles:\n"
                << "T: Mode torique " << (grid.getToroidal() ? "(ON)" : "(OFF)") << "\n"
                << "G: Placer un glider\n"
                << "O: Placer un obstacle\n"
                << "Clic gauche: Activer/Desactiver une cellule\n"
                << "Echap: Quitter\n"
                << "Taille: " << grid.getWidth() << "x" << grid.getHeight();
        helpText.setString(controls.str());
        buffer.draw(helpText);

        buffer.display();
        sf::Sprite sprite(buffer.getTexture());
        window.clear();
        window.draw(sprite);
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
                else if (event.key.code == sf::Keyboard::T && grid != nullptr) {
                    grid->setToroidal(!grid->getToroidal());
                }
                else if (event.key.code == sf::Keyboard::G && grid != nullptr) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int gridX = mousePos.x / cellSize;
                    int gridY = mousePos.y / cellSize;
                    if (gridX >= 0 && gridX < grid->getWidth() &&
                        gridY >= 0 && gridY < grid->getHeight()) {
                        grid->addPattern(Pattern::GLIDER, gridX, gridY);
                    }
                }
                else if (event.key.code == sf::Keyboard::O && grid != nullptr) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int gridX = mousePos.x / cellSize;
                    int gridY = mousePos.y / cellSize;
                    if (gridX >= 0 && gridX < grid->getWidth() &&
                        gridY >= 0 && gridY < grid->getHeight()) {
                        grid->addObstacle(gridX, gridY);
                    }
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left && grid != nullptr) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int gridX = mousePos.x / cellSize;
                    int gridY = mousePos.y / cellSize;
                    if (gridX >= 0 && gridX < grid->getWidth() &&
                        gridY >= 0 && gridY < grid->getHeight()) {
                        const Cell& currentCell = grid->getCellAt(gridX, gridY);
                        CellState newState = (currentCell.getCurrentState() == CellState::ALIVE)
                            ? CellState::DEAD
                            : CellState::ALIVE;
                        grid->setCellAt(gridX, gridY, newState);
                    }
                }
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