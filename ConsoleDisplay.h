#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include "DisplayManager.h"

class ConsoleDisplay : public DisplayManager {
public:
    void initialize() override;
    void update(const Grid& grid) override;
    void close() override;
};

#endif // CONSOLE_DISPLAY_H