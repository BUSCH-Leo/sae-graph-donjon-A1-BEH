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

    /*
    FauxChargement(50);
    */

    unsigned int seed;
    char choix_seed;
    cout << "Voulez-vous entrer une seed manuellement ? (o/n) : ";
    cin >> choix_seed;

    if (choix_seed == 'o' || choix_seed == 'O') {
        cout << "Entrez la seed : ";
        cin >> seed;
    }
    else {
        random_device rd;
        seed = rd();
        cout << "Seed aléatoire générée : " << seed << endl;
    }
    srand(seed);
    cout << "la seed est :" << seed << endl;
    Sleep(5000);

    system("Clear");

    cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;

    int entreX=0;
    int entreY=0;

    // On demande à l'utilisateur la taille du labyrinthe
    int taille = 0;
    while (taille <= 0 || taille > 160) {
        cout << "Entrez la taille du labyrinthe : ";
        cin >> taille;
        if (taille <= 0 || taille > 160) {
            cout << "[!] Veuillez rentrer une valeur entre 1 et 160." << endl;
        }
    }

    int sortix = rand() % taille;
    int sorty = rand() % taille;

    cout << sortix << " " << sorty << endl;

    vector<vector<bool>> matrice_adjacenceParfaite(taille * taille, vector<bool>(taille * taille, false));
    vector<vector<bool>> matrice_adjacencePlusqueparfaite(taille * taille, vector<bool>(taille * taille, false));
    vector<vector<bool>> matrice_adjacenceImparfaite(taille * taille, vector<bool>(taille * taille, false));
    int sortieParfaite = LabyrintheParfait(matrice_adjacenceParfaite, taille, entreX, entreY);
    AfficheDonjon(matrice_adjacenceParfaite, taille, sortix, sorty);
    vector<pair<int, int>> cheminParfait = Dijkstra(matrice_adjacenceParfaite, taille, 0, 0, sortix, sorty);
    AfficheDijkstra(matrice_adjacenceParfaite, taille, cheminParfait, sortix, sorty);
    int sortiePlusqueparfaite = LabyrinthePlusQueParfait(matrice_adjacencePlusqueparfaite, taille, entreX, entreY);
    AfficheDonjon(matrice_adjacencePlusqueparfaite, taille, sortix, sorty);
    vector<pair<int, int>> cheminPlusqueparfait = Dijkstra(matrice_adjacencePlusqueparfaite, taille, 0, 0, sortix, sorty);
    AfficheDijkstra(matrice_adjacencePlusqueparfaite, taille, cheminPlusqueparfait, sortix, sorty);
    int sortieImparfaite = LabyrintheImparfait(matrice_adjacenceImparfaite, taille, entreX, entreY, 5);
    AfficheDonjon(matrice_adjacenceImparfaite, taille, sortix, sorty);
    vector<pair<int, int>> cheminImparfait = Dijkstra(matrice_adjacenceImparfaite, taille, 0, 0, sortix, sorty);
    AfficheDijkstra(matrice_adjacenceImparfaite, taille, cheminImparfait, sortix, sorty);
    return 0;
}

