#include <iostream>
#include <time.h>

using namespace std;

void FauxChargement(int latence) {  // Latence = potentiel délai en ms pour faire 5%
	srand(time(NULL));
	string chargement="█";
	string chargement2="░░░░░░░░░░░░░░░░░░░";
	int pourcent=5;
	for (int i=0; i<20; ++i) {
		system("clear");
		cout<<"\n	Chargement : ";
		cout<<chargement<<chargement2<<" - "<<pourcent<<"%"<<endl;
		chargement=chargement+"█";
		chargement2.pop_back();
		chargement2.pop_back();
		chargement2.pop_back();
		pourcent=pourcent+5;
		Sleep((rand() % latence)+1);
	}
}