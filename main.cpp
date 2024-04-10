#include <iostream>
#include <vector>
#include <windows.h>
#include "affichage/AfficheDonjon.cpp"

using namespace std;

int main() {

   SetConsoleOutputCP(CP_UTF8); // pour éviter d'avoir mauvais charactère
   
    // On demande à l'utilisateur la taille du labyrinthe
    int taille=0;
    while (taille <= 0 || taille > 50) {
        cout<<"Entrez la taille du labyrinthe : ";
        cin>>taille;
        if (taille <= 0 || taille > 50) {
            cout<<"[!] Veuillez rentrer une valeur entre 1 et 50."<<endl;
        }
    }

    // Création d'une matrice d'adjacence de n*n taille (pour lier pouvoir lier tout les sommets)
    vector<vector<bool>> matrice_adjacence(taille*taille, vector<bool>(taille*taille, false));

    AfficheDonjon(matrice_adjacence, taille);


// ---------------------------------------------------------------------------

/*
    // Création d'une matrice d'adjacence de 3x3
    vector<vector<bool>> matrice_adjacence(9, vector<bool>(9, false));
    
    AfficheDonjon(matrice_adjacence, 3);
    // Modifier quelques connexions pour illustrer l'exemple
    matrice_adjacence[0][1] = true; // Lien entre (0,0) et (0,1)
    matrice_adjacence[1][0] = true;

    matrice_adjacence[3][6] = true; // Lien entre (0,1) et (0,2)
    matrice_adjacence[6][3] = true;

    matrice_adjacence[1][4] = true; // Lien entre (1,0) et (1,1)
    matrice_adjacence[4][1] = true;
    
    AfficheDonjon(matrice_adjacence, 3);
*/
    return 0;
}
