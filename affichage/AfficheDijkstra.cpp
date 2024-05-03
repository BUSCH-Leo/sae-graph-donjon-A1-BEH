#include <iostream>
#include <vector>

using namespace std;

void AfficheDijkstra(const vector<vector<bool>>& matrice_adjacence, int taille, const vector<pair<int, int>>& cheminDijkstra) {
    
    // Première ligne
    for (int i=0; i<taille*2+1; ++i) {
        cout<<"█";
    }
    cout<<endl;

    //Lignes intermédiaires
    for (int i=0; i<taille; ++i) {
        cout<<"█";
        for (int j=0; j<taille; ++j) {
            bool estCheminDijkstra = false;
            for (const auto& coord : cheminDijkstra) {
                if (coord.first == j && coord.second == i) {
                    estCheminDijkstra = true;
                    break;
                }
            }
            if (estCheminDijkstra) {
                cout << "\033[33m∎\033[0m"; // Affiche "O" pour indiquer le chemin de Dijkstra
            } else {
                cout << "·"; // Affiche l'espace si ce n'est pas le chemin de Dijkstra
            }
            
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
                if (j != taille-1) {
                    // Vérifier si les 4 nœuds adjacents sont reliés
                    if (j < taille - 1 && i < taille - 1 &&
                        matrice_adjacence[i * taille + j][i * taille + j + 1] && // Nœud suivant
                        matrice_adjacence[i * taille + j][(i + 1) * taille + j] && // Nœud en dessous
                        matrice_adjacence[i * taille + j + 1][(i + 1) * taille + j +1] && // Nœud en diagonale en bas à droite
                        matrice_adjacence[(i + 1) * taille + j][(i + 1) * taille + j + 1]) { // Nœud en diagonale en bas à gauche
                        cout << " "; // Pas de mur
                    } else {
                        cout << "█"; // Mur
                    }
                }
            }
            cout<<"█"<<endl;
        }
    }

    // Dernière ligne
    for (int i=0; i<taille*2+1; ++i) {
        cout<<"█";
    }
    cout<<endl;
}
