#include <iostream>
#include <vector>
#include "../generation/generateur.cpp"

using namespace std;

void AfficheDonjon(const vector<vector<bool>>& matrice_adjacence, int taille, int sortieX, int sortieY, loot** LootsMatrix) {
    
    // Première ligne
    cout<<"  ";
    for (int i=0; i<taille*2+1; ++i) {
        cout<<"██";
    }
    cout<<endl;

    //Lignes intermédiaires
    for (int i=0; i<taille; ++i) {
        cout<<"  ██";
        for (int j=0; j<taille; ++j) {
            if (LootsMatrix[i][j].type == "Joueur") cout << "\033[42m👤\033[0m";
            else if ((i==0 && j==0) || (i==sortieX && j==sortieY)) cout << "\033[100m\033[96m[]\033[0m";
            else if (LootsMatrix[i][j].type == "Ennemi") cout << "\033[100m\033[31mඞ!\033[0m";
            else if (LootsMatrix[i][j].type == "Soin") cout << "\033[100m\033[92m♥" << LootsMatrix[i][j].value << "\033[0m";
            else if (LootsMatrix[i][j].type == "Tresor") cout << "\033[100m\033[33m💰\033[0m";
            else cout << "░░";

            if (j != taille-1) {
                if (matrice_adjacence[i * taille + j][i * taille + j + 1]) // Vérifie le noeud suivant
                    cout<<"  "; // Pas de mur
                else {
                    cout << "██"; // Mur
                }
            }
        }
        cout<<"██"<<endl;
        
        if (i != taille-1) {
            cout<<"  ██";
            for (int j=0; j<taille; ++j) {
                if (matrice_adjacence[i * taille + j][(i + 1) * taille + j]) // Vérifie le noeud en dessous
                    cout<<"  "; // Pas de mur
                else
                    cout<<"██"; // Mur
                if (j != taille-1) {
                    // Vérifier si les 4 nœuds adjacents sont reliés
                    if (j < taille - 1 && i < taille - 1 &&
                        matrice_adjacence[i * taille + j][i * taille + j + 1] && // Nœud suivant
                        matrice_adjacence[i * taille + j][(i + 1) * taille + j] && // Nœud en dessous
                        matrice_adjacence[i * taille + j + 1][(i + 1) * taille + j +1] && // Nœud en diagonale en bas à droite
                        matrice_adjacence[(i + 1) * taille + j][(i + 1) * taille + j + 1]) { // Nœud en diagonale en bas à gauche
                        cout << "  "; // Pas de mur
                    } else {
                        cout << "██"; // Mur
                    }
                }
            }
            cout<<"██"<<endl;
        }
    }

    // Dernière ligne
    cout<<"  ";
    for (int i=0; i<taille*2+1; ++i) {
        cout<<"██";
    }
    cout<<endl;
}
