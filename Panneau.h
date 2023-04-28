#ifndef PANNEAU_H_
#define PANNEAU_H_
#include <iostream>
#include <string>

using namespace std;

class Panneau {
private:
//Données entrée
    string type;
    string orientation;
    int inclinaison_deg;
    float surface_m2;
    float prix;

//Données sorties
    float rendement_orientation;
    float production_W;

public:
    //Constructeurs
    Panneau(string,string,int,float,float);

    //Destructeur
    virtual ~Panneau();

    //Accesseur
    float getProduction(float); //calcul de la production en temps réel
    string getType();
    float getRendement_Ori();
    float getPrix();
    float getRendement_type();

};
#endif 