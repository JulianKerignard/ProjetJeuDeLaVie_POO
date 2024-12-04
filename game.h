#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "FileHandler.h"
#include "RLEReader.h"
#include "DisplayManager.h"
#include <memory>

enum class DisplayMode {
    CONSOLE,
    GRAPHICAL
};

enum class FileType {
    STANDARD,
    RLE
};

class Game {
private:
    Grid grid;
    std::unique_ptr<DisplayManager> displayManager;
    int iterationCount;
    bool isRunning;
    int iterationDelay;

    void initializeDisplay(DisplayMode mode);

public:
    Game(const std::string& filePath, DisplayMode mode); // Constructeur original
    Game(const std::string& filePath, DisplayMode mode, FileType fileType); // Nouveau constructeur simple
    Game(const std::string& filePath, DisplayMode mode, FileType fileType, int width, int height); // Constructeur avec dimensions
    void run();
    void pause();
    void resume();
    void setIterationDelay(int ms);
    int getCurrentIteration() const;
};

#endif // GAME_H