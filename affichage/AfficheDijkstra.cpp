#include <iostream>
#include <vector>

using namespace std;

void AfficheDijkstra(const vector<vector<bool>>& matrice_adjacence, int taille, const vector<pair<int, int>>& cheminDijkstra, int sortieX, int sortieY, loot** LootsMatrix, bool afficheChemin, vector<pair<int, int>>& chemin) {
    
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
            bool estCheminDijkstra = false;
            for (const auto& coord : cheminDijkstra) {
                if (coord.first == j && coord.second == i) {
                    estCheminDijkstra = true;
                    break;
                }
            }
            bool estChemin = false;
            for (const auto& coord : chemin) {
                if (coord.first == j && coord.second == i) {
                    estChemin = true;
                    break;
                }
            }
            if (estChemin && afficheChemin == true && estCheminDijkstra) { // violet
                if ((i==0 && j==0) || (i==sortieX && j==sortieY)) cout << "\033[105m[]\033[0m";
                else if (LootsMatrix[i][j].type == "Ennemi") cout << "\033[105mඞ!\033[0m";
                else if (LootsMatrix[i][j].type == "Soin") cout << "\033[105m♥" << LootsMatrix[i][j].value << "\033[0m";
                else if (LootsMatrix[i][j].type == "Tresor") cout << "\033[105m💰\033[0m";
                else cout << "\033[95m▓▓\033[0m";
            } else if (estChemin && afficheChemin == true) { // rouge
                if ((i==0 && j==0) || (i==sortieX && j==sortieY)) cout << "\033[41m[]\033[0m";
                else if (LootsMatrix[i][j].type == "Ennemi") cout << "\033[41mඞ!\033[0m";
                else if (LootsMatrix[i][j].type == "Soin") cout << "\033[41m♥" << LootsMatrix[i][j].value << "\033[0m";
                else if (LootsMatrix[i][j].type == "Tresor") cout << "\033[41m💰\033[0m";
                else cout << "\033[31m▓▓\033[0m";
            } else if (estCheminDijkstra) { // bleu
                if ((i==0 && j==0) || (i==sortieX && j==sortieY)) cout << "\033[44m[]\033[0m";
                else if (LootsMatrix[i][j].type == "Ennemi") cout << "\033[44mඞ!\033[0m";
                else if (LootsMatrix[i][j].type == "Soin") cout << "\033[44m♥" << LootsMatrix[i][j].value << "\033[0m";
                else if (LootsMatrix[i][j].type == "Tresor") cout << "\033[44m💰\033[0m";
                else cout << "\033[34m▓▓\033[0m";
            } else { // gris
                if (LootsMatrix[i][j].type == "Ennemi") cout << "\033[100mඞ!\033[0m";
                else if (LootsMatrix[i][j].type == "Soin") cout << "\033[100m♥" << LootsMatrix[i][j].value << "\033[0m";
                else if (LootsMatrix[i][j].type == "Tresor") cout << "\033[100m💰\033[0m";
                else cout << "░░";
            }
            
            if (j != taille-1) {
                if (matrice_adjacence[i * taille + j][i * taille + j + 1]) {// Vérifie le noeud suivant
                    estCheminDijkstra = false;
                    estChemin = false;
                    for (const auto& coord : cheminDijkstra) {
                        if (coord.first == j && coord.second == i) {
                            estCheminDijkstra = true;
                            break;
                        }
                    }
                    for (const auto& coord : chemin) {
                        if (coord.first == j && coord.second == i) {
                            estChemin = true;
                            break;
                        }
                    }
                    bool estCheminDijkstra2 = false;
                    for (const auto& coord : cheminDijkstra) {
                        if (coord.first == (j+1) && coord.second == (i)) {
                            estCheminDijkstra2 = true;
                            break;
                        }
                    }
                    bool estChemin2 = false;
                    for (const auto& coord : chemin) {
                        if (coord.first == (j+1) && coord.second == (i)) {
                            estChemin2 = true;
                            break;
                        }
                    }
                    if (estChemin2 && estChemin && afficheChemin == true && estCheminDijkstra2 && estCheminDijkstra) cout<<"\033[95m▒▒\033[0m";
                    else if (estChemin2 && estChemin && afficheChemin == true) cout<<"\033[31m▒▒\033[0m";
                    else if (estCheminDijkstra2 && estCheminDijkstra) cout<<"\033[34m▒▒\033[0m";
                    else cout<<"  "; // Pas de mur
                } else
                    cout<<"██"; // Mur
            }
        }
        cout<<"██"<<endl;
        
        if (i != taille-1) {
            cout<<"  ██";
            for (int j=0; j<taille; ++j) {
                if (matrice_adjacence[i * taille + j][(i + 1) * taille + j]) {// Vérifie le noeud en dessous
                    bool estCheminDijkstra = false;
                    for (const auto& coord : cheminDijkstra) {
                        if (coord.first == j && coord.second == i) {
                            estCheminDijkstra = true;
                            break;
                        }
                    }
                    bool estChemin = false;
                    for (const auto& coord : chemin) {
                        if (coord.first == j && coord.second == i) {
                            estChemin = true;
                            break;
                        }
                    }
                    bool estCheminDijkstra2 = false;
                    for (const auto& coord : cheminDijkstra) {
                        if (coord.first == (j) && coord.second == (i+1)) {
                            estCheminDijkstra2 = true;
                            break;
                        }
                    }
                    bool estChemin2 = false;
                    for (const auto& coord : chemin) {
                        if (coord.first == (j) && coord.second == (i+1)) {
                            estChemin2 = true;
                            break;
                        }
                    }
                    if (estChemin2 && estChemin && afficheChemin == true && estCheminDijkstra2 && estCheminDijkstra) cout<<"\033[95m▒▒\033[0m";
                    else if (estChemin2 && estChemin && afficheChemin == true) cout<<"\033[31m▒▒\033[0m";
                    else if (estCheminDijkstra2 && estCheminDijkstra) cout<<"\033[34m▒▒\033[0m";
                    else cout<<"  "; // Pas de mur
                } else
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
