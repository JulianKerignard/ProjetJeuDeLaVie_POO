#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include "DisplayManager.h"
#include <fstream>

class ConsoleDisplay : public DisplayManager {
private:
    int iterationCounter;
    std::ofstream outputFile;

public:
    ConsoleDisplay();
    void initialize() override;
    void update(const Grid& grid) override;
    void close() override;
};

#endif // CONSOLE_DISPLAY_H
