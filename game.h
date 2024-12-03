#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "FileHandler.h"
#include "DisplayManager.h"
#include <memory>

enum class DisplayMode {
    CONSOLE,
    GRAPHICAL
};

class Game {
private:
    Grid grid;
    std::unique_ptr<DisplayManager> displayManager;
    int iterationCount;
    bool isRunning;
    int iterationDelay;

public:
    Game(const std::string& filePath, DisplayMode mode);
    void run();
    void pause();
    void resume();
    void setIterationDelay(int ms);
    int getCurrentIteration() const;
};

#endif // GAME_H