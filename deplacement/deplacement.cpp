#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "../listes/listes.cpp"

using namespace std;

visibilite(vector<vector<bool>>& matrice_adjacence, int taille, int entreX, int entreY) {
	int cellule = (entreX + entreY * taille);
	vector<bool>vue(taille * taille, false);
	vue[cellule]=true
    //sud
    while (cellule - taille >= 0 && matrice_adjacence[cellule][cellule-taille]) {
        cellule = cellule - taille;
        vue[cellule] = true
    }
    //nord
    while (cellule + taille < taille * taille && matrice_adjacence[cellule][cellule + taille]) {
        cellule = cellule + taille;
        vue[cellule] = true
    }
    //ouest
    while (cellule % taille != 0 && matrice_adjacence[cellule][cellule - 1]) {
        cellule = cellule - 1;
        vue[cellule] = true
    }
    //est
    while ((cellule + 1) % taille != 0 && matrice_adjacence[cellule][cellule + 1]) {
        cellule = cellule + 1;
        vue[cellule] = true
    }

    //nord-est
    while (cellule - taille >= 0 && (cellule + 1) % taille != 0 && matrice_adjacence[cellule][cellule - taille] && matrice_adjacence[cellule][cellule + 1] && matrice_adjacence[(cellule - taille) + 1][cellule - taille] && matrice_adjacence[(cellule - taille) + 1][cellule + 1]) {
        cellule = (cellule - taille) - 1;
        vue[cellule] = true
    }
    //sud-est
    while (cellule + taille < taille * taille && (cellule + 1) % taille != 0 && matrice_adjacence[cellule][cellule + taille] && matrice_adjacence[cellule][cellule + 1] && matrice_adjacence[(cellule + taille) + 1][cellule + taille] && matrice_adjacence[(cellule + taille) + 1][cellule + 1]) {
        cellule = (cellule + taille) + 1;
        vue[cellule] = true
    }
    //sud-ouest
    while (cellule + taille < taille * taille && cellule % taille != 0 && matrice_adjacence[cellule][cellule + taille] && matrice_adjacence[cellule][cellule - 1 && matrice_adjacence[(cellule + taille) - 1][cellule + taille] && matrice_adjacence[(cellule + taille) - 1][cellule - 1]) {
        cellule = (cellule + taille) - 1;
        vue[cellule] = true
    }

    //nord-ouest
    while (cellule - taille >= 0 && cellule % taille != 0 && matrice_adjacence[cellule][cellule - taille] && matrice_adjacence[cellule][cellule - 1 && matrice_adjacence[(cellule - taille) - 1][cellule - taille] && matrice_adjacence[(cellule - taille) - 1][cellule - 1]) {
        cellule = (cellule - taille) - 1;
        vue[cellule] = true
    }
    return vue;
}