#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <filesystem>
#include <iostream>

// Définition des constantes statiques
const int FileHandler::DEFAULT_CELLS_WIDTH = 50;
const int FileHandler::DEFAULT_CELLS_HEIGHT = 50;

FileFormat FileHandler::getFileFormat(const std::string& path) {
    std::string extension = std::filesystem::path(path).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension == ".txt") return FileFormat::TXT;
    if (extension == ".cells") return FileFormat::CELLS;
    return FileFormat::UNKNOWN;
}

Grid FileHandler::loadGridFromFile(const std::string& path) {
    FileFormat format = getFileFormat(path);
    switch (format) {
        case FileFormat::TXT:
            return loadTxtFile(path);
        case FileFormat::CELLS:
            return loadCellsFile(path);
        default:
            throw std::runtime_error("Format de fichier non supporté : " + path);
    }
}

void FileHandler::loadGridFromFile(const std::string& path, Grid& grid) {
    FileFormat format = getFileFormat(path);
    switch (format) {
        case FileFormat::TXT:
            loadTxtFile(path, grid);
            break;
        case FileFormat::CELLS:
            loadCellsFile(path, grid);
            break;
        default:
            throw std::runtime_error("Format de fichier non supporté : " + path);
    }
}

Grid FileHandler::loadTxtFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
    }

    std::string line;
    std::getline(file, line);
    auto [width, height] = parseGridDimensions(line);

    Grid grid(width, height);
    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        std::istringstream lineStream(line);
        for (int x = 0; x < width; x++) {
            int state;
            if (!(lineStream >> state)) {
                throw std::runtime_error("Format de grille invalide à la ligne " + std::to_string(y + 1));
            }
            if (state == 2) {
                grid.addObstacle(x, y);
            } else {
                grid.setCellAt(x, y, state ? CellState::ALIVE : CellState::DEAD);
            }
        }
    }

    return grid;
}

void FileHandler::loadTxtFile(const std::string& path, Grid& grid) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
    }

    std::string line;
    std::getline(file, line);
    auto [width, height] = parseGridDimensions(line);

    if (width != grid.getWidth() || height != grid.getHeight()) {
        throw std::runtime_error("Les dimensions du fichier ne correspondent pas à la grille");
    }

    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        std::istringstream lineStream(line);
        for (int x = 0; x < width; x++) {
            int state;
            if (!(lineStream >> state)) {
                throw std::runtime_error("Format de grille invalide à la ligne " + std::to_string(y + 1));
            }
            if (state == 2) {
                grid.addObstacle(x, y);
            } else {
                grid.setCellAt(x, y, state ? CellState::ALIVE : CellState::DEAD);
            }
        }
    }
}

Grid FileHandler::loadCellsFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
    }

    // Créer une grille avec les dimensions par défaut
    Grid grid(DEFAULT_CELLS_WIDTH, DEFAULT_CELLS_HEIGHT);

    // Première passe : lire le motif pour obtenir ses dimensions
    std::vector<std::string> pattern;
    std::string line;
    int patternWidth = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '!') continue;
        patternWidth = std::max(patternWidth, static_cast<int>(line.length()));
        pattern.push_back(line);
    }

    int patternHeight = pattern.size();

    // Calculer les coordonnées pour centrer le motif
    int startX = (DEFAULT_CELLS_WIDTH - patternWidth) / 2;
    int startY = (DEFAULT_CELLS_HEIGHT - patternHeight) / 2;

    std::cout << "Création d'une grille " << DEFAULT_CELLS_WIDTH << "x" << DEFAULT_CELLS_HEIGHT << std::endl;
    std::cout << "Motif de taille " << patternWidth << "x" << patternHeight
              << " centré à la position (" << startX << "," << startY << ")" << std::endl;

    // Placer le motif au centre
    for (size_t y = 0; y < pattern.size(); y++) {
        for (size_t x = 0; x < pattern[y].length(); x++) {
            if (pattern[y][x] == 'O' || pattern[y][x] == '*') {
                int gridX = startX + x;
                int gridY = startY + y;
                if (gridX >= 0 && gridX < DEFAULT_CELLS_WIDTH &&
                    gridY >= 0 && gridY < DEFAULT_CELLS_HEIGHT) {
                    grid.setCellAt(gridX, gridY, CellState::ALIVE);
                }
            }
        }
    }

    return grid;
}

