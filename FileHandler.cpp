#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

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
            grid.setCellAt(x, y, state ? CellState::ALIVE : CellState::DEAD);
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
            file << (grid.getCellAt(x, y).getCurrentState() == CellState::ALIVE ? "1" : "0");
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
    // TODO: Implement file format validation
    return true;
}