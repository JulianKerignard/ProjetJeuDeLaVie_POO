#include "GameManager.h"
#include <iostream>

int main() {
    try {
        GameManager gameManager("input.txt");
        // Mode console ou graphique selon le choix
        // game.runConsoleMode();
        gameManager.runGraphicalMode();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
}