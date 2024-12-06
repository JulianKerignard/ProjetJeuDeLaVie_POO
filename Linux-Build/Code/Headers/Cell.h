#ifndef CELL_H
#define CELL_H

enum class CellState {
    ALIVE,
    DEAD,
    OBSTACLE
};

class Cell {
public:
    Cell();  // Default constructor
    Cell(CellState initialState);

    void updateState();
    CellState getCurrentState() const;
    void setNextState(CellState state);
    void setObstacle(bool obstacle);
    bool isObstacleCell() const;

private:
    CellState currentState;
    CellState nextState;
    bool isObstacle;
};

#endif // CELL_H