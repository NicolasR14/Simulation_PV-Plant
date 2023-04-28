#include "Compteur.h"
#include <iostream>

//Constructeur
Compteur::Compteur(float prixHP,float prixHC,float prixVt){
    heurePleine==true;
    prixHeureCreuse=prixHC;
    prixHeurePleine=prixHP;
    prixVente=prixVt;

    productionAnnuelle = 0;
    autoconsommationAnnuelleCout = 0;
    autoconsommationAnnuelle = 0;
    consommationAnnuelle = 0;
    consommationAnnuelleCout = 0;
    venteEdf = 0;
    venteEdfCout = 0;

}

//Accesseurs
    float Compteur::getPrixHP(){
        return prixHeurePleine;
    }

    float Compteur::getPrixHC(){
        return prixHeureCreuse;
    }

    float Compteur::getPrixVt(){
        return prixVente;
    }

    bool Compteur::isHeurePleine(){
        if (heurePleine==true)
        return true;
        else return false;
    }
    float Compteur::getConsoAnnuelle(){
        return consommationAnnuelle;
    }
    float Compteur::getConsoAnnuelleCout(){
            return consommationAnnuelleCout;
    }
    float Compteur::getProductionAnnuelle(){
        return productionAnnuelle;
    }
    float Compteur::getAutoconsommationAnnuelle(){
        return autoconsommationAnnuelle;
    }

    float Compteur::getVenteEdf(){
        return venteEdf;
    }

    float Compteur::getVenteEdfCout(){
        return venteEdfCout;
    }
    
    float Compteur::getAutoconsommationAnnuelleCout(){
        return autoconsommationAnnuelleCout;
    }


    //Methodes
    void Compteur::ajoutAutoconso(float autoconso){
        autoconsommationAnnuelle+=autoconso;
        if (isHeurePleine()==true)
        autoconsommationAnnuelleCout+=autoconso*prixHeurePleine;
        else autoconsommationAnnuelleCout+=autoconso*prixHeureCreuse;
    }

    void Compteur::ajoutProduction(float prod){
        productionAnnuelle+=prod;
    }



    void Compteur::ajoutConsommation(float conso){
        consommationAnnuelle+=conso;

        if (heurePleine==true)
        consommationAnnuelleCout+=conso*prixHeurePleine;
        else consommationAnnuelleCout+=conso*prixHeureCreuse;

    }
    void Compteur::setHeurePleine(bool h){
        heurePleine=h;
    }

    void Compteur::ajoutVenteEdf(float prodVendue){
        venteEdf+=prodVendue;
        /*
        if(heurePleine==true){
            venteEdfCout+=prodVendue*prixHeurePleine;
        }
        else venteEdfCout+=prodVendue*prixHeureCreuse;*/
         venteEdfCout+=prodVendue*prixVente;

    }