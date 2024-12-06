#ifndef RLE_READER_H
#define RLE_READER_H

#include "Grid.h"
#include <string>

class RLEReader {
public:
    static Grid loadFromFile(const std::string& filename);
    static void loadFromFile(const std::string& filename, Grid& grid);
};

#endif // RLE_READER_H