#ifndef COMPTEUR_H_
#define COMPTEUR_H_
#include <iostream>
#include <string>

using namespace std;

class Compteur {
private:
    bool heurePleine;
    float prixHeurePleine;
    float prixHeureCreuse;
    float productionAnnuelle; //Wh
    float autoconsommationAnnuelle;
    float autoconsommationAnnuelleCout; //Coût économisé
    float consommationAnnuelle; //Wh
    float consommationAnnuelleCout; //Coût
    float venteEdf;
    float venteEdfCout;
    float prixVente;

public:
    //Constructeur
    Compteur(float,float,float);

    //Accesseurs
    bool isHeurePleine();
    float getAutoconsommationAnnuelle();
    float getConsoAnnuelle();
    float getConsoAnnuelleCout();
    float getProductionAnnuelle();
    float getAutoconsommationAnnuelleCout();
    float getVenteEdf();
    float getVenteEdfCout();
    float getPrixHP();
    float getPrixHC();
    float getPrixVt();

    //Methodes
    void ajoutProduction(float); //ajout Wh de production au compteur production Annuelle + calcul coût économmisé
    void ajoutAutoconso(float);
    void ajoutConsommation(float); //ajout Wh de consommation + calcul du coût selon heure
    void setHeurePleine(bool); //passer à heure pleine
    void ajoutVenteEdf(float);
};
#endif 