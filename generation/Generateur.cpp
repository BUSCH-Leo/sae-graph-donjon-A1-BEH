#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct loot {
	string type;
	int value;
    int alt_value;
	loot () {
		type = "none";
		value = 0;
		alt_value = 0;
	}
};

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

int LabyrintheImparfait(vector<vector<bool>>& matrice_adjacence, int taille, int entreX, int entreY, float nbtrou) {
    nbtrou = (taille * taille) * (nbtrou / 100);
    int cellule = (entreX + entreY * taille);
    vector<bool>visite(taille * taille, false);
    randomprofondeur(matrice_adjacence, visite, cellule, taille);
    int voisin;
    int numrand;
    vector<bool>visitevide(taille * taille, false);
    int y = 0;
    for (int i = 0; i < nbtrou; i++) {
        numrand = rand() % (taille*taille);
        voisin = voisinrandom(matrice_adjacence, visitevide, numrand, taille);
        if (matrice_adjacence[numrand][voisin] == true) {
            i--;
            y++;
            if (y >= 1000) { break; }
        }
        else {
            matrice_adjacence[numrand][voisin] = true;
            matrice_adjacence[voisin][numrand] = true;
            y = 0;
        }
    }
    return cellule;
}

loot** PlaceLoot(vector<vector<bool>>& matrice_adjacence, int taille, int proba) {
	loot** LootsMatrix = new loot*[taille];
	for (int i = 0; i < taille; ++i) {
        LootsMatrix[i] = new loot[taille];
    }
	
	for (int i = 0; i < taille; ++i) {
		for (int j = 0; j < taille; ++j) {
			int randType = rand() % 100;
			int randValue = (rand() % 8)+1;	// Valeur à changer au besoin
			if (randType <= proba*7/10) { // 70%
				LootsMatrix[i][j].type = "Ennemi";
				LootsMatrix[i][j].value = randValue*2; // Degats entre 2 et 20
			}
			else if (randType > proba*7/10 && randType <= (proba*7/10+proba*1/10)) { // 10 %
				LootsMatrix[i][j].type = "Soin";
				LootsMatrix[i][j].value = randValue;
			}
			else if (randType > (proba*8/10) && randType <= proba) { // 20 %
				LootsMatrix[i][j].type = "Tresor";
				LootsMatrix[i][j].value = randValue;
			}
		}
	}
	return LootsMatrix;
}
