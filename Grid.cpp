#include "Grid.h"
#include <fstream>
#include <iostream>

Grid::Grid(int rows, int columns) : rows(rows), columns(columns) {
    cells.resize(rows, std::vector<Cell>(columns));

    // Initialisation des cellules avec leurs coordonnées
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cells[i][j] = Cell(false, i, j);
        }
    }
}

bool Grid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }

    // Logique de chargement depuis un fichier
    // Par exemple, lire un fichier avec des 0 et des 1

    return true;
}

void Grid::updateGrid() {
    // Créer une copie temporaire pour calculer l'évolution
    std::vector<std::vector<Cell>> newCells = cells;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            newCells[i][j].evolve(*this);
        }
    }

    cells = newCells;
}

Cell& Grid::getCell(int x, int y) {
    // Gérer les débordements si nécessaire
    return cells[x][y];
}

void Grid::displayConsole() {
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            std::cout << (cell.getState() ? "■" : "□") << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::displayGraphical() {
    // Implémentation à compléter avec SFML
}