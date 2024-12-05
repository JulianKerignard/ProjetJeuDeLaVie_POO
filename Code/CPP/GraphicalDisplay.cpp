#include "GraphicalDisplay.h"
#include <iostream>
#include <sstream>

// Le constructeur initialise tous les éléments graphiques nécessaires au jeu
GraphicalDisplay::GraphicalDisplay(int windowWidth, int windowHeight)
    : window(sf::VideoMode(windowWidth, windowHeight), "Game of Life"),
      cellSize(10.0f),
      isDrawing(false),
      grid(nullptr),
      lastFPS(0.0f),
      iterationSpeed(100.0f) {

    // Active la synchronisation verticale pour un affichage plus fluide
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);  // Limite les FPS pour économiser les ressources

    // Prépare le buffer pour le double buffering (évite le scintillement)
    buffer.create(windowWidth, windowHeight);
    cellShape.setSize(sf::Vector2f(cellSize - 1, cellSize - 1));

    // Charge la police pour l'interface utilisateur
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erreur de chargement de la police" << std::endl;
    }

    // Configure le texte d'aide qui affiche les commandes
    helpText.setFont(font);
    helpText.setCharacterSize(14);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(10, 10);

    // Configure l'affichage des FPS
    fpsText.setFont(font);
    fpsText.setCharacterSize(14);
    fpsText.setFillColor(sf::Color::Yellow);
    fpsText.setPosition(10, window.getSize().y - 20);
}

void GraphicalDisplay::initialize() {
    std::cout << "Initialisation de l'affichage graphique" << std::endl;
    std::cout << "Vitesse initiale : " << iterationSpeed << "ms" << std::endl;
}

// Détermine si une cellule est dans le champ visible de la fenêtre
bool GraphicalDisplay::isCellVisible(float x, float y, float windowWidth, float windowHeight) const {
    return x >= -cellSize && x <= windowWidth && y >= -cellSize && y <= windowHeight;
}

// Dessine une cellule individuelle avec la couleur spécifiée
void GraphicalDisplay::drawCell(float x, float y, float size, sf::Color color, bool drawOutline) {
    cellShape.setPosition(x, y);
    cellShape.setSize(sf::Vector2f(size - 1, size - 1));
    cellShape.setFillColor(color);
    buffer.draw(cellShape);
}

// Met à jour le compteur de FPS
void GraphicalDisplay::updateFPS() {
    float currentTime = fpsClock.restart().asSeconds();
    lastFPS = 1.f / currentTime;

    std::stringstream fpsStr;
    fpsStr << "FPS: " << static_cast<int>(lastFPS);
    fpsText.setString(fpsStr.str());
}

// Affiche l'interface utilisateur avec toutes les informations et commandes
void GraphicalDisplay::drawInterface(const Grid& grid) {
    std::stringstream controls;
    controls << "Controles:\n"
             << "T: Mode torique " << (grid.getToroidal() ? "(ON)" : "(OFF)") << "\n"
             << "G: Placer un Glider\n"
             << "O: Placer un obstacle\n"
             << "Clic gauche: Activer/Desactiver une cellule\n"
             << "PageUp/PageDown: Vitesse [" << iterationSpeed << "ms]\n"
             << "Echap: Quitter\n"
             << "Taille: " << grid.getWidth() << "x" << grid.getHeight() << "\n";
    helpText.setString(controls.str());
    buffer.draw(helpText);
    buffer.draw(fpsText);
}

// Mise à jour principale de l'affichage
void GraphicalDisplay::update(const Grid& grid) {
    handleEvents();
    updateFPS();

    if (window.isOpen()) {
        // Efface le buffer avec la couleur de fond
        buffer.clear(DEAD_COLOR);

        // Calcule les dimensions pour centrer la grille
        float gridWidth = static_cast<float>(window.getSize().x);
        float gridHeight = static_cast<float>(window.getSize().y);
        cellSize = std::min(gridWidth / grid.getWidth(), gridHeight / grid.getHeight());

        // Calcule les offsets pour centrer la grille dans la fenêtre
        float offsetX = (gridWidth - (cellSize * grid.getWidth())) / 2;
        float offsetY = (gridHeight - (cellSize * grid.getHeight())) / 2;

        // Optimisation : ne dessine que les cellules visibles
        int startX = std::max(0, static_cast<int>(-offsetX / cellSize));
        int startY = std::max(0, static_cast<int>(-offsetY / cellSize));
        int endX = std::min(grid.getWidth(), static_cast<int>((gridWidth - offsetX) / cellSize) + 1);
        int endY = std::min(grid.getHeight(), static_cast<int>((gridHeight - offsetY) / cellSize) + 1);

        // Dessine chaque cellule visible
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

        // Affiche le résultat final
        buffer.display();
        sf::Sprite sprite(buffer.getTexture());
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

// Gestion des événements utilisateur
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