#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "../listes/listes.cpp"

using namespace std;


int voisinrandom(vector<vector<bool>>& matrice_adjacence, vector<bool>& visite, int cellule, int taille) {
    vector<int> cellules;
    cellules.clear();

    if (cellule - taille >= 0 && !visite[cellule - taille]) {
        cellules.push_back(cellule - taille);
    }

    if (cellule + taille < taille * taille && !visite[cellule + taille]) {
        cellules.push_back(cellule + taille);
    }

    if (cellule % taille != 0 && !visite[cellule - 1]) {
        cellules.push_back(cellule - 1);
    }

    if ((cellule + 1) % taille != 0 && !visite[cellule + 1]) {
        cellules.push_back(cellule + 1);
    }

    if (cellules.empty()) {
        return -1;
    }

    int numrand = rand() % cellules.size();
    int voisin = cellules[numrand];
    return voisin;
}

int randomprofondeur(vector<vector<bool>>& matrice_adjacence, vector<bool>& visite, int cellule, int taille) {
    visite[cellule] = true;
    int voisin = voisinrandom(matrice_adjacence, visite, cellule, taille);
    while (voisin != -1) {
        matrice_adjacence[cellule][voisin] = true;
        matrice_adjacence[voisin][cellule] = true;
        randomprofondeur(matrice_adjacence, visite, voisin, taille);
        voisin = voisinrandom(matrice_adjacence, visite, cellule, taille);
    }
    return cellule;
}

int LabyrintheParfait(vector<vector<bool>>& matrice_adjacence, int taille, int entreX, int entreY) {
    int cellule = (entreX + entreY * taille);
    vector<bool>visite(taille*taille, false);
    randomprofondeur(matrice_adjacence, visite, cellule, taille);
    return cellule;
}

int LabyrinthePlusQueParfait(vector<vector<bool>>& matrice_adjacence, int taille, int entreX, int entreY) {
    int cellule1 = (entreX + entreY * taille);
    vector<bool>visite1(taille * taille, false);
    randomprofondeur(matrice_adjacence, visite1, cellule1, taille);
    int cellule2 = (entreX + entreY * taille);
    vector<bool>visite2(taille * taille, false);
    randomprofondeur(matrice_adjacence, visite2, cellule2, taille);
    return cellule2;
}

/*
function create Maze()
    startVertex Vertex(0, 0)
    randomizedDFS(start Vertex)
end
    function randomizedDFS(vertex)
    mark Visited(vertex)
    nextVertex <- randomUnvisited Neighbour(vertex)
    while nextVertex != null do
    connectCells(vertex, nextVertex);
    randomizedDFS(nextVertex)
    nextVertex <- randomUnvisited Neighbour(vertex)
    end
    return
end
*/