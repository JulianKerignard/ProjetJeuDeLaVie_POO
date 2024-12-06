#include "gtest/gtest.h"
#include "GraphicalDisplay.h"
#include "Grid.h"

class GraphicalDisplayTest : public ::testing::Test {
protected:
    GraphicalDisplay* display;
    Grid* grid;

    void SetUp() override {
        display = new GraphicalDisplay(800, 600);
        grid = new Grid(10, 10);
        display->setGrid(grid);
    }

    void TearDown() override {
        delete display;
        delete grid;
    }
};

TEST_F(GraphicalDisplayTest, Initialization) {
    EXPECT_NO_THROW(display->initialize());
}

TEST_F(GraphicalDisplayTest, WindowOpen) {
    display->initialize();
    EXPECT_TRUE(display->isWindowOpen());
}

TEST_F(GraphicalDisplayTest, SetIterationDelay) {
    display->setIterationDelay(100.0f);
    EXPECT_EQ(display->getIterationSpeed(), 100.0f);

    display->setIterationDelay(2000.0f); // Should be clamped to 1000.0f
    EXPECT_EQ(display->getIterationSpeed(), 1000.0f);

    display->setIterationDelay(30.0f); // Should be clamped to 50.0f
    EXPECT_EQ(display->getIterationSpeed(), 50.0f);
}

TEST_F(GraphicalDisplayTest, TogglePause) {
    EXPECT_FALSE(display->isPaused());
    display->togglePause();
    EXPECT_TRUE(display->isPaused());
    display->togglePause();
    EXPECT_FALSE(display->isPaused());
}

TEST_F(GraphicalDisplayTest, UpdateDisplay) {
    display->initialize();
    EXPECT_NO_THROW(display->update(*grid));
}

TEST_F(GraphicalDisplayTest, CloseWindow) {
    display->initialize();
    display->close();
    EXPECT_FALSE(display->isWindowOpen());
}