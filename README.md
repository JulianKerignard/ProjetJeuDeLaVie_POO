####################################################
###                                              ###
###  CREATED BY KERIGNARD JULIAN & LAGOCKI CHLOE ###
###                                              ###
####################################################


# Présentation du Projet :video_game:

Le **Jeu de la Vie** est un automate cellulaire créé par John Conway, où l'évolution d'une population de cellules se fait sur une grille à 2 dimensions. Chaque cellule peut être vivante :green_circle: ou morte :red_circle: et évolue selon des règles précises. L'objectif de ce projet est d'implémenter cet automate en utilisant la programmation orientée objet (POO) en C++ et de créer une interface graphique pour visualiser l'évolution des cellules.

## Objectifs :dart:

- Implémenter le jeu de la vie en C++ en utilisant les concepts de la programmation orientée objet.
- Lire l'état initial des cellules à partir d'un fichier.
- Implémenter un mode console :computer: pour afficher les itérations et un mode graphique :desktop: avec la bibliothèque SFML.
- Ajouter des extensions comme la gestion d'une grille torique, l'introduction de cellules obstacles, et la possibilité de placer des constructions pré-programmées.

## Structure du Projet :construction_site:

### Classes Principales :bricks:

- **Cellule :**
    - Attributs :
        - `bool vivant` : état de la cellule (vivante :green_circle: ou morte :red_circle:).
        - `int x, y` : coordonnées de la cellule sur la grille.
    - Méthodes :
        - `void changerEtat()` : change l'état de la cellule (vivante :green_circle: ou morte :red_circle:).
        - `int compterVoisins(const Grille&)` : compte le nombre de voisins vivants d'une cellule.

- **Grille :**
    - Attributs :
        - `Cellule[][]` : une matrice de cellules.
        - `int largeur, hauteur` : dimensions de la grille.
    - Méthodes :
        - `void initialiserGrille()` : initialise la grille à partir d'un fichier.
        - `void afficherGrille()` : affiche la grille dans la console.
        - `void calculerNouvelEtat()` : calcule le nouvel état de chaque cellule en fonction des règles du jeu.
        - `void mettreAJour()` : met à jour la grille après chaque itération.

- **JeuDeLaVie :**
    - Attributs :
        - `Grille grille` : instance de la grille.
        - `int nbIterations` : nombre d'itérations à effectuer.
    - Méthodes :
        - `void lancerJeu()` : lance le jeu avec les itérations.
        - `void afficherEtat()` : affiche l'état de la grille à chaque itération.
        - `void genererFichierSortie()` : génère un fichier de sortie avec les résultats du jeu.

### Extensions :rocket:

- **Grille Torique :** 
    - Les bords de la grille sont connectés, chaque cellule du bord a des voisins de l'autre côté.

- **Cellules Obstacle :**
    - Ces cellules restent dans un état fixe, et n'évoluent pas.

- **Constructions Pré-programmées :**
    - Des motifs spécifiques peuvent être ajoutés à la grille pendant l'exécution via des touches du clavier.

- **Parallélisation :**
    - Utilisation d'OpenMP ou des threads pour calculer les états des cellules en parallèle.

## Fonctionnement du Programme :robot:

### Entrée :file_folder:

Le programme lit un fichier contenant les dimensions de la grille suivies de l'état des cellules. Le format du fichier est le suivant :

5 10 
0 0 1 0 0
0 0 0 0 0 
0 0 0 1 0
0 0 0 0 0
0 1 1 1 0

### Mode Console :computer:

- Affichage de l'état de la grille à chaque itération dans la console.
- Génération d'un fichier de sortie avec l'état de la grille pour chaque itération.

### Mode Graphique :desktop:

- Affichage de la grille sous forme graphique avec SFML.
- La grille est mise à jour à chaque itération et affichée à l'écran.
- L'utilisateur peut contrôler la vitesse de l'itération.

## Compilation et Exécution :tools:

### Prérequis :clipboard:

- C++11 ou supérieur.
- SFML pour l'interface graphique.
- CMake pour la gestion de la compilation.

### Instructions de Compilation :robot:

1. Clonez le repository Git.
2. Créez un dossier de compilation :
   ```bash
   mkdir build
   cd build
   ```
