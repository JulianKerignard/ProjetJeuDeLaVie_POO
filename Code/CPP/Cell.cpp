#include "Cell.h"

Cell::Cell(CellState initialState)
    : currentState(initialState), nextState(initialState), isObstacle(false) {}

void Cell::updateState() {
    if (!isObstacle) {
        currentState = nextState;
    }
}

CellState Cell::getCurrentState() const {
    return currentState;
}

void Cell::setNextState(CellState state) {
    if (!isObstacle) {
        nextState = state;
    }
}

void Cell::setObstacle(bool obstacle) {
    isObstacle = obstacle;
    if (obstacle) {
        currentState = CellState::OBSTACLE;
        nextState = CellState::OBSTACLE;
    }
}

bool Cell::isObstacleCell() const {
    return isObstacle;
}