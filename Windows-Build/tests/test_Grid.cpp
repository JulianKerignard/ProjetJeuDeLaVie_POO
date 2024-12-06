#include "gtest/gtest.h"
#include "Grid.h"

TEST(GridTest, Constructor) {
    Grid grid(10, 10);
    EXPECT_EQ(grid.getWidth(), 10);
    EXPECT_EQ(grid.getHeight(), 10);
    EXPECT_FALSE(grid.getToroidal());
}

TEST(GridTest, SetAndGetCell) {
    Grid grid(10, 10);
    grid.setCellAt(1, 1, CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(1, 1).getCurrentState(), CellState::ALIVE);
    grid.setCellAt(1, 1, CellState::DEAD);
    EXPECT_EQ(grid.getCellAt(1, 1).getCurrentState(), CellState::DEAD);
}

/*
TEST(GridTest, ToroidalBehavior) {
    Grid grid(10, 10);
    grid.setToroidal(true);
    grid.setCellAt(0, 0, CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(9, 9).getCurrentState(), CellState::ALIVE); // Wrap around to the opposite corner
    EXPECT_EQ(grid.getCellAt(0, 0).getCurrentState(), CellState::ALIVE); // Original position
}
*/

TEST(GridTest, AddObstacle) {
    Grid grid(10, 10);
    grid.addObstacle(2, 2);
    EXPECT_TRUE(grid.getCellAt(2, 2).isObstacleCell());
}

TEST(GridTest, AddPattern) {
    Grid grid(10, 10);
    grid.addPattern(Pattern::GLIDER, 1, 1);
    EXPECT_EQ(grid.getCellAt(2, 1).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(3, 2).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(1, 3).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(2, 3).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(3, 3).getCurrentState(), CellState::ALIVE);
}
/*
TEST(GridTest, UpdateCells) {
    Grid grid(5, 5);
    grid.setCellAt(1, 0, CellState::ALIVE);
    grid.setCellAt(2, 1, CellState::ALIVE);
    grid.setCellAt(0, 2, CellState::ALIVE);
    grid.setCellAt(1, 2, CellState::ALIVE);
    grid.setCellAt(2, 2, CellState::ALIVE);
    grid.updateCells();
    EXPECT_EQ(grid.getCellAt(1, 1).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(2, 2).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(1, 2).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(2, 1).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(0, 1).getCurrentState(), CellState::ALIVE);
}
*/