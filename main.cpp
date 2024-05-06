#include <iostream>
#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include "affichage/AfficheDonjon.cpp"
#include "affichage/AfficheDijkstra.cpp"
#include "generation/generateur.cpp"
#include "parcours/Dijkstra.cpp"
#include "chargement/chargement.cpp"

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8); // pour éviter d'avoir mauvais charactère
    
    srand(time(NULL));

    FauxChargement(50);
    system("Clear");

    cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;

    int entreX=0;
    int entreY=0;


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
    int sortie = LabyrintheImparfait(matrice_adjacence, taille, entreX, entreY,75);

    AfficheDonjon(matrice_adjacence, taille);

    cout<<endl;

    vector<pair<int, int>> cheminParcouru = Dijkstra(matrice_adjacence, taille, 0, 0, taille-1, taille-1);

    cout<<endl;

    AfficheDijkstra(matrice_adjacence, taille, cheminParcouru);

    return 0;
}
