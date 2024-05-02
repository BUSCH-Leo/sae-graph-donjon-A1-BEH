    #include <iostream>
#include <vector>

using namespace std;

void AfficheDonjon(const vector<vector<bool>>& matrice_adjacence, int taille) {
    
    // Première ligne
    cout<<"█";
    for (int i=0; i<taille; ++i) {
        if (i != 1) cout<<"█";
        else cout<<" ";
        if (i != taille-1) {
            cout<<"█";
        }
    }
    cout<<"█"<<endl;

    //Lignes intermédiaires
    for (int i=0; i<taille; ++i) {
        cout<<"█";
        for (int j=0; j<taille; ++j) {
            cout<<" ";
            if (j != taille-1) {
                if (matrice_adjacence[i * taille + j][i * taille + j + 1]) // Vérifie le noeud suivant
                    cout<<" "; // Pas de mur
                else
                    cout<<"█"; // Mur
            }
        }
        cout<<"█"<<endl;
        
        if (i != taille-1) {
            cout<<"█";
            for (int j=0; j<taille; ++j) {
                if (matrice_adjacence[i * taille + j][(i + 1) * taille + j]) // Vérifie le noeud en dessous
                    cout<<" "; // Pas de mur
                else
                    cout<<"█"; // Mur
                if (j != taille-1) cout<<"█";
            }
            cout<<"█"<<endl;
        }
    }

    // Dernière ligne
    cout<<"█";
    for (int i=0; i<taille; ++i) {
        cout<<"█";
        if (i != taille-1) {
            cout<<"█";
        }
    }
    cout<<"█"<<endl;
}