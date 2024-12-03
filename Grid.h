#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"

enum class Pattern {
    GLIDER,
    BLINKER,
    BLOCK,
    BEACON
};

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int width;
    int height;
    bool isToroidal;

    int getValidIndex(int index, int max) const;
    int countLiveNeighbors(int x, int y) const;

public:
    Grid(int width, int height);
    void updateCells();
    Cell& getCellAt(int x, int y);
    const Cell& getCellAt(int x, int y) const;
    void setCellAt(int x, int y, CellState state);
    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const;
    void setToroidal(bool enabled);
    void addObstacle(int x, int y);
    void addPattern(Pattern pattern, int x, int y);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif // GRID_H