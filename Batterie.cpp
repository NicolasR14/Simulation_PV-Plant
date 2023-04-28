#include "Batterie.h"
#include <iostream>

//Constructeur
Batterie::Batterie(string t, float c_max, float tension, float p){
    type=t;
    capacite=c_max;
    charge=0.7*c_max;
    tension_entree_sortie=tension;
    prix = p;
}

//Destructeur
Batterie::~Batterie(){

}

//Accesseur
float Batterie::getTension(){
        return tension_entree_sortie;
    }

float Batterie::getCharge(){
    return charge;
}

float Batterie::getCapacite(){
        return capacite;
    }

float Batterie::getPrix(){
    return prix;
}

string Batterie::getType(){
    return type;
}

//Méthode
void Batterie::ChargerBatterie(){
    if (charge<=(capacite-tension_entree_sortie)){
        charge+=tension_entree_sortie*1; //On charge de tension*1 Ah (correspond à une charge de 1h)
    }
    else cout << "erreur charge" << endl;
}

void Batterie::DechargerBatterie(){
    if(charge>(0.3*capacite+tension_entree_sortie)){
        charge-=tension_entree_sortie*1;
    }
    else cout << "erreur charge 2" << endl;
}
