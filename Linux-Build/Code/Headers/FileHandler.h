#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "Grid.h"
#include <string>
#include <utility>
#include <vector>

enum class FileFormat {
    TXT,
    CELLS,
    UNKNOWN
};

class FileHandler {
private:
    static const int DEFAULT_CELLS_WIDTH;   // Largeur par défaut pour les .cells
    static const int DEFAULT_CELLS_HEIGHT;  // Hauteur par défaut pour les .cells

    // Méthodes privées de gestion des formats
    static FileFormat getFileFormat(const std::string& path);
    static Grid loadTxtFile(const std::string& path);
    static Grid loadCellsFile(const std::string& path);
    static std::pair<int, int> parseGridDimensions(const std::string& line);
    static bool validateTxtFormat(const std::string& content);
    static bool validateCellsFormat(const std::string& content);

public:
    // Méthodes principales de chargement et sauvegarde
    static Grid loadGridFromFile(const std::string& path);
    static void loadGridFromFile(const std::string& path, Grid& grid);
    static void saveGridToFile(const Grid& grid, const std::string& path);

    // Méthodes de chargement spécifiques publiques
    static void loadTxtFile(const std::string& path, Grid& grid);
    static void loadCellsFile(const std::string& path, Grid& grid);

    // New public method
    bool validateFileFormat(const std::string& content);
};

#endif // FILE_HANDLER_H