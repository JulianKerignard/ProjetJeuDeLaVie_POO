#include "../Headers/RleReader.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

void RLEReader::loadFromFile(const std::string& filename, Grid& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open RLE file: " + filename);
    }

    int patternWidth = 0, patternHeight = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line[0] == 'x') {
            std::regex header_regex("x\\s*=\\s*(\\d+)\\s*,\\s*y\\s*=\\s*(\\d+)");
            std::smatch matches;
            if (std::regex_search(line, matches, header_regex)) {
                patternWidth = std::stoi(matches[1]);
                patternHeight = std::stoi(matches[2]);
                std::cout << "Pattern width: " << patternWidth << ", height: " << patternHeight << "\n"; // Debug
            }
            break;
        }
    }

    int startX = (grid.getWidth() - patternWidth) / 2;
    int startY = (grid.getHeight() - patternHeight) / 2;

    std::stringstream dataStream;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#' || line[0] == 'x') continue;
        dataStream << line;
    }

    int x = startX, y = startY;
    std::string count;

    for (char c : dataStream.str()) {
        if (std::isdigit(c)) {
            count += c;
            continue;
        }

        int repeat = count.empty() ? 1 : std::stoi(count);
        count.clear();

        switch (c) {
            case 'o':
                for (int i = 0; i < repeat; ++i) {
                    if (x >= 0 && x < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
                        grid.setCellAt(x, y, CellState::ALIVE);
                        std::cout << "Setting cell (" << x << ", " << y << ") to ALIVE\n"; // Debug
                    }
                    x++;
                }
                break;
            case 'b':
                x += repeat;
                break;
            case '$':
                y += repeat;
                x = startX;
                break;
            case '!':
                return;
            default:
                throw std::runtime_error("Unexpected character in RLE file: " + std::string(1, c));
        }
    }
}

Grid RLEReader::loadFromFile(const std::string& filename) {
    Grid grid(10, 10);
    loadFromFile(filename, grid);
    return grid;
}
