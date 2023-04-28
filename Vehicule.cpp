#include "Vehicule.h"
#include <iostream>
//Constructeurs
    Vehicule::Vehicule(string t,float capa, float tens, float conso, float p){
    type=t;
    capacite=capa;
    charge=capa;
    tension_entree_sortie=tens;
    presenceVehicule=true;
    consoAuKm=conso;
    prix = p;
    }

    //Destructeur
    Vehicule::~Vehicule(){

    }

    //Accesseur
    float Vehicule::getTension(){
        return tension_entree_sortie;
    }

    string Vehicule::getType(){
        return type;
    }

    float Vehicule::getPrix(){
        return prix;
    }

    float Vehicule::getCharge(){
        return charge;
    } //y'a t'il assez de charge pour une heure ?

    float Vehicule::getCapacite(){
        return capacite;
    }

    bool Vehicule::isReady(float nb_km){
        chargeRequisePourVoyage=consoAuKm*nb_km;
        if (charge>=chargeRequisePourVoyage){
        return true;
        }
        else return false;
    }; //Est-il prêt pour voyager

    bool Vehicule::isPresent(){
        if (presenceVehicule==true)
        return true;
        else return false;
    } //le vehicule est présent ?

    float Vehicule::getConso(){
        return consoAuKm;
    }

  /*  bool Vehicule::isAvalaibleToUse(){
        if (isPresent()==true&&besoinVehiculeProchainJour==false&&isCharged()==true)
            return true;
            else return false;
    } //dispo pour charger ? présent et chargé pour l'heure et pas de besoin vehicule prochain jour*/
    
    //Méthode
    void Vehicule::ChargerBatterie(){
        if (charge<=(capacite-tension_entree_sortie)){
            charge+=tension_entree_sortie*1;
        }
        else cout << "erreur" << endl;
    } //charger la batterie pendant l'heure

    void Vehicule::DechargerBatterie(){
        if(charge>(0.3*capacite+tension_entree_sortie)){
        charge-=tension_entree_sortie*1;
    }
    else cout << "erreur charge 2" << endl;
    } //decharger la batteire pendant l'heure

    void Vehicule::setPresent(bool pres){
        if(pres==true) presenceVehicule=false;
        else presenceVehicule==true;
        }//Indiquer un besoin de vehicule prochainJour

    void Vehicule::retourVehicule(float nbkm){
        charge=charge-nbkm*consoAuKm;
    }