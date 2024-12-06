#include <gtest/gtest.h>
#include "Cell.h"

TEST(CellTest, DefaultState) {
    Cell cell;
    EXPECT_EQ(cell.getCurrentState(), CellState::DEAD);
    EXPECT_FALSE(cell.isObstacleCell());
}

TEST(CellTest, SetAndGetState) {
    Cell cell;
    cell.setNextState(CellState::ALIVE);
    cell.updateState();
    EXPECT_EQ(cell.getCurrentState(), CellState::ALIVE);
    cell.setNextState(CellState::DEAD);
    cell.updateState();
    EXPECT_EQ(cell.getCurrentState(), CellState::DEAD);
}

TEST(CellTest, ObstacleCell) {
    Cell cell;
    cell.setObstacle(true);
    EXPECT_TRUE(cell.isObstacleCell());
    cell.setObstacle(false);
    EXPECT_FALSE(cell.isObstacleCell());
}