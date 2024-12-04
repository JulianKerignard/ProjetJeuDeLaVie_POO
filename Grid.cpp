#include "Grid.h"
#include <stdexcept>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

Grid::Grid(int width, int height)
    : width(width), height(height), isToroidal(false) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Grid dimensions must be positive");
    }
    cells.resize(height, std::vector<Cell>(width));
}

void Grid::setCellAt(int x, int y, CellState state) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Cell coordinates out of range");
    }
    cells[y][x] = Cell(state);
}

int Grid::getValidIndex(int index, int max) const {
    if (isToroidal) {
        if (index < 0) return max - 1;
        if (index >= max) return 0;
    }
    return index;
}

int Grid::countLiveNeighbors(int x, int y) const {
    int count = 0;
    for (const auto& neighbor : getNeighbors(x, y)) {
        if (getCellAt(neighbor.first, neighbor.second).getCurrentState() == CellState::ALIVE) {
            count++;
        }
    }
    return count;
}

void Grid::updateCells() {
    auto start = std::chrono::high_resolution_clock::now();

    // Configuration du multithreading
    const int threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    const int rowsPerThread = height / threadCount;

    // Première phase : calculer les états suivants
    for (int i = 0; i < threadCount; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == threadCount - 1) ? height : (i + 1) * rowsPerThread;

        threads.emplace_back([this, startRow, endRow, i]() {
            std::cout << "Thread " << i << " traite les lignes " << startRow << " à " << endRow - 1 << std::endl;

            for (int y = startRow; y < endRow; y++) {
                for (int x = 0; x < width; x++) {
                    if (cells[y][x].isObstacleCell()) continue;

                    int liveNeighbors = countLiveNeighbors(x, y);
                    CellState currentState = cells[y][x].getCurrentState();

                    if (currentState == CellState::DEAD) {
                        if (liveNeighbors == 3) {
                            cells[y][x].setNextState(CellState::ALIVE);
                        }
                    } else if (currentState == CellState::ALIVE) {
                        if (liveNeighbors < 2 || liveNeighbors > 3) {
                            cells[y][x].setNextState(CellState::DEAD);
                        }
                    }
                }
            }
        });
    }

    // Attendre que tous les threads terminent
    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();

    // Deuxième phase : mettre à jour les états (aussi en parallèle)
    for (int i = 0; i < threadCount; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == threadCount - 1) ? height : (i + 1) * rowsPerThread;

        threads.emplace_back([this, startRow, endRow]() {
            for (int y = startRow; y < endRow; y++) {
                for (int x = 0; x < width; x++) {
                    cells[y][x].updateState();
                }
            }
        });
    }

    // Attendre que tous les threads terminent
    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Mise à jour effectuée en " << duration.count()
              << " microsecondes avec " << threadCount << " threads" << std::endl;
}

Cell& Grid::getCellAt(int x, int y) {
    if (isToroidal) {
        x = getValidIndex(x, width);
        y = getValidIndex(y, height);
    }
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Cell coordinates out of range");
    }
    return cells[y][x];
}

const Cell& Grid::getCellAt(int x, int y) const {
    return const_cast<Grid*>(this)->getCellAt(x, y);
}

void Grid::addObstacle(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Obstacle coordinates out of range");
    }
    cells[y][x].setObstacle(true);
}

std::vector<std::pair<int, int>> Grid::getNeighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;

            int newX = x + dx;
            int newY = y + dy;

            if (isToroidal) {
                newX = getValidIndex(newX, width);
                newY = getValidIndex(newY, height);
                neighbors.emplace_back(newX, newY);
            } else if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                neighbors.emplace_back(newX, newY);
            }
        }
    }
    return neighbors;
}

void Grid::addPattern(Pattern pattern, int x, int y) {
    switch (pattern) {
        case Pattern::GLIDER:
            if (x + 2 < width && y + 2 < height) {
                setCellAt(x + 1, y, CellState::ALIVE);
                setCellAt(x + 2, y + 1, CellState::ALIVE);
                setCellAt(x, y + 2, CellState::ALIVE);
                setCellAt(x + 1, y + 2, CellState::ALIVE);
                setCellAt(x + 2, y + 2, CellState::ALIVE);
            }
            break;
        case Pattern::BLINKER:
            if (x + 2 < width && y < height) {
                setCellAt(x, y, CellState::ALIVE);
                setCellAt(x + 1, y, CellState::ALIVE);
                setCellAt(x + 2, y, CellState::ALIVE);
            }
            break;
        case Pattern::BLOCK:
            if (x + 1 < width && y + 1 < height) {
                setCellAt(x, y, CellState::ALIVE);
                setCellAt(x + 1, y, CellState::ALIVE);
                setCellAt(x, y + 1, CellState::ALIVE);
                setCellAt(x + 1, y + 1, CellState::ALIVE);
            }
            break;
        case Pattern::BEACON:
            if (x + 3 < width && y + 3 < height) {
                setCellAt(x, y, CellState::ALIVE);
                setCellAt(x + 1, y, CellState::ALIVE);
                setCellAt(x, y + 1, CellState::ALIVE);
                setCellAt(x + 3, y + 2, CellState::ALIVE);
                setCellAt(x + 2, y + 3, CellState::ALIVE);
                setCellAt(x + 3, y + 3, CellState::ALIVE);
            }
            break;
    }
}