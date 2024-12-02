#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>

#include "Grid.h"

Grille{}();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <fichier d'entree>\n";
        return 1;
    }

    std::string nomFichier = argv[1];

    try {
        Grille grille(0, 0);
        grille.chargerDepuisFichier(nomFichier);

        std::cout << "État initial :\n";
        Grille::afficherGrille();

        const int iterations = 10; // Modifier si besoin
        for (int iter = 0; iter < iterations; ++iter) {
            std::cout << "\nIteration " << iter + 1 << " :\n";
            grille.nouvelleGeneration();
            grille.afficherGrille();
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
        return 1;
    }

    return 0;
}
