#include "Game.h"
#include <iostream>
#include <fstream>

int main() {
    try {
        // Créer un fichier de test initial "init.txt"
        std::ofstream initFile("init.txt");
        initFile << "10000 10000\n";  // Grille plus grande pour mieux voir

        // Créer un planeur
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                if ((x == 1 && y == 2) ||
                    (x == 2 && y == 3) ||
                    (x == 0 && y == 3) ||
                    (x == 1 && y == 3) ||
                    (x == 1 && y == 1)) {
                    initFile << "1 ";
                    } else {
                        initFile << "0 ";
                    }
            }
            initFile << "\n";
        }
        initFile.close();

        // Lancer le jeu en mode graphique
        Game game("init.txt", DisplayMode::GRAPHICAL);
        game.setIterationDelay(100);  // 100ms entre chaque itération
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}