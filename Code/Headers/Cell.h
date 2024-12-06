#ifndef CELL_H
#define CELL_H

enum class CellState {
    DEAD,
    ALIVE,
    OBSTACLE
};

class Cell {
private:
    CellState currentState;
    CellState nextState;
    bool isObstacle;

public:
    Cell(CellState initialState = CellState::DEAD);
    void updateState();
    CellState getCurrentState() const;
    void setNextState(CellState state);
    void setObstacle(bool obstacle);
    bool isObstacleCell() const;
};

#endif // CELL_H