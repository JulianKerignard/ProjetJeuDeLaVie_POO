#pragma once
#include <vector>
#include <string>
#include "Cell.h"

class Grid {
private:
    int rows;
    int columns;
    std::vector<std::vector<Cell>> cells;

public:
    Grid(int rows, int columns);

    bool loadFromFile(const std::string& filename);
    void updateGrid();

    Cell& getCell(int x, int y);

    void displayConsole();
    void displayGraphical();

    int getRows() const { return rows; }
    int getColumns() const { return columns; }
};