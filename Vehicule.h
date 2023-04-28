#ifndef VEHICULE_H_
#define VEHICULE_H_
#include <iostream>
#include <string>

using namespace std;

class Vehicule {
private:
    string type;
    float charge;
    float capacite;
    float consoAuKm;
    float tension_entree_sortie;
    float chargeRequisePourVoyage;
    bool presenceVehicule;
    float prix;
public:
    //Constructeurs
    Vehicule(string,float, float, float, float);

    //Destructeur
    virtual ~Vehicule();

    //Accesseur
    float getCharge(); //y'a t'il assez de charge pour une heure ?
    bool isReady(float); //Est-il prêt pour voyager
    bool isPresent(); //le vehicule est présent ?
    float getTension();
    float getCapacite();
    float getConso();
    float getPrix();
    string getType();
    
    
    //Méthode
    void ChargerBatterie(); //charger la batterie pendant l'heure
    void DechargerBatterie(); //decharger la batteire pendant l'heure
    void setPresent(bool); //Indiquer un besoin de vehicule
    void retourVehicule(float);
};
#endif 