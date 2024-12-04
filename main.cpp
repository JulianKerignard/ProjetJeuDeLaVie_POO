#include "Game.h"
#include "RLEReader.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {
    try {
        std::string filename;
        int choice, displayChoice;
        unsigned int iterationDelay;

        // Choix du mode d'affichage
        std::cout << "Mode d'affichage:" << std::endl;
        std::cout << "1. Mode Console" << std::endl;
        std::cout << "2. Mode Graphique" << std::endl;
        std::cout << "Votre choix (1 ou 2): ";
        std::cin >> displayChoice;

        DisplayMode mode = (displayChoice == 1) ? DisplayMode::CONSOLE : DisplayMode::GRAPHICAL;

        // Menu principal
        std::cout << "\nJeu de la vie" << std::endl;
        std::cout << "1. Utiliser un fichier existant (standard)" << std::endl;
        std::cout << "2. Utiliser un fichier RLE (Mode Graphique uniquement)" << std::endl;
        std::cout << "3. Créer une nouvelle configuration" << std::endl;
        std::cout << "Votre choix (1, 2 ou 3): ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Entrez le nom du fichier (ex: init.txt): ";
            std::cin >> filename;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            Game game(filename, mode, FileType::STANDARD);
            game.setIterationDelay(iterationDelay);
            game.run();
        }
        else if (choice == 2 && mode == DisplayMode::GRAPHICAL) {
            std::cout << "Entrez le nom du fichier RLE (ex: glider.rle): ";
            std::cin >> filename;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            Game game(filename, mode, FileType::RLE);
            game.setIterationDelay(iterationDelay);
            game.run();
        }
        else if (choice == 3) {
            int width, height;
            std::cout << "Largeur de la grille: ";
            std::cin >> width;
            std::cout << "Hauteur de la grille: ";
            std::cin >> height;
            std::cout << "Entrez le délai entre les itérations (ms): ";
            std::cin >> iterationDelay;

            std::ofstream initFile("new_config.txt");
            initFile << width << " " << height << "\n";

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    bool isGlider = false;
                    int centerX = width / 2;
                    int centerY = height / 2;

                    if ((x == centerX && y == centerY-1) ||
                        (x == centerX+1 && y == centerY) ||
                        (x == centerX-1 && y == centerY+1) ||
                        (x == centerX && y == centerY+1) ||
                        (x == centerX+1 && y == centerY+1)) {
                        isGlider = true;
                    }

                    initFile << (isGlider ? "1" : "0");
                    if (x < width - 1) initFile << " ";
                }
                initFile << "\n";
            }
            initFile.close();

            Game game("new_config.txt", mode, FileType::STANDARD);
            game.setIterationDelay(iterationDelay);
            game.run();
        }
        else {
            throw std::runtime_error("Choix invalide");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Appuyez sur une touche pour quitter...";
        std::cin.get();
        std::cin.get();
        return 1;
    }
    return 0;
}