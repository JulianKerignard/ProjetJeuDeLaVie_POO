//
// Created by jujuk on 2024-12-02.
//

#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <fstream>

class Grille {
private:
    int lignes;
    int colonnes;
    std::vector<std::vector<int>> cellules;

    int compterVoisinsVivants(int x, int y) const {
        int voisinsVivants = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Ignorer la cellule elle-même
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes) {
                    voisinsVivants += cellules[nx][ny];
                }
            }
        }
        return voisinsVivants;
    }

public:
    Grille(int l, int c) : lignes(l), colonnes(c), cellules(l, std::vector<int>(c, 0)) {}

    void chargerDepuisFichier(const std::string& nomFichier) {
        std::ifstream fichier(nomFichier);
        if (!fichier.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier : " + nomFichier);
        }

        fichier >> lignes >> colonnes;
        cellules.resize(lignes, std::vector<int>(colonnes));

        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                fichier >> cellules[i][j];
            }
        }

        fichier.close();
    }

    void afficherGrille() const {
        for (const auto& ligne : cellules) {
            for (int cellule : ligne) {
                std::cout << (cellule ? "1 " : "0 ");
            }
            std::cout << "\n";
        }
    }

    void nouvelleGeneration() {
        std::vector<std::vector<int>> nouvelleGrille = cellules;

        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                int voisinsVivants = compterVoisinsVivants(i, j);
                if (cellules[i][j] == 1) { // Cellule vivante
                    nouvelleGrille[i][j] = (voisinsVivants == 2 || voisinsVivants == 3) ? 1 : 0;
                } else { // Cellule morte
                    nouvelleGrille[i][j] = (voisinsVivants == 3) ? 1 : 0;
                }
            }
        }

        cellules = nouvelleGrille;
    }
};



#endif //GRID_H
