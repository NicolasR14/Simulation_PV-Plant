#include <iostream>
#include "Panneau.h"
#include "Batterie.h"
#include "Vehicule.h"
#include "Compteur.h"
#include <string>
#include <fstream>
int definir_Mode(float conso,float prod, bool util_vehic, Batterie *b, Vehicule *v, Compteur *c, float nb_km);
void definir_Surfaces(float * s1, float * i1,string* o1,float * s2, float * i2,string * o2);
void simulation(Panneau p1, Panneau p2, Batterie b1,Compteur c1,Vehicule v1);