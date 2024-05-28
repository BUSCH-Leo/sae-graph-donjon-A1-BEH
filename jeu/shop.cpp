#include <iostream>

using namespace std;

int Shop(int joueur_coins, bool pass_paye, float nb_bonus, bool visibilite) {
    int choix = 0;

    termkit::clear();

    cout << "\n     Bienvenue dans le magasin ! Voici votre argent : " << joueur_coins << " 💰" << endl;

    cout << "\n     Voici les articles possible :" << endl;
    cout << "     - Pass PlusCourtChemin (" << (visibilite ? "20" : "40") << " 💰)     -> Choix 1" << endl;
    cout << "     - InstaKill sur 1 ennemi (10 💰)   -> Choix 2" << endl;
    cout << "     - Potion de vie +5 ♥ (10 💰)       -> Choix 3" << endl;
    cout << "     - Téléportation aléatoire (5 💰)   -> Choix 4" << endl;
    cout << "     - Double l'argent des sacs (" << int(10*nb_bonus) << " 💰) -> Choix 5" << endl;
    cout << "     - Ressortir                        -> Choix 0" << endl;

    cout << "     Votre choix : ";
    cin >> choix;

    while (choix < 0 || choix > 5
    || (choix == 1 && joueur_coins - 20 < 0 && visibilite == true)
    || (choix == 1 && joueur_coins - 40 < 0 && visibilite == false)
    || (choix == 2 && joueur_coins - 10 < 0)
    || (choix == 3 && joueur_coins - 10 < 0)
    || (choix == 4 && joueur_coins - 5 < 0)
    || (choix == 5 && ((joueur_coins - int(10*nb_bonus)) < 0))
    || (pass_paye == true && choix == 1)
    ) {
        if (pass_paye == true && choix == 1) {
            cout << "\n     [!] Vous avez déjà payé ce Pass." << endl;
        }
        else {
            cout << "\n     [!] Erreur lors de la saisie ou argent insuffisant, veuillez réessayer." << endl;
        }
        cout << "     Votre choix : ";
        cin >> choix;
    }

    return choix;
}
