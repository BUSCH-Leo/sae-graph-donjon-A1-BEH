#include <iostream>

using namespace std;

void AfficheTouche() {
    termkit::clear();

    cout << "\n      ____ ____ ____ \n     ||A |||Z |||E ||\n     ||__|||__|||__||\n     |/__\\|/__\\|/__\\|\n      ____ ____ ____ \n     ||Q |||S |||D ||\n     ||__|||__|||__||\n     |/__\\|/__\\|/__\\|" << endl;
    cout << "\n     Touches à utiliser :" << endl;
    cout << "     - Z, Q, S, D : Permettent de se déplacer dans le sens associé," << endl;
    cout << "     - A : Afficher le chemin le plus court depuis votre position (Il vous faut payer le Pass)," << endl;
    cout << "     - E : Vous permet d'ouvrir le Shop où vous voulez afin d'acheter des objets utiles." << endl;
    
    cout << "\n     Appuyez sur une touche pour continuer..." << endl;
    termkit::getch();

    return;
}