void FileHandler::loadCellsFile(const std::string& path, Grid& grid) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
    }

    // Réinitialiser la grille
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            grid.setCellAt(x, y, CellState::DEAD);
        }
    }

    // Première passe : lire le motif
    std::vector<std::string> pattern;
    std::string line;
    int patternWidth = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '!') continue;
        patternWidth = std::max(patternWidth, static_cast<int>(line.length()));
        pattern.push_back(line);
    }

    int patternHeight = pattern.size();

    // Centrer le motif dans la grille existante
    int startX = (grid.getWidth() - patternWidth) / 2;
    int startY = (grid.getHeight() - patternHeight) / 2;

    // Placer le motif
    for (size_t y = 0; y < pattern.size(); y++) {
        for (size_t x = 0; x < pattern[y].length(); x++) {
            if (pattern[y][x] == 'O' || pattern[y][x] == '*') {
                int gridX = startX + x;
                int gridY = startY + y;
                if (gridX >= 0 && gridX < grid.getWidth() &&
                    gridY >= 0 && gridY < grid.getHeight()) {
                    grid.setCellAt(gridX, gridY, CellState::ALIVE);
                }
            }
        }
    }
}

void FileHandler::saveGridToFile(const Grid& grid, const std::string& path) {
    FileFormat format = getFileFormat(path);
    std::ofstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Impossible de créer le fichier : " + path);
    }

    switch (format) {
        case FileFormat::TXT: {
            file << grid.getWidth() << " " << grid.getHeight() << "\n";
            for (int y = 0; y < grid.getHeight(); y++) {
                for (int x = 0; x < grid.getWidth(); x++) {
                    const Cell& cell = grid.getCellAt(x, y);
                    if (cell.isObstacleCell()) {
                        file << "2";
                    } else {
                        file << (cell.getCurrentState() == CellState::ALIVE ? "1" : "0");
                    }
                    if (x < grid.getWidth() - 1) file << " ";
                }
                file << "\n";
            }
            break;
        }
        case FileFormat::CELLS: {
            file << "!Name: Pattern sauvegardé\n";
            file << "!Author: Game of Life\n\n";

            for (int y = 0; y < grid.getHeight(); y++) {
                for (int x = 0; x < grid.getWidth(); x++) {
                    const Cell& cell = grid.getCellAt(x, y);
                    file << (cell.getCurrentState() == CellState::ALIVE ? 'O' : '.');
                }
                file << "\n";
            }
            break;
        }
        default:
            throw std::runtime_error("Format de fichier non supporté pour la sauvegarde");
    }
}

std::pair<int, int> FileHandler::parseGridDimensions(const std::string& line) {
    std::istringstream iss(line);
    int width, height;
    if (!(iss >> width >> height) || width <= 0 || height <= 0) {
        throw std::runtime_error("Format de dimensions invalide");
    }
    return {width, height};
}

bool FileHandler::validateTxtFormat(const std::string& content) {
    std::istringstream iss(content);
    std::string firstLine;
    if (!std::getline(iss, firstLine)) return false;

    try {
        auto [width, height] = parseGridDimensions(firstLine);
        std::string line;
        int lineCount = 0;

        while (std::getline(iss, line) && lineCount < height) {
            std::istringstream lineStream(line);
            int value;
            int columnCount = 0;

            while (lineStream >> value && columnCount < width) {
                if (value != 0 && value != 1 && value != 2) {
                    return false;
                }
                columnCount++;
            }

            if (columnCount != width) return false;
            lineCount++;
        }

        return lineCount == height;
    }
    catch (const std::exception&) {
        return false;
    }
}

bool FileHandler::validateCellsFormat(const std::string& content) {
    std::istringstream iss(content);
    std::string line;

    while (std::getline(iss, line)) {
        if (line.empty() || line[0] == '!') continue;

        for (char c : line) {
            if (c != '.' && c != 'O' && c != '*') {
                return false;
            }
        }
    }

    return true;
}