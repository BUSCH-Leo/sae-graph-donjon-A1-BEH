#include <iostream>

#include "../termkit/termkit.cpp"
#include "../affichage/dicte.cpp"

using namespace std;

int PFC(int degats) {
    char choix = ' ';
    int degats_total = 0;

    bool fin_jeu = false;

    int jeu_ennemi = 0;
    char jeu_ennemi_char = ' ';
    
    while (fin_jeu == false) {
        termkit::clear();
        cout<<"\n     █████████   ███████████   █████ █████\n    ███░░░░░███ ░░███░░░░░███ ░░███ ░░███ \n   ░███    ░███  ░███    ░███  ░░███ ███  \n   ░███████████  ░██████████    ░░█████   \n   ░███░░░░░███  ░███░░░░░███    ███░███  \n   ░███    ░███  ░███    ░███   ███ ░░███ \n   █████   █████ █████   █████ █████ █████\n  ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ \n"<<endl;
        cout << "\n     Vous avez rencontré un ennemi ! Gagnez le combat pour ne pas perdre de points de vie." << endl;
        cout << "     Dégats de l'ennemi : " << degats << endl;

        // Jeu du PFC

        cout << "\n     Pour le vaincre, gagnez ce Pierre Feuille Ciseaux." << endl;
        cout << "     - Tapez 'P' pour jouer Pierre," << endl;
        cout << "     - Tapez 'F' pour jouer Feuille," << endl;
        cout << "     - Tapez 'C' pour jouer Ciseaux," << endl;
        cout << "     Votre choix : ";

        cin >> choix;

        while (choix != 'P' && choix != 'F' && choix != 'C' && choix != 'p' && choix != 'f' && choix != 'c') {
            cout << "\n     [!] Erreur lors de la saisie de votre choix, veuillez réessayer." << endl;
            cout << "     Votre choix : ";
            cin >> choix;
        }

        jeu_ennemi = rand() % 3; // Conversion du jeu ennemi en caractère pour comprendre plus facilement

        if (jeu_ennemi == 0) jeu_ennemi_char = 'P';
        else if (jeu_ennemi == 1) jeu_ennemi_char = 'F';
        else if (jeu_ennemi == 2) jeu_ennemi_char = 'C';

        // Détermination du gagnant

        if (jeu_ennemi_char == choix) {
            cout << "\n     Vous avez joué la même attaque ! Vous perdez " << degats << " points de vie" << endl;
            cout << "     Appuyez sur une touche pour revenir au donjon..." << endl;
            degats_total += degats;
            return degats_total;
        }
        else if ((jeu_ennemi_char == 'P' && (choix == 'C' || choix == 'c'))
        || (jeu_ennemi_char == 'F' && (choix == 'P' || choix == 'p'))
        || (jeu_ennemi_char == 'C' && (choix == 'F' || choix == 'f'))) {
            cout << "\n     Vous avez perdu face a l'ennemi ! Vous perdez " << degats/2 << " points de vie" << endl;
            cout << "     Recommencez !" << endl;
            degats_total += degats/2;
            Attente(3);
        }
        else {
            cout << "\n     Vous avez gagné face a l'ennemi !" << endl;
            cout << "     Appuyez sur une touche pour revenir au donjon..." << endl;
            return degats_total;
        }
    }
}