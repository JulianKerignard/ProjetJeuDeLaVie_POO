#include "../Headers/GraphicalDisplay.h"
#include <iostream>
#include <sstream>

// Constructeur avec initialisation des composants
GraphicalDisplay::GraphicalDisplay(int windowWidth, int windowHeight)
    : window(sf::VideoMode(windowWidth, windowHeight), "Game of Life"),
      cellSize(10.0f),
      isDrawing(false),
      grid(nullptr),
      lastFPS(0.0f),
      iterationSpeed(100.0f),
      paused(false),
      currentIteration(0),
      maxIterations(0) {

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

    fpsText.setFont(font);
    fpsText.setCharacterSize(14);
    fpsText.setFillColor(sf::Color::Yellow);
    fpsText.setPosition(10, window.getSize().y - 20);
}

void GraphicalDisplay::initialize() {
    std::cout << "Initialisation de l'affichage graphique" << std::endl;
    std::cout << "Vitesse initiale : " << iterationSpeed << "ms" << std::endl;
}

bool GraphicalDisplay::isCellVisible(float x, float y, float windowWidth, float windowHeight) const {
    return x >= -cellSize && x <= windowWidth && y >= -cellSize && y <= windowHeight;
}

void GraphicalDisplay::drawCell(float x, float y, float size, sf::Color color, bool drawOutline) {
    cellShape.setPosition(x, y);
    cellShape.setSize(sf::Vector2f(size - 1, size - 1));
    cellShape.setFillColor(color);
    buffer.draw(cellShape);
}

void GraphicalDisplay::updateFPS() {
    float currentTime = fpsClock.restart().asSeconds();
    lastFPS = 1.f / currentTime;

    std::stringstream fpsStr;
    fpsStr << "FPS: " << static_cast<int>(lastFPS);
    fpsText.setString(fpsStr.str());
}

void GraphicalDisplay::drawInterface(const Grid& grid) {
    std::stringstream controls;
    controls << "Controles:\n"
             << "T: Mode torique " << (grid.getToroidal() ? "(ON)" : "(OFF)") << "\n"
             << "G: Placer un Glider\n"
             << "O: Placer un obstacle\n"
             << "Espace: " << (paused ? "PAUSE" : "EN COURS") << "\n"
             << "Clic gauche: Activer/Desactiver une cellule\n"
             << "PageUp/PageDown: Vitesse [" << iterationSpeed << "ms]\n"
             << "Echap: Quitter\n"
             << "Taille: " << grid.getWidth() << "x" << grid.getHeight() << "\n"
             << "Itération: " << currentIteration << "/"
             << (maxIterations > 0 ? std::to_string(maxIterations) : "∞") << "\n";
    helpText.setString(controls.str());
    buffer.draw(helpText);
    buffer.draw(fpsText);
}

void GraphicalDisplay::update(const Grid& grid) {
    handleEvents();
    updateFPS();

    if (window.isOpen()) {
        buffer.clear(DEAD_COLOR);

        float gridWidth = static_cast<float>(window.getSize().x);
        float gridHeight = static_cast<float>(window.getSize().y);
        cellSize = std::min(gridWidth / grid.getWidth(), gridHeight / grid.getHeight());

        float offsetX = (gridWidth - (cellSize * grid.getWidth())) / 2;
        float offsetY = (gridHeight - (cellSize * grid.getHeight())) / 2;

        int startX = std::max(0, static_cast<int>(-offsetX / cellSize));
        int startY = std::max(0, static_cast<int>(-offsetY / cellSize));
        int endX = std::min(grid.getWidth(), static_cast<int>((gridWidth - offsetX) / cellSize) + 1);
        int endY = std::min(grid.getHeight(), static_cast<int>((gridHeight - offsetY) / cellSize) + 1);

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

        drawInterface(grid);

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
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;

                    case sf::Keyboard::Space:
                        paused = !paused;
                        std::cout << (paused ? "Jeu en pause" : "Jeu repris") << std::endl;
                        break;

                    case sf::Keyboard::T:
                        if (grid) {
                            grid->setToroidal(!grid->getToroidal());
                            std::cout << "Mode torique : " << (grid->getToroidal() ? "activé" : "désactivé") << std::endl;
                        }
                        break;

                    case sf::Keyboard::PageUp:
                        iterationSpeed = std::max(50.0f, iterationSpeed - 50.0f);
                        std::cout << "Vitesse d'itération : " << iterationSpeed << "ms" << std::endl;
                        break;

                    case sf::Keyboard::PageDown:
                        iterationSpeed = std::min(1000.0f, iterationSpeed + 50.0f);
                        std::cout << "Vitesse d'itération : " << iterationSpeed << "ms" << std::endl;
                        break;

                    case sf::Keyboard::G:
                        if (grid) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int gridX = mousePos.x / cellSize;
                            int gridY = mousePos.y / cellSize;
                            if (gridX >= 0 && gridX < grid->getWidth() && gridY >= 0 && gridY < grid->getHeight()) {
                                grid->addPattern(Pattern::GLIDER, gridX, gridY);
                                std::cout << "Glider ajouté en (" << gridX << "," << gridY << ")" << std::endl;
                            }
                        }
                        break;

                    case sf::Keyboard::O:
                        if (grid) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int gridX = mousePos.x / cellSize;
                            int gridY = mousePos.y / cellSize;
                            if (gridX >= 0 && gridX < grid->getWidth() && gridY >= 0 && gridY < grid->getHeight()) {
                                grid->addObstacle(gridX, gridY);
                                std::cout << "Obstacle ajouté en (" << gridX << "," << gridY << ")" << std::endl;
                            }
                        }
                        break;
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left && grid) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int gridX = mousePos.x / cellSize;
                    int gridY = mousePos.y / cellSize;
                    if (gridX >= 0 && gridX < grid->getWidth() && gridY >= 0 && gridY < grid->getHeight()) {
                        const Cell& currentCell = grid->getCellAt(gridX, gridY);
                        CellState newState = (currentCell.getCurrentState() == CellState::ALIVE)
                                         ? CellState::DEAD
                                         : CellState::ALIVE;
                        grid->setCellAt(gridX, gridY, newState);
                        std::cout << "Cellule " << (newState == CellState::ALIVE ? "activée" : "désactivée")
                                 << " en (" << gridX << "," << gridY << ")" << std::endl;
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