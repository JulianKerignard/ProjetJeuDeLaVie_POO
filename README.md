####################################################
###                                              ###
###  CREATED BY KERIGNARD JULIAN & LAGOCKI CHLOE ###
###                                              ###
####################################################


###DOCUMENTATION

Wev Documentation : In Dev.....

Text Documentation : https://github.com/JulianKerignard/ProjetJeuDeLaVie_POO/wiki

## 1. **Présentation du Projet**
Le **Jeu de la Vie** est un automate cellulaire créé par John Conway, où l'évolution d'une population de cellules se fait sur une grille à 2 dimensions. Chaque cellule peut être vivante ou morte et évolue selon des règles précises. L'objectif de ce projet est d'implémenter cet automate en utilisant la programmation orientée objet (POO) en C++ et de créer une interface graphique pour visualiser l'évolution des cellules.

## 2. **Objectifs**
- Implémenter le jeu de la vie en C++ en utilisant les concepts de la programmation orientée objet.
- Lire l'état initial des cellules à partir d'un fichier.
- Implémenter un mode console pour afficher les itérations et un mode graphique avec la bibliothèque SFML.
- Ajouter des extensions comme la gestion d'une grille torique, l'introduction de cellules obstacles, et la possibilité de placer des constructions pré-programmées.

## 3. **Structure du Projet**

### 3.1 **Classes Principales**
- **Cellule :**
    - Attributs :
        - `bool vivant` : état de la cellule (vivante ou morte).
        - `int x, y` : coordonnées de la cellule sur la grille.
    - Méthodes :
        - `void changerEtat()` : change l'état de la cellule (vivante ou morte).
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

### 3.2 **Extensions**
- **Grille Torique :**
    - Les bords de la grille sont connectés, chaque cellule du bord a des voisins de l'autre côté.

- **Cellules Obstacle :**
    - Ces cellules restent dans un état fixe, vivant ou mort, et n'évoluent pas.

- **Constructions Pré-programmées :**
    - Des motifs spécifiques peuvent être ajoutés à la grille pendant l'exécution via des touches du clavier.

- **Parallélisation :**
    - Utilisation d'OpenMP ou des threads pour calculer les états des cellules en parallèle.

## 4. **Fonctionnement du Programme**

### 4.1 **Entrée**
Le programme lit un fichier contenant les dimensions de la grille suivies de l'état des cellules. Le format du fichier est le suivant :

5 10 
0 0 1 0 0
0 0 0 0 0 
0 0 0 1 0
0 0 0 0 0
0 1 1 1 0


### 4.2 **Mode Console**
- Affichage de l'état de la grille à chaque itération dans la console.
- Génération d'un fichier de sortie avec l'état de la grille pour chaque itération.

### 4.3 **Mode Graphique**
- Affichage de la grille sous forme graphique avec SFML.
- La grille est mise à jour à chaque itération et affichée à l'écran.
- L'utilisateur peut contrôler la vitesse de l'itération.

## 6. **Compilation et Exécution**

### 6.1 **Prérequis**
- C++11 ou supérieur.
- SFML pour l'interface graphique.
- CMake pour la gestion de la compilation.

### 6.2 **Instructions de Compilation**
1. Clonez le repository Git.
2. Créez un dossier de compilation :
   ```bash
   mkdir build
   cd build
   
