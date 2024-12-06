#include "gtest/gtest.h"
#include "DisplayManager.h"
#include "Grid.h"

class TestDisplayManager : public DisplayManager {
public:
    bool initialized = false;
    bool updated = false;
    bool closed = false;

    void initialize() override {
        initialized = true;
    }

    void update(const Grid& grid) override {
        updated = true;
    }

    void close() override {
        closed = true;
    }
};

class DisplayManagerTest : public ::testing::Test {
protected:
    TestDisplayManager* displayManager;
    Grid* grid;

    void SetUp() override {
        displayManager = new TestDisplayManager();
        grid = new Grid(10, 10);
    }

    void TearDown() override {
        delete displayManager;
        delete grid;
    }
};

TEST_F(DisplayManagerTest, Initialization) {
    displayManager->initialize();
    EXPECT_TRUE(displayManager->initialized);
}

TEST_F(DisplayManagerTest, UpdateDisplay) {
    displayManager->update(*grid);
    EXPECT_TRUE(displayManager->updated);
}

TEST_F(DisplayManagerTest, CloseDisplay) {
    displayManager->close();
    EXPECT_TRUE(displayManager->closed);
}