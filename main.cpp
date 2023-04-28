#include <iostream>
#include "Panneau.h"
#include "Batterie.h"
#include "Vehicule.h"
#include "Compteur.h"
#include <string>
#include <fstream>
#include "simulation.h"

int main(){
///////////////////////////////Données client////////////////////////////////////
cout << "Définition des données client :" << endl << endl;
///Surfaces disponibles pour panneau
float surface_m2_p1;
float incli_deg_p1;
string ori_deg_p1;
float surface_m2_p2;
float incli_deg_p2;
string ori_deg_p2;
definir_Surfaces(&surface_m2_p1,&incli_deg_p1,&ori_deg_p1,&surface_m2_p2,&incli_deg_p2,&ori_deg_p2);



///////////////////////////Configuration 1//////////////////////////////////////
    Panneau p1("polycristallin",ori_deg_p1,incli_deg_p1,surface_m2_p1,surface_m2_p1*350);
    Panneau p2("polycristallin",ori_deg_p2,incli_deg_p2,surface_m2_p2,surface_m2_p2*350);
    Batterie b1("Li12V60Ah", 60,12,581);
    Vehicule v1("Zoé",20, 2, 5.5,32000);
    Compteur c1(0.0001798,0.0001344,0.00018);

simulation(p1,p2,b1,c1,v1);

///////////////////////////Configuration 2//////////////////////////////////////
    Panneau p3("monocristallin",ori_deg_p1,incli_deg_p1,surface_m2_p1,surface_m2_p1*190);
    Panneau p4("monocristallin",ori_deg_p2,incli_deg_p2,surface_m2_p2,surface_m2_p2*190);
    Batterie b2("Li12V60Ah", 60,12,581);
    Vehicule v2("Zoé",20, 1, 2.2,32000);
    Compteur c2(0.0001798,0.0001344,0.00018);

simulation(p3,p4,b2,c2,v2);







return 0;
}



