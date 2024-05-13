//BUSCH Léo
#include<iostream>
#include<string>
#include<windows.h>

//phrase est un string qui va être affiché charactère par charactère
//endligne est un bool qui exprime si une ligne est sauté à la fin du print 1=oui 0=non
//vites correspond au nombre de miliseconde entre chaque charactère
void dicte_phrase(std::string phrase,bool endligne, int vites){
	for (int i=0;i<=phrase.size();++i){
		std::cout<<phrase[i]<<std::flush;
		// flush permet d'afficher chaque cout un par un tel un endl sans le retour à la ligne que le endl offre
		Sleep(vites);
		// attendre autant de miliseconde que vites
	}
	if (endligne==1){std::cout<<std::endl;}
	// permet d'avoir 1 endl si la condition endligne est true
}

void Attente() {
    for (int i=0; i<5; ++i) {
		std::cout<<"    ";
		dicte_phrase(" ...",1,250);
		std::cout<<"\033[A\33[2K\r";
	}
}