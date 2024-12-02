#pragma once
#include <string>
#include "Grid.h"
#include "GameManager.h"

class GameManager {
private:
    Grid gameGrid;
    int maxIterations;
    bool toroidalMode;
    GameManager gameManager;

public:
    GameManager(const std::string& inputFile);

    void runConsoleMode();
    void runGraphicalMode();
    void saveIteration(int iterationNumber);
};