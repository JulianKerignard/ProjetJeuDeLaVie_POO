#include "gtest/gtest.h"
#include "RLEReader.h"
#include "Grid.h"
#include <fstream>

class RLEReaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary RLE file for testing
        std::ofstream file("test_pattern.rle");
        file << "#N Test Pattern\n";
        file << "x = 3, y = 3\n";
        file << "bo$2bo$3o!\n";
        file.close();
    }

    void TearDown() override {
        // Remove the temporary RLE file after tests
        std::remove("test_pattern.rle");
    }
};

TEST_F(RLEReaderTest, LoadFromFile) {
    Grid grid(10, 10);
    EXPECT_NO_THROW(RLEReader::loadFromFile("test_pattern.rle", grid));

    // Vérification des cellules vivantes au centre
    EXPECT_EQ(grid.getCellAt(4, 3).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(5, 4).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(3, 5).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(4, 5).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(5, 5).getCurrentState(), CellState::ALIVE);
}

TEST_F(RLEReaderTest, LoadFromFileInvalid) {
    Grid grid(10, 10);
    EXPECT_THROW(RLEReader::loadFromFile("non_existent.rle", grid), std::runtime_error);
}

TEST_F(RLEReaderTest, LoadFromFileReturnGrid) {
    Grid grid = RLEReader::loadFromFile("test_pattern.rle");

    // Vérification des cellules vivantes au centre
    EXPECT_EQ(grid.getCellAt(4, 3).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(5, 4).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(3, 5).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(4, 5).getCurrentState(), CellState::ALIVE);
    EXPECT_EQ(grid.getCellAt(5, 5).getCurrentState(), CellState::ALIVE);
}
