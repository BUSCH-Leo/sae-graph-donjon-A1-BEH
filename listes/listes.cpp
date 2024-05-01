#include <assert.h>
#include <iostream>

// Déclaration de la structure maillon
struct maillon {

	int val;
	maillon* suiv;
	maillon* prec;

};

// Déclaration de la structure liste
struct liste {

	maillon* tete;
	maillon* queue;

	// Fonction d'initialisation, automatiquement appelée lors de la création d'une variable de type liste
	// Plus de détails en S2 ! 
	liste() {
		tete = NULL;
		queue = NULL;	
	}
};

// Fonction qui ajoute en tête
void ajouterTete(liste & l, int value) {

	if(l.tete == NULL) {
	
		l.tete = new maillon;
		l.tete->val = value;
		l.tete->prec = NULL;
		l.tete->suiv = NULL;	
		l.queue = l.tete;
	} else {
	
		maillon* tmp = new maillon;
		tmp->val = value;
		tmp->suiv = l.tete;
		tmp->prec = NULL;
		l.tete->prec = tmp;
		l.tete = tmp;
	}
}

void ajouterQueue(liste & l, int value) {

	if(l.queue == NULL) ajouterTete(l,value);
	else {
	
		maillon* tmp = new maillon;
		tmp->val = value;
		tmp->suiv = NULL;
		tmp->prec = l.queue;
		l.queue->suiv = tmp;
		l.queue = tmp;
	
	}
}

int retirerTete(liste & l) {
	int tete_val=l.tete->val;

	if(l.tete != NULL) {
	
		if(l.tete->suiv != NULL) l.tete->suiv->prec = NULL;
		else l.queue = NULL;
	
		maillon* tmp = l.tete->suiv;
		delete l.tete;
		l.tete = tmp;
	
	}
	return tete_val;
}

int retirerQueue(liste & l) {
	int queue_val=l.queue->val;

	if(l.queue != NULL) {
	
		if(l.queue->prec != NULL) l.queue->prec->suiv = NULL;
		else l.tete = NULL;
	
		maillon* tmp = l.queue->prec;
		delete l.queue;
		l.queue = tmp;
	
	}
	return queue_val;
}

void affichageListeDetail(liste & l) {

	std::cout<<std::endl;
	std::cout<<"/////////////////////"<<std::endl;
	std::cout<<"Affichage de la liste"<<std::endl;
	std::cout<<"/////////////////////"<<std::endl;
	std::cout<<std::endl;

	maillon* tmp = l.tete;
	while(tmp != NULL) {
		
		std::cout<<"Maillon = "<<tmp<<std::endl;
		std::cout<<"Val = "<<tmp->val<<std::endl;
		std::cout<<"Suiv = "<<tmp->suiv<<std::endl;
		std::cout<<"Prec = "<<tmp->prec<<std::endl;
		std::cout<<std::endl;
		
		tmp = tmp->suiv;
		std::cout<<"-----------------"<<std::endl;
	}
	std::cout<<std::endl;
}

void affichageListeSimple(liste & l) {

	std::cout<<"- Affichage de la liste :"<<std::endl;

	maillon* tmp = l.tete;
	if (tmp == NULL) {
		std::cout<<"Vide\n"<<std::endl;
		return;
	}
	while(tmp != NULL) {
		
		std::cout<<"[ "<<tmp->val<<" ]";
		if (tmp->suiv!=NULL) {
			std::cout<<" - ";
		}
		
		tmp = tmp->suiv;
	}
	std::cout<<"\n"<<std::endl;
}

bool estVide(liste & l) {

	return (l.tete == NULL);

}

int valeurTete(liste & l) {

	assert(l.tete != NULL);
	return l.tete->val;

}

int valeurQueue(liste & l) {

	assert(l.tete != NULL);
	return l.queue->val;

}

void insertion(liste & l, int valeurInseree, int position) {

	if(position == 0 || l.tete == NULL) ajouterTete(l,valeurInseree);
	else  {
	
		maillon* courant = l.tete;
		int cpt = 0;
		while(cpt < position - 1 && courant->suiv != NULL) {
			courant = courant->suiv;
			cpt++;
		} 
		
		if(courant == l.queue) ajouterQueue(l,valeurInseree);
		else {
			maillon* tmp = new maillon;
			tmp->val = valeurInseree;
			tmp->suiv = courant->suiv;
			tmp->prec = courant;
			tmp->suiv->prec = tmp;
			tmp->prec->suiv = tmp;
		}
	}
}

void supprime(liste & l, int position) {

	if(l.tete != NULL) {
	
		maillon* courant = l.tete;
		int cpt = 0;
		while(cpt < position && courant->suiv != NULL) {
			courant = courant->suiv;
			cpt++;
		}
		
		if(courant == l.tete) retirerTete(l);
		else if(courant == l.queue) retirerQueue(l);
		else {
			courant->suiv->prec = courant->prec;
			courant->prec->suiv = courant->suiv;
			delete courant;
		}
	}
}

void supprimeListe(liste & l) {
	while(!estVide(l)) retirerTete(l);
}