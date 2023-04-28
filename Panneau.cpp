#include "Panneau.h"
#include <iostream>

//Constructeurs
Panneau::Panneau(string n,string ori,int incli, float sur, float p){
    type = n;
    orientation = ori;
    inclinaison_deg = incli;
    surface_m2 = sur;
    prix = p;
}

//Destructeur
Panneau::~Panneau(){
}


float Panneau::getRendement_Ori(){
    int val_incli;
    int val_ori;

    if (orientation=="ouest")
    {
        val_ori=0;
    }
    if (orientation=="sud-ouest")
    {
        val_ori=1;
    }
    if (orientation=="sud")
    {
        val_ori=2;
    }
    if (orientation=="sud-est")
    {
        val_ori=3;
    }
    if (orientation=="est")
    {
        val_ori=4;
    }

    switch (this->inclinaison_deg)
    {
        case 0:
            val_incli=0;
            break;
        case 30:
            val_incli=1;
            break;
        case 45:
            val_incli=2;
            break;
        case 60:
            val_incli=3;
            break;
        case 90:
            val_incli=4;
            break;
    }

    float tab_rend[5][5];
    //Inclinaison 0°
    tab_rend[0][0]=0.86; //Ouest
    tab_rend[0][1]=0.86; //Sud-Ouest
    tab_rend[0][2]=0.86; //Sud
    tab_rend[0][3]=0.86; //Sud-Est
    tab_rend[0][4]=0.86; //Est

    //Inclinaison 30°
    tab_rend[1][0]=0.80; //Ouest
    tab_rend[1][1]=0.93; //Sud-Ouest
    tab_rend[1][2]=1;    //Sud
    tab_rend[1][3]=0.93; //Sud-Est
    tab_rend[1][4]=0.80; //Est

    //Inclinaison 45°
    tab_rend[2][0]=0.74; //Ouest
    tab_rend[2][1]=0.94; //Sud-Ouest
    tab_rend[2][2]=0.98; //Sud
    tab_rend[2][3]=0.94; //Sud-Est
    tab_rend[2][4]=0.74; //Est

    //Inclinaison 60°
    tab_rend[3][0]=0.67; //Ouest
    tab_rend[3][1]=0.87; //Sud-Ouest
    tab_rend[3][2]=0.93; //Sud
    tab_rend[3][3]=0.87; //Sud-Est
    tab_rend[3][4]=0.67; //Est

    //Inclinaison 90°
    tab_rend[4][0]=0.51; //Ouest
    tab_rend[4][1]=0.65; //Sud-Ouest
    tab_rend[4][2]=0.67; //Sud
    tab_rend[4][3]=0.65; //Sud-Est
    tab_rend[4][4]=0.51; //Est

    return tab_rend[val_incli][val_ori];
}

float Panneau::getRendement_type(){
    if (type=="monocristallin")
    {
        return 0.21;
    }

    if (type=="polycristallin")
    {
        return 0.16;
    }
/*
    if (type=="monocristallin")
    {
        return 0.06;
    }*/
    return 0;
}

float Panneau::getPrix(){
    return prix;
}

string Panneau::getType(){
    return type;
}

//Accesseur
float Panneau::getProduction(float ensoleillement_Wrapm2){
    float rend_orientation = getRendement_Ori();
    float rendement_sol_elec = getRendement_type();
    return production_W = ensoleillement_Wrapm2*rend_orientation*rendement_sol_elec*surface_m2;
}

//Méthode
