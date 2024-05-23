#include <iostream>

#include "PFC.cpp"
#include "shop.cpp"
#include "../affichage/AfficheTouche.cpp"   

using namespace std;

void Jeu(vector<vector<bool>> matrice_adjacence, int taille, int sortieX, int sortieY, loot** LootsMatrix, int seed, float coef_argent, float coef_ennemi) {

    AfficheTouche();

    /*
    ======================================================================================================
    pour une raison qui m'échappe, x et y ont été inversé dans une bonne partie du programme, après m'être
    perdu dans le programme j'ai décidé de laisser comme tel étant donné que ça marche très bien
    ======================================================================================================
    */

    bool fin_jeu = false;
    char key_pressed = ' ';

    // Initialisation du joueur

    LootsMatrix[0][0].type = "Joueur";
    LootsMatrix[0][0].value = 50;

    int joueur_value = 50;
    int joueur_coins = 0;
    int joueur_x = 0;
    int joueur_y = 0;

    bool dijkstra_pass = false;
    int choix_shop = 0;
    bool instakill = false;

    int tp_x = 0;
    int tp_y = 0;

    int PFC_jeu = 0;
    int ennemis_tues = 0;

    float bonus_argent = coef_argent;
    int nb_bonus = 1;

    bool** visibleMatrix = new bool* [taille];
    for (int i = 0; i < taille; ++i) {
        visibleMatrix[i] = new bool[taille];
        for (int j = 0; j < taille; ++j) {
            visibleMatrix[i][j] = false;
        }
    }

    // Initialisation d'une valeur de sauvegarde

    string type_temp = "none";
    int value_temp = 0;

    while (fin_jeu == false) {
        termkit::clear();
        
        cout << "\n     Votre vie : " << joueur_value << " \033[91m♥\033[0m" << endl;
        cout << "     Votre argent : " << joueur_coins << " 💰 [E]" << endl;
        cout << "     Pass PlusCourtChemin : " << (dijkstra_pass ? "Acheté [A]." : "Non-acheté.") << endl;
        cout << "     Coefficient de l'argent : " << "×" << bonus_argent << endl;

        cout << "\n     Affichage du donjon :\n" << endl;
        //AfficheDonjon(matrice_adjacence, taille, sortieX, sortieY, LootsMatrix);
        AfficheDonjonVisible(matrice_adjacence, taille, sortieX, sortieY, LootsMatrix,joueur_x,joueur_y,visibleMatrix);

        // Si nous rencontrons un ennemi ou une potion de soin

        if (type_temp == "Ennemi" && instakill == true) {
            type_temp = "none"; // Efface la case
            value_temp = 0;
            instakill = false;
            joueur_coins += rand() % 6;
        }
        else if (type_temp == "Ennemi" && instakill == false) {
            PFC_jeu = PFC(value_temp*coef_ennemi);

            joueur_value -= PFC_jeu;
            ennemis_tues++;

            if (PFC_jeu == 0) {
                joueur_coins += rand() % 6;
                joueur_value += rand() % 6;
            }

            type_temp = "none"; // Efface la case
            value_temp = 0;
        }
        else if (type_temp == "Soin") {
            joueur_value += value_temp;

            type_temp = "none"; // Efface la case
            value_temp = 0;
        }
        else if (type_temp == "Tresor") {
            joueur_coins += value_temp*(bonus_argent);

            type_temp = "none"; // Efface la case
            value_temp = 0;
        }

        // Detection des touches

        key_pressed = termkit::getch();

        /*while (key_pressed != 'a' && key_pressed != 'z' && key_pressed != 'e' && key_pressed != 'q' && key_pressed != 's' && key_pressed != 'd')
            key_pressed = termkit::getch();*/

        // Touche séléctionnée

        if (key_pressed == 'a' && dijkstra_pass == true) {
            cout << "\b \b";
            termkit::clear();
            
            cout << "\n     [Aide] Le plus court chemin possible est le suivant :" << endl;
            vector<pair<int, int>> cheminParfait = Dijkstra(matrice_adjacence, taille, joueur_y, joueur_x, sortieX, sortieY);
            AfficheDijkstra(matrice_adjacence, taille, cheminParfait, sortieX, sortieY, LootsMatrix);

            cout << endl;
            Attente(3);
        }
        else if (key_pressed == 'e') {
            cout << "\b \b";

            choix_shop = Shop(joueur_coins, dijkstra_pass, nb_bonus);
            
            if (choix_shop == 1) {
                dijkstra_pass = true;
                joueur_coins -= 20;
            }
            else if (choix_shop == 2) {
                instakill = true;
                joueur_coins -= 5;
            }
            else if (choix_shop == 3) {
                joueur_value += 5;
                joueur_coins -= 10;
            }
            else if (choix_shop == 4) {
                tp_x = rand() % taille;
                tp_y = rand() % taille;

                LootsMatrix[joueur_y][joueur_x].type = type_temp;
                LootsMatrix[joueur_y][joueur_x].value = value_temp;

                type_temp = LootsMatrix[tp_y][tp_x].type;
                value_temp = LootsMatrix[tp_y][tp_x].value;

                joueur_y = tp_y;
                joueur_x = tp_x;
                LootsMatrix[joueur_y][joueur_x].type = "Joueur";
                LootsMatrix[joueur_y][joueur_x].value = joueur_value;

                joueur_coins -= 5;
            }
            else if (choix_shop == 5) {
                bonus_argent = bonus_argent*2;

                joueur_coins -= 10*nb_bonus;
                nb_bonus ++;
            }
        }
        else if (key_pressed == 'z') {
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
        }
        else if (key_pressed == 'q') {
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
        }
        else if (key_pressed == 's') {
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
        }
        else if (key_pressed == 'd') {
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
        }

        // Si on perd

        if (joueur_value <= 0 ) {
            termkit::clear();
            cout << "\n     Vous avez perdu !" << endl;
            cout << "     Fin de la partie." << endl;

            Attente(3);
            fin_jeu = true;
        }

        // Detection de fin de jeu

        if (joueur_y == sortieX && joueur_x == sortieY) {
            fin_jeu = true;
        }

        key_pressed = ' ';
    }

    termkit::clear();
    cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;
    
    if (joueur_value < 0) joueur_value = 0;

    cout << "\n     Votre vie : " << joueur_value << " \033[91m♥\033[0m" << endl;
    cout << "     Votre argent : " << joueur_coins << " 💰" << endl;
    cout << "     Ennemis tués : " << ennemis_tues << " ඞ" << endl;
    
    cout << "\n     Le plus court chemin possible était le suivant :" << endl;
    vector<pair<int, int>> cheminParfait = Dijkstra(matrice_adjacence, taille, 0, 0, sortieX, sortieY);
    AfficheDijkstra(matrice_adjacence, taille, cheminParfait, sortieX, sortieY, LootsMatrix);
    cout << "\n     La seed était : " << seed << "\n" << endl;
}
