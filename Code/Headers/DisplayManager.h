#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "Grid.h"

class DisplayManager {
public:
    virtual ~DisplayManager() = default;
    virtual void initialize() = 0;
    virtual void update(const Grid& grid) = 0;
    virtual void close() = 0;
};

#endif // DISPLAY_MANAGER_H