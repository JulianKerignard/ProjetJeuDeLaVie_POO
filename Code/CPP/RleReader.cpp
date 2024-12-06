#include "RLEReader.h"
#include <fstream>
#include <sstream>
#include <regex>

void RLEReader::loadFromFile(const std::string& filename, Grid& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open RLE file: " + filename);
    }

    // Lire le fichier une première fois pour obtenir les dimensions du motif
    int patternWidth = 0, patternHeight = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line[0] == 'x') {
            // Extraire les dimensions du motif RLE
            std::regex header_regex("x\\s*=\\s*(\\d+)\\s*,\\s*y\\s*=\\s*(\\d+)");
            std::smatch matches;
            if (std::regex_search(line, matches, header_regex)) {
                patternWidth = std::stoi(matches[1]);
                patternHeight = std::stoi(matches[2]);
            }
            break;
        }
    }

    // Calculer la position centrale pour le motif
    int startX = (grid.getWidth() - patternWidth) / 2;
    int startY = (grid.getHeight() - patternHeight) / 2;

    // Revenir au début du fichier et ignorer l'en-tête
    file.clear();
    file.seekg(0);
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#' || line[0] == 'x') continue;
        break;
    }

    int x = startX, y = startY;
    std::string count;

    for (char c : line) {
        if (std::isdigit(c)) {
            count += c;
            continue;
        }

        int repeat = count.empty() ? 1 : std::stoi(count);
        count.clear();

        switch (c) {
            case 'o': // Live cell
                for (int i = 0; i < repeat && x < grid.getWidth(); i++) {
                    if (x >= 0 && x < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
                        grid.setCellAt(x, y, CellState::ALIVE);
                    }
                    x++;
                }
                break;
            case 'b': // Dead cell
                x += repeat;
                break;
            case '$': // End of line
                y += repeat;
                x = startX;
                break;
            case '!': // End of pattern
                return;
        }
    }
}

Grid RLEReader::loadFromFile(const std::string& filename) {
    // Création d'une grille avec les dimensions par défaut
    Grid grid(350, 350);
    loadFromFile(filename, grid);
    return grid;
}