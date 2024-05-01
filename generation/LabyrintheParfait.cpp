#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "../listes/listes.cpp"

using namespace std;


void LabyrintheParfait(vector<vector<bool>>& matrice_adjacence, int taille, int entreX, int entreY) {
    int posX = 0;
    int posY = 0;
    int comptalea = 0;
    vector<vector<bool>> visite(taille, vector<bool>(taille, false));
    std::vector<int> cellules;
    visite[entreX][entreY] = true;
    liste pile;

    ajouterTete(pile, taille * entreY + entreX); // Utilisation d'un identifiant unique pour les coordonnées

    while (!estVide(pile)) {
        auto coord = retirerTete(pile);
        posX = coord % taille; // Récupération de la coordonnée X à partir de l'identifiant unique
        posY = coord / taille; // Récupération de la coordonnée Y à partir de l'identifiant unique

        cellules.clear();
        comptalea = 0;

        if (posY - 1 >= 0 && !visite[posX][posY - 1]) {
            cellules.push_back(taille * (posY - 1) + posX); // Ajout d'un identifiant unique
            comptalea++;
        }

        if (posY + 1 < taille && !visite[posX][posY + 1]) {
            cellules.push_back(taille * (posY + 1) + posX); // Ajout d'un identifiant unique
            comptalea++;
        }

        if (posX - 1 >= 0 && !visite[posX - 1][posY]) {
            cellules.push_back(taille * posY + posX - 1); // Ajout d'un identifiant unique
            comptalea++;
        }

        if (posX + 1 < taille && !visite[posX + 1][posY]) {
            cellules.push_back(taille * posY + posX + 1); // Ajout d'un identifiant unique
            comptalea++;
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cellules.begin(), cellules.end(), g);

        cout << endl;
        for (const auto& nextCoord : cellules) {
            int nextX = nextCoord % taille; // Récupération de la coordonnée X à partir de l'identifiant unique
            int nextY = nextCoord / taille; // Récupération de la coordonnée Y à partir de l'identifiant unique
            matrice_adjacence[taille * posY + posX][nextCoord] = true;
            matrice_adjacence[nextCoord][taille * posY + posX] = true;
            visite[nextX][nextY] = true;
            ajouterTete(pile, nextCoord);
        }
        Sleep(10);
        system("clear");
        AfficheDonjon(matrice_adjacence, taille);
    }

    AfficheDonjon(matrice_adjacence, taille);
}
