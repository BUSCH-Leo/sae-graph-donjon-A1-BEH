#include <iostream>
#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include "termkit/termkit.cpp"

#include "affichage/AfficheDonjon.cpp"
#include "affichage/AfficheDijkstra.cpp"
#include "affichage/dicte.cpp"
#include "parcours/Dijkstra.cpp"
#include "chargement/chargement.cpp"

using namespace std;

void Jeu(vector<vector<bool>> matrice_adjacence, int taille, int sortieX, int sortieY, loot** LootsMatrix) {

    /*
    ======================================================================================================
    pour une raison qui m'échappe, x et y ont été inversé dans une bonne partie du programme, après m'être
    perdu dans le programme j'ai décidé de laisser comme tel étant donné que ça marche très bien
    ======================================================================================================
    */

    bool fin_jeu = false;
    bool releve = false;

    // Initialisation du joueur

    LootsMatrix[0][0].type = "Joueur";
    LootsMatrix[0][0].value = 100;

    int joueur_value = 100;
    int joueur_x = 0;
    int joueur_y = 0;

    // Initialisation d'une valeur de sauvegarde

    string type_temp = "none";
    int value_temp = 0;

    while (fin_jeu == false) {
        termkit::clear();
        cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;
    
        cout << "\n     Affichage du donjon :\n" << endl;
        AfficheDonjon(matrice_adjacence, taille, sortieX, sortieY, LootsMatrix);

        // Detection des touches

        if (releve == true) {
            if (!(GetAsyncKeyState('Z') & 0x8000)
            && !(GetAsyncKeyState('Q') & 0x8000)
            && !(GetAsyncKeyState('S') & 0x8000)
            && !(GetAsyncKeyState('D') & 0x8000)) releve = false;
            else releve = true;
        }

        termkit::getch();

        // Aide possible

        if (GetAsyncKeyState('A') & 0x8000 && releve == false) {
            cout << "\b \b";
            termkit::clear();
            cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;
            cout << "\n     [Aide] Le plus court chemin possible est le suivant :" << endl;
            vector<pair<int, int>> cheminParfait = Dijkstra(matrice_adjacence, taille, 0, 0, sortieX, sortieY);
            AfficheDijkstra(matrice_adjacence, taille, cheminParfait, sortieX, sortieY, LootsMatrix);

            cout << endl;
            Attente(5);

            releve = true;
        }
        
        // Touches principales

        if (GetAsyncKeyState('Z') & 0x8000 && releve == false) {
            cout << "\b \b";
            if (joueur_y-1 >= 0) {
                if (matrice_adjacence[joueur_y * taille + joueur_x][(joueur_y - 1) * taille + joueur_x] == true) {
                    LootsMatrix[joueur_y][joueur_x].type = type_temp;
                    LootsMatrix[joueur_y][joueur_x].value = value_temp;

                    type_temp = LootsMatrix[joueur_y-1][joueur_x].type;
                    value_temp = LootsMatrix[joueur_y-1][joueur_x].value;

                    joueur_y--;
                    LootsMatrix[joueur_y][joueur_x].type = "Joueur";
                    LootsMatrix[joueur_y][joueur_x].value = joueur_value;
                }
            }
            releve = true;
        }
        if (GetAsyncKeyState('Q') & 0x8000 && releve == false) {
            cout << "\b \b";
            if (joueur_x-1 >= 0) {
                if (matrice_adjacence[joueur_y * taille + joueur_x][joueur_y * taille + joueur_x - 1] == true) {
                    LootsMatrix[joueur_y][joueur_x].type = type_temp;
                    LootsMatrix[joueur_y][joueur_x].value = value_temp;

                    type_temp = LootsMatrix[joueur_y][joueur_x-1].type;
                    value_temp = LootsMatrix[joueur_y][joueur_x-1].value;

                    joueur_x--;
                    LootsMatrix[joueur_y][joueur_x].type = "Joueur";
                    LootsMatrix[joueur_y][joueur_x].value = joueur_value;
                }
            }
            releve = true;
        }
        if (GetAsyncKeyState('S') & 0x8000 && releve == false) {
            cout << "\b \b";
            if (joueur_y+1 < taille) {
                if (matrice_adjacence[joueur_y * taille + joueur_x][(joueur_y + 1) * taille + joueur_x] == true) {
                    LootsMatrix[joueur_y][joueur_x].type = type_temp;
                    LootsMatrix[joueur_y][joueur_x].value = value_temp;

                    type_temp = LootsMatrix[joueur_y+1][joueur_x].type;
                    value_temp = LootsMatrix[joueur_y+1][joueur_x].value;

                    joueur_y++;
                    LootsMatrix[joueur_y][joueur_x].type = "Joueur";
                    LootsMatrix[joueur_y][joueur_x].value = joueur_value;
                }
            }
            releve = true;
        }
        if (GetAsyncKeyState('D') & 0x8000 && releve == false) {
            cout << "\b \b";
            if (joueur_x+1 < taille) {
                if (matrice_adjacence[joueur_y * taille + joueur_x][joueur_y * taille + joueur_x + 1] == true) {
                    LootsMatrix[joueur_y][joueur_x].type = type_temp;
                    LootsMatrix[joueur_y][joueur_x].value = value_temp;

                    type_temp = LootsMatrix[joueur_y][joueur_x+1].type;
                    value_temp = LootsMatrix[joueur_y][joueur_x+1].value;

                    joueur_x++;
                    LootsMatrix[joueur_y][joueur_x].type = "Joueur";
                    LootsMatrix[joueur_y][joueur_x].value = joueur_value;
                }
            }
            releve = true;
        }

        // Detection de fin de jeu

        if (joueur_y == sortieX && joueur_x == sortieY) {
            fin_jeu = true;
        }

        Sleep(10);
    }

    termkit::clear();
    cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;
    cout << "\n     Le plus court chemin possible était le suivant :" << endl;
    vector<pair<int, int>> cheminParfait = Dijkstra(matrice_adjacence, taille, 0, 0, sortieX, sortieY);
    AfficheDijkstra(matrice_adjacence, taille, cheminParfait, sortieX, sortieY, LootsMatrix);
}

