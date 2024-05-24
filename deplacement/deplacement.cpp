#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void nord_est(int entreX,int entreY,int taille, vector<bool>& vue, const vector<vector<bool>>& matrice_adjacence){
    int cellule = (entreX + entreY * taille);
    if (cellule - taille >= 0 && (cellule + 1) % taille != 0 &&
        matrice_adjacence[cellule][cellule - taille] &&
        matrice_adjacence[cellule][cellule + 1] &&
        matrice_adjacence[cellule - taille][cellule - taille + 1] &&
        matrice_adjacence[cellule + 1][cellule - taille + 1] &&
        vue[cellule - taille + 1] == false)  {
        cellule = (cellule - taille) + 1;
        vue[cellule] = true;
        nord_est(entreX + 1, entreY, taille, vue, matrice_adjacence);
        nord_est(entreX, entreY - 1, taille, vue, matrice_adjacence);
    }
    else { return; }
}

void sud_est(int entreX, int entreY, int taille, vector<bool>& vue, const vector<vector<bool>>& matrice_adjacence) {
    int cellule = (entreX + entreY * taille);
    if (cellule + taille < taille * taille && (cellule + 1) % taille != 0 &&
        matrice_adjacence[cellule][cellule + taille] &&
        matrice_adjacence[cellule][cellule + 1] &&
        matrice_adjacence[cellule + taille][cellule + taille + 1] &&
        matrice_adjacence[cellule + 1][cellule + taille + 1] &&
        vue[cellule + taille + 1]==false) {
        cellule = (cellule + taille) + 1;
        vue[cellule] = true;
        sud_est(entreX + 1, entreY, taille, vue, matrice_adjacence);
        sud_est(entreX, entreY + 1, taille, vue, matrice_adjacence);
    }
    else { return; }
}

void sud_ouest(int entreX, int entreY, int taille, vector<bool>& vue, const vector<vector<bool>>& matrice_adjacence) {
    int cellule = (entreX + entreY * taille);
    if (cellule + taille < taille * taille && cellule % taille != 0 &&
        matrice_adjacence[cellule][cellule + taille] &&
        matrice_adjacence[cellule][cellule - 1] &&
        matrice_adjacence[cellule + taille][cellule + taille - 1] &&
        matrice_adjacence[cellule - 1][cellule + taille - 1] &&
        vue[(cellule + taille) - 1] == false) {
        cellule = (cellule + taille) - 1;
        vue[cellule] = true;
        sud_ouest(entreX - 1, entreY, taille, vue, matrice_adjacence);
        sud_ouest(entreX, entreY + 1, taille, vue, matrice_adjacence);
    }
    else { return; }
}

void nord_ouest(int entreX, int entreY, int taille, vector<bool>& vue, const vector<vector<bool>>& matrice_adjacence) {
    int cellule = (entreX + entreY * taille);
    if (cellule - taille >= 0 && cellule % taille != 0 &&
        matrice_adjacence[cellule][cellule - taille] &&
        matrice_adjacence[cellule][cellule - 1] &&
        matrice_adjacence[cellule - taille][cellule - taille - 1] &&
        matrice_adjacence[cellule - 1][cellule - taille - 1] &&
        vue[(cellule - taille) - 1] == false) {
        cellule = (cellule - taille) - 1;
        vue[cellule] = true;
        nord_ouest(entreX - 1, entreY, taille, vue, matrice_adjacence);
        nord_ouest(entreX, entreY - 1, taille, vue, matrice_adjacence);
    }
    else { return; }
}

vector<bool> visibilite(const vector<vector<bool>>& matrice_adjacence, int taille, int entreX, int entreY) {
    int cellule = (entreX + entreY * taille);
    vector<bool> vue(taille * taille, false);
    vue[cellule] = true;

    // sud
    while (cellule - taille >= 0 && matrice_adjacence[cellule][cellule - taille]) {
        cellule = cellule - taille;
        vue[cellule] = true;
    }

    // nord
    cellule = (entreX + entreY * taille);
    while (cellule + taille < taille * taille && matrice_adjacence[cellule][cellule + taille]) {
        cellule = cellule + taille;
        vue[cellule] = true;
    }

    // ouest
    cellule = (entreX + entreY * taille);
    while (cellule % taille != 0 && matrice_adjacence[cellule][cellule - 1]) {
        cellule = cellule - 1;
        vue[cellule] = true;
    }

    // est
    cellule = (entreX + entreY * taille);
    while ((cellule + 1) % taille != 0 && matrice_adjacence[cellule][cellule + 1]) {
        cellule = cellule + 1;
        vue[cellule] = true;
    }

    nord_est(entreX, entreY, taille, vue, matrice_adjacence);
    sud_est(entreX, entreY, taille, vue, matrice_adjacence);
    sud_ouest(entreX, entreY, taille, vue, matrice_adjacence);
    nord_ouest(entreX, entreY, taille, vue, matrice_adjacence);

    return vue;
}
