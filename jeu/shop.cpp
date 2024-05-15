#include <iostream>

using namespace std;

int Shop(int joueur_coins, bool pass_paye) {
    int choix = 0;

    termkit::clear();

    cout << "\n     Bienvenue dans le magasin ! Voici votre argent : " << joueur_coins << " 💰" << endl;

    cout << "\n     Voici les articles possible :" << endl;
    cout << "     - Pass PlusCourtChemin (15 💰)   -> Choix 1" << endl;
    cout << "     - InstaKill sur 1 ennemi (5 💰)  -> Choix 2" << endl;
    cout << "     - Potion de vie +5 ♥ (10 💰)     -> Choix 3" << endl;
    cout << "     - Téléportation aléatoire (5 💰) -> Choix 4" << endl;
    cout << "     - Ressortir                      -> Choix 0" << endl;

    cout << "     Votre choix : ";
    cin >> choix;

    while (choix < 0 || choix > 4 
    || (choix == 1 && joueur_coins - 15 < 0)
    || (choix == 2 && joueur_coins - 5 < 0)
    || (choix == 3 && joueur_coins - 10 < 0)
    || (choix == 4 && joueur_coins - 5 < 0)
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
