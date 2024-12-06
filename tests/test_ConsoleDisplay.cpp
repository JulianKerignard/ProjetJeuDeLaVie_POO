#include "gtest/gtest.h"
#include "ConsoleDisplay.h"
#include "Grid.h"

class ConsoleDisplayTest : public ::testing::Test {
protected:
    ConsoleDisplay* display;
    Grid* grid;

    void SetUp() override {
        display = new ConsoleDisplay();
        grid = new Grid(10, 10);
    }

    void TearDown() override {
        delete display;
        delete grid;
    }
};

TEST_F(ConsoleDisplayTest, Initialization) {
    EXPECT_NO_THROW(display->initialize());
}

TEST_F(ConsoleDisplayTest, UpdateDisplay) {
    display->initialize();
    EXPECT_NO_THROW(display->update(*grid));
}

TEST_F(ConsoleDisplayTest, CloseDisplay) {
    display->initialize();
    EXPECT_NO_THROW(display->close());
}