int main() {

    SetConsoleOutputCP(CP_UTF8); // pour éviter d'avoir mauvais charactère

    srand(time(NULL));

    // FauxChargement(50); // à mettre en commentaire si il y a des problèmes
    termkit::clear();

    // Déclaration des variables

    int entreX=0;
    int entreY=0;

    char config_d = ' ';
    bool ChoixConfig = false;

    string seed = "";
    int seed_convert = 0;
    char choix_seed;

    int taille = 0;
    
    int sortix = 0;
    int sorty = 0;

    int type_laby = 0;

    int prct_imparfait = 10;
    int prct_proba = 15;

    // Affichage ARX

    cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;

    // Demander le type de configuration
    
    while (ChoixConfig != true) {
        cout << "\n     Souhaitez-vous une configuration rapide ? (o/n)\n     Choix : ";
        cin >> config_d;

        if (config_d == 'O' || config_d == 'o') {

            // Choix de la seed
            
            random_device rd;
            seed_convert = rand() % 1000000;

            cout << "\n     1. La seed aléatoirement choisi est : " << seed_convert << endl;
            srand(seed_convert);

            // Choix de la taille du labyrinthe

            taille = (rand() % 10)+20;

            cout << "\n     2. La taille aléatoirement choisi est : " << taille << endl;

            // Choix de la sortie aléatoire

            sortix = rand() % taille;
            sorty = rand() % taille;
            
            cout << "\n     3. La sortie se situera en :\n     X = " << sortix << "\n     Y = " << sorty << endl;

            // Création d'un labyrinthe imparfait avec 10% de murs retirés

            cout << "\n     4. Le labyrinthe est défini comme 'Imparfait' avec 10% de murs retirés." << endl;
            vector<vector<bool>> matrice_adjacence(taille * taille, vector<bool>(taille * taille, false));
            LabyrintheImparfait(matrice_adjacence, taille, entreX, entreY, prct_imparfait);

            // Placement des loots

            cout << "\n     5. Placement des loots aléatoirement (par défaut 15 %)." << endl;
            loot** LootsMatrix = PlaceLoot(matrice_adjacence, taille, prct_proba);

            // Préparation du prochain écran

            cout<<endl;
            Attente(3);

            termkit::clear();
            ChoixConfig = true;

            // Lancement du jeu

            Jeu(matrice_adjacence, taille, sortix, sorty, LootsMatrix);
        }
        else if (config_d == 'N' || config_d == 'n') {

            // Choix de la seed

            cout << "\n     1. Entrez la seed : ";
            cin >> seed;

            for (char c : seed) {
                int asciiValue = static_cast<int>(c);
                seed_convert = seed_convert * 10 + asciiValue;
            }

            srand(seed_convert);
            cout << "     La seed choisi est : " << seed << "\n     Ou " << seed_convert << " en Ascii." << endl;

            // Choix de la taille du labyrinthe

            cout << "\n     2. Entrez la taille du labyrinthe (conseillé en dessous de 50) : ";
            cin >> taille;

            while (taille <= 1 || taille > 160) {
                cout << "\n     [!] Veuillez rentrer une valeur entre 2 et 160." << endl;
                cout << "\n     Entrez la taille du labyrinthe (conseillé en dessous de 50) : ";
                cin >> taille;
            }

            // Choix de la sortie aléatoire

            sortix = rand() % taille;
            sorty = rand() % taille;
            
            cout << "\n     3. La sortie se situera en :\n     X = " << sortix << "\n     Y = " << sorty << endl;

            // Création d'un labyrinthe choisi

            cout << "\n     4. Veuillez choisir le type de labyrinthe selon la liste suivante :" << endl;
            cout << "     1 - Labyrinthe Parfait (un seul chemin possible)" << endl;
            cout << "     2 - Labyrinthe Imparfait (plusieurs chemins possibles)" << endl;
            cout << "     3 - Labyrinthe 'Plus Que Parfait' (utilisation du labyrinthe parfait 2×)" << endl;
            cout << "     Votre choix : ";
            cin >> type_laby;
            
            while (type_laby <= 0 || type_laby > 3) {
                cout << "\n     [!] Le choix est incorrect, veuillez réessayer." << endl;
                cout << "\n     Votre choix : ";
                cin >> type_laby;
            }

            vector<vector<bool>> matrice_adjacence(taille * taille, vector<bool>(taille * taille, false));

            if (type_laby == 1) {
                LabyrintheParfait(matrice_adjacence, taille, entreX, entreY);
            }
            else if (type_laby == 2) {
                cout << "\n     Entrez le pourcentage de murs à retirer dans le labyrinthe imparfait : ";
                cin >> prct_imparfait;

                while (prct_imparfait<0 || prct_imparfait>100) {
                    cout << "\n     [!] Veuillez entrer une valeur entre 0 et 100." << endl;
                    cout << "\n     Votre choix : ";
                    cin >> prct_imparfait;
                }

                if (prct_imparfait >= 95) cout << "\n     [!] Il arrive parfois qu'un pourcentage élevé possède des erreurs à la suppression des murs" << endl;
                LabyrintheImparfait(matrice_adjacence, taille, entreX, entreY, prct_imparfait);
            }
            else if (type_laby == 3) {
                LabyrinthePlusQueParfait(matrice_adjacence, taille, entreX, entreY);
            }

            // Placement des loots

            cout << "\n     5. Veuillez envoyer le pourcentage d'apparition des loots (conseillé 15 %)\n     Votre choix : ";
            cin >> prct_proba;

            while (prct_proba<0 && prct_proba>100) {
                cout << "\n     [!] Veuillez entrer une valeur entre 0 et 100." << endl;
                cout << "\n     Votre choix : ";
                cin >> prct_proba;
            }

            loot** LootsMatrix = PlaceLoot(matrice_adjacence, taille, prct_proba);

            // Préparation du prochain écran

            cout<<endl;
            Attente(3);

            termkit::clear();
            ChoixConfig = true;

            // Lancement du jeu

            Jeu(matrice_adjacence, taille, sortix, sorty, LootsMatrix);
        }
        else {
            cout << "\n     [!] Le choix est incorrect, veuillez réessayer." << endl;
        }
    }

    return 0;
}
