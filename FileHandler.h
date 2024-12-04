#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include "Grid.h"

class FileHandler {
public:
    static Grid loadGridFromFile(const std::string& path);
    static void loadGridFromFile(const std::string& path, Grid& grid);
    static void saveGridToFile(const Grid& grid, const std::string& path);

private:
    static std::pair<int, int> parseGridDimensions(const std::string& line);
    static bool validateFileFormat(const std::string& content);
};

#endif // FILE_HANDLER_H