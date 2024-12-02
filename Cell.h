#pragma once
#include <vector>

class Grid; // Forward declaration

class Cell {
private:
    bool isAlive;
    bool isObstacle;
    int x;
    int y;

public:
    Cell(bool state = false, int x = 0, int y = 0);

    bool getState();
    void setState(bool state);

    int getNeighborsCount(Grid& grid);
    void evolve(Grid& grid);
};