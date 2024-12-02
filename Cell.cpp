#include "Cell.h"
#include "Grid.h"

Cell::Cell(bool state, int x, int y) 
    : isAlive(state), isObstacle(false), x(x), y(y) {}

bool Cell::getState() const {
    return isAlive;
}

void Cell::setState(bool state) {
    isAlive = state;
}

int Cell::getNeighborsCount(Grid& grid) {
    int count = 0;
    // Implémentation du comptage des voisins vivants
    // Vous devrez adapter cette méthode selon votre implémentation
    return count;
}

void Cell::evolve(Grid& grid) {
    // Implémentation des règles du Jeu de la Vie
    // Selon le nombre de voisins, la cellule change d'état
}