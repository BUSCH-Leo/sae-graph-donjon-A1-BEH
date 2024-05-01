#include <iostream>
#include <vector>
#include <windows.h>
#include "affichage/AfficheDonjon.cpp"
#include "generation/LabyrintheParfait.cpp"

using namespace std;

int main() {

    int entreX=1;
    int entreY=0;

    SetConsoleOutputCP(CP_UTF8); // pour éviter d'avoir mauvais charactère

    // On demande à l'utilisateur la taille du labyrinthe
    int taille = 0;
    while (taille <= 0 || taille > 50) {
        cout << "Entrez la taille du labyrinthe : ";
        cin >> taille;
        if (taille <= 0 || taille > 50) {
            cout << "[!] Veuillez rentrer une valeur entre 1 et 50." << endl;
        }
    }

    // Création d'une matrice d'adjacence de n*n taille (pour lier pouvoir lier tout les sommets)   
    vector<vector<bool>> matrice_adjacence(taille * taille, vector<bool>(taille * taille, false));
    LabyrintheParfait(matrice_adjacence, taille, entreX, entreY);

    return 0;
}
