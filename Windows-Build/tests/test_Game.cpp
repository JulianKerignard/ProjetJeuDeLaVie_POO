#include "gtest/gtest.h"
#include "Game.h"
#include <fstream>

// Helper function to create a temporary configuration file
void createTempConfigFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

TEST(GameTest, ConstructorWithStandardFile) {
    std::string filename = "temp_config.txt";
    std::string content = "5 5\n0 1 0 0 0\n0 0 0 0 0\n0 0 2 0 0\n0 0 0 0 0\n0 0 0 0 0\n";
    createTempConfigFile(filename, content);

    Game game(filename, DisplayMode::CONSOLE, FileType::STANDARD);
    EXPECT_EQ(game.getCurrentIteration(), 0);
    EXPECT_FALSE(game.isGameRunning());

    std::remove(filename.c_str());
}

TEST(GameTest, ConstructorWithRLEFile) {
    std::string filename = "temp_config.rle";
    std::string content = "#N Glider\n#O Richard K. Guy\n#C A small spaceship that moves diagonally.\n#C The smallest, most common, and first discovered spaceship.\n#C www.conwaylife.com/wiki/index.php?title=Glider\nx = 3, y = 3, rule = B3/S23\nbo$2bo$3o!";
    createTempConfigFile(filename, content);

    Game game(filename, DisplayMode::CONSOLE, FileType::RLE);
    EXPECT_EQ(game.getCurrentIteration(), 0);
    EXPECT_FALSE(game.isGameRunning());

    std::remove(filename.c_str());
}

TEST(GameTest, ConstructorWithDimensions) {
    std::string filename = "temp_config.txt";
    std::string content = "5 5\n0 1 0 0 0\n0 0 0 0 0\n0 0 2 0 0\n0 0 0 0 0\n0 0 0 0 0\n";
    createTempConfigFile(filename, content);

    Game game(filename, DisplayMode::CONSOLE, FileType::STANDARD, 5, 5);
    EXPECT_EQ(game.getCurrentIteration(), 0);
    EXPECT_FALSE(game.isGameRunning());

    std::remove(filename.c_str());
}

TEST(GameTest, SetIterationDelay) {
    std::string filename = "temp_config.txt";
    std::string content = "5 5\n0 1 0 0 0\n0 0 0 0 0\n0 0 2 0 0\n0 0 0 0 0\n0 0 0 0 0\n";
    createTempConfigFile(filename, content);

    Game game(filename, DisplayMode::CONSOLE, FileType::STANDARD);
    game.setIterationDelay(200.0f);
    EXPECT_EQ(game.getIterationDelay(), 200.0f);

    std::remove(filename.c_str());
}

TEST(GameTest, UpdateIterationDelay) {
    std::string filename = "temp_config.txt";
    std::string content = "5 5\n0 1 0 0 0\n0 0 0 0 0\n0 0 2 0 0\n0 0 0 0 0\n0 0 0 0 0\n";
    createTempConfigFile(filename, content);

    Game game(filename, DisplayMode::CONSOLE, FileType::STANDARD);
    game.setIterationDelay(200.0f);
    game.updateIterationDelay(50.0f);
    EXPECT_EQ(game.getIterationDelay(), 250.0f);

    std::remove(filename.c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}