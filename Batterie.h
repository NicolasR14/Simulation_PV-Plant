#ifndef BATTERIE_H_
#define BATTERIE_H_
#include <iostream>
#include <string>

using namespace std;

class Batterie {
private:
    string type;
    float charge;
    float capacite; //en Ah
    float tension_entree_sortie;
    float prix;

public:
    //Constructeurs
    Batterie(string,float, float, float);

    //Destructeur
    virtual ~Batterie();

    //Accesseur
    float getCharge(); //y'a t'il assez de charge pour une heure ? pas moins de 70% pour durée de vie max
    float getCapacite();
    float getPrix();
    //Méthode
    float getTension();
    string getType();
    void ChargerBatterie(); //charger la batterie pendant l'heure
    void DechargerBatterie(); //decharger la batteire pendant l'heure
};
#endif 