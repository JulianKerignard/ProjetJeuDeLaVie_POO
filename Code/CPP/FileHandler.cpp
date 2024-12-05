#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void FileHandler::loadGridFromFile(const std::string& path, Grid& grid) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    std::string line;
    std::getline(file, line);  // Read dimensions line
    auto [width, height] = parseGridDimensions(line);

    // Vérifier que les dimensions correspondent
    if (width != grid.getWidth() || height != grid.getHeight()) {
        throw std::runtime_error("File dimensions do not match grid dimensions");
    }

    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        std::istringstream iss(line);
        for (int x = 0; x < width; x++) {
            int state;
            iss >> state;
            if (state == 2) {
                grid.addObstacle(x, y);
            } else {
                grid.setCellAt(x, y, state ? CellState::ALIVE : CellState::DEAD);
            }
        }
    }
}

Grid FileHandler::loadGridFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    std::string line;
    std::getline(file, line);
    auto [width, height] = parseGridDimensions(line);

    Grid grid(width, height);

    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        std::istringstream iss(line);
        for (int x = 0; x < width; x++) {
            int state;
            iss >> state;
            if (state == 2) {
                grid.addObstacle(x, y);
            } else {
                grid.setCellAt(x, y, state ? CellState::ALIVE : CellState::DEAD);
            }
        }
    }

    return grid;
}

void FileHandler::saveGridToFile(const Grid& grid, const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + path);
    }

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
}

std::pair<int, int> FileHandler::parseGridDimensions(const std::string& line) {
    std::istringstream iss(line);
    int width, height;
    if (!(iss >> width >> height) || width <= 0 || height <= 0) {
        throw std::runtime_error("Invalid grid dimensions in file");
    }
    return {width, height};
}

bool FileHandler::validateFileFormat(const std::string& content) {
    std::istringstream iss(content);
    std::string firstLine;

    // Vérifier la première ligne (dimensions)
    if (!std::getline(iss, firstLine)) {
        return false;
    }

    try {
        auto [width, height] = parseGridDimensions(firstLine);

        // Vérifier les lignes suivantes
        std::string line;
        int lineCount = 0;
        while (std::getline(iss, line) && lineCount < height) {
            std::istringstream lineStream(line);
            int value;
            int columnCount = 0;

            while (lineStream >> value && columnCount < width) {
                if (value != 0 && value != 1 && value != 2) {  // Ajout de la vérification pour 2
                    return false;
                }
                columnCount++;
            }

            if (columnCount != width) {
                return false;
            }

            lineCount++;
        }

        return lineCount == height;
    }
    catch (const std::exception&) {
        return false;
    }
}