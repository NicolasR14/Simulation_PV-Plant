#include <iostream>
#include "Panneau.h"
#include "Batterie.h"
#include "Vehicule.h"
#include "Compteur.h"
#include <string>
#include <fstream>
#include "simulation.h"

int definir_Mode(float conso,float prod, bool util_vehic, Batterie *b, Vehicule *v, Compteur *c, float nb_km){
/*
    Mode 10 = Mode solaire pour appareils electriques + stockage batterie vehicules 
    Mode 11 = Mode solaire pour appareils electriques + stockage batterie vehicules + stockage batterie
    Mode 12 = Mode solaire pour appareils electriques + stockage batterie vehicules + stockage batterie + vente edf
    Mode 13 = Mode solaire pour appareils electriques + stockage batterie
    Mode 14 = Mode solaire pour appareils electriques + stockage batterie + vente edf
    Mode 15 = Mode solaire pour appareils electriques + vente edf
    Mode 16 = Mode solaire pour appareils electriques + stockage batterie vehicules + vente edf
    Mode 20 = (heure pleine) Mode batterie pour appareils electriques
    Mode 21 = (heure pleine) Mode batterie pour appareils electriques + achat Edf batterie vehicules
    Mode 30 = Mode achat EdF pour appareils electriques
    Mode 31 = Mode achat EdF pour appareils electriques + achat EdF batterie vehicules
    Mode 32 = (heure creuse) Mode achat EdF pour appareils electriques + achat EdF batterie vehicules + achat Edf batterie
    Mode 33 = (heure creuse)  Mode achat EdF pour appareils electriques + achat EdF batterie
    Mode 40 = Mode VtoG pour appareils electriques
*/
    if(c->isHeurePleine()==true){ //Heure pleine
        if(conso<=prod){ //Conso < prod
            if(v->getCharge()<(v->getCapacite()-v->getTension())){ //vehicule pas chargé
                if(prod>=(conso+v->getTension())&&prod<(conso+v->getTension()+b->getTension())){ //Surplus suffisant juste pour vehicule
                    return 10;
                }
                else { //Surplus suffisant pour + que vehicule
                    if(b->getCharge()<(b->getCapacite()-b->getTension())){  //batterie pas chargée
                        if(prod==(conso+v->getTension()+b->getTension())){ //Surplus suffisant juste pour vehicule + batteries
                            return 11; 
                        }
                        else if(prod>(conso+v->getTension()+b->getTension())||prod<(conso+v->getTension()+b->getTension()))//Surplus suffisant pour vehicule + batterie + vente edf
                            return 12;
                    }
                    else if(prod>(conso+v->getTension())||prod<(conso+v->getTension()))//batterie chargée
                        return 16;
                }
            } 
            else {//vehicule chargé
                if(b->getCharge()<(b->getCapacite()-b->getTension())){ //batterie pas chargée
                    if(prod==(conso+b->getTension())){ //surplus suffisant juste pour batterie
                        return 13;
                    }
                    else if(prod>(conso+b->getTension())||prod<(conso+b->getTension()))//surplus suffisant pour batterie + vente edf
                        return 14;
                }
                else //batterie chargée
                    return 15;
            }
        }
        else{ //Conso > prod
            if (b->getCharge()>(0.3*b->getCapacite()+b->getTension())){ //Batterie chargée
                if(util_vehic==true&&v->isReady(nb_km)==false&&v->isPresent()==true&&v->getCharge()<(v->getCapacite()-v->getTension())){ //besoin vehicule bientôt et vehicule pas prêt
                    return 21;
                }
                else //pas besoin vehicule ou déjà prêt ou pas là ou déjà chargé
                return 20;
            }
            else {//Batterie pas chargée
                if(v->getCharge()<(v->getCapacite()-v->getTension())){ //Vehicule pas chargé
                    if(util_vehic==true&&v->isReady(nb_km)==false&&v->isPresent()==true&&v->getCharge()<(v->getCapacite()-v->getTension())){ //besoin vehicule bientôt et vehicule pas prêt
                        return 31;
                    }
                    else //pas besoin vehicule ou déjà prêt ou pas là ou déjà chargé
                        return 30;
                } 
            else{ //Vehicule chargé
                if (util_vehic==false&&v->isPresent()==true){ //si pas besoin vehicule prochain jour
                return 40;
                } 
                else  //si besoin vehicule prochain jour
                    return 30;
                }
            }
        }
    }
    else {//heure creuse
        if(conso<=prod){ //Conso < prod
            if(v->getCharge()<(v->getCapacite()-v->getTension())){ //vehicule pas chargé
                if(prod>=(conso+v->getTension())&&prod<(conso+v->getTension()+b->getTension())){ //Surplus suffisant juste pour vehicule
                    return 10;
                }
                else { //Surplus suffisant pour + que vehicule
                    if(b->getCharge()<(b->getCapacite()-b->getTension())){  //batterie pas chargée
                        if(prod==(conso+v->getTension()+b->getTension())){ //Surplus suffisant juste pour vehicule + batteries
                            return 11; 
                        }
                        else if(prod>(conso+v->getTension()+b->getTension())||prod<(conso+v->getTension()+b->getTension()))//Surplus suffisant pour vehicule + batterie + vente edf
                            return 12;
                    }
                    else //batterie chargée
                        return 16;
                }
            } 
            else {//vehicule chargé
                if(b->getCharge()<(b->getCapacite()-b->getTension())){ //batterie pas chargée
                    if(prod==(conso+b->getTension())){ //surplus suffisant juste pour batterie
                        return 13;
                    }
                    else if(prod>(conso+b->getTension())||prod<(conso+b->getTension()))//surplus suffisant pour batterie + vente edf
                        return 14;
                }
                else //batterie chargée
                    return 15;
            }
        }
        else{ //Conso > prod
            //if(manque==true){ //manque prod dans prochaines heures
                if(b->getCharge()<(b->getCapacite()-b->getTension())){ //batterie pas chargée
                    if(v->getCharge()<(v->getCapacite()-v->getTension())){ //vehicule pas chargé
                        return 32;
                    }
                    else //vehicule chargé
                        return 33;
                }
                else {//batterie chargée
                    if(v->getCharge()<(v->getCapacite()-v->getTension())){ //vehicule pas chargé
                        return 31;
                    }
                    else //vehicule chargé
                        return 30;
                }
            /*}
            else{ //pas de manque de prod prévu
                if (b.isCharged()==true){ //Batterie chargée
                    if(util_vehic==true&&v.isReady(nb_km)==false&&v.isPresent()==true&&v.isCharged()==false){ //besoin vehicule bientôt et vehicule pas prêt
                        return 21;
                    }
                    else //pas besoin vehicule ou déjà prêt ou pas là ou déjà chargé
                    return 20;
                }
                else {//Batterie pas chargée
                    if(v.isCharged()==false){ //Vehicule pas chargé
                        if(util_vehic==true&&v.isReady(nb_km)==false&&v.isPresent()==true&&v.isCharged()==false){ //besoin vehicule bientôt et vehicule pas prêt
                            return 31;
                        }
                        else //pas besoin vehicule ou déjà prêt ou pas là ou déjà chargé
                            return 30;
                    } 
                else{ //Vehicule chargé
                    if (util_vehic==false&&v.isPresent()==true){ //si pas besoin vehicule prochain jour
                    return 40;
                    } 
                    else  //si besoin vehicule prochain jour
                        return 30;
                    }
                }
            }*/
        }
    }
    cout << "erreur" << endl;
    return 0;
}

void definir_Surfaces(float * s1, float * i1,string* o1,float * s2, float * i2,string * o2){
int nb_surfaces;
float surface_m2_p1=0;
float incli_deg_p1=0;
string ori_deg_p1="sud";
float surface_m2_p2=0;
float incli_deg_p2=0;
string ori_deg_p2="sud";

cout << "Nombre de surfaces à couvrir ? ";
cin >> nb_surfaces;
cout << "Surface numéro 1 :"<<endl;
cout << "Surface (m^2) : "<< endl;
cin >> surface_m2_p1;
cout << "Inclinaison (deg) : (0;30;45;60;90)"<<endl;
cin >> incli_deg_p1;
cout << "Orientation : (est;sud-est;sud;sud-ouest;ouest)"<<endl;
cin >> ori_deg_p1;

if (nb_surfaces==2){
    cout << "Surface numéro 2 :"<< endl;
    cout << "Surface (m^2) : " << endl;
    cin >> surface_m2_p2;
    cout << "Inclinaison (deg) : (0;30;45;60;90)";
    cin >> incli_deg_p2;
    cout << "Orientation : (est;sud-est;sud;sud-ouest;ouest)"<<endl;
    cin >> ori_deg_p2;
}
*s1=surface_m2_p1;
*s2=surface_m2_p2;
*i1=incli_deg_p1;
*i2=incli_deg_p2;
*o1=ori_deg_p1;
*o2=ori_deg_p2;
}

void simulation(Panneau p1, Panneau p2, Batterie b1,Compteur c1,Vehicule v1){ //Type de client : conso client, utilisation voiture (jour/heure utilisation + nb de km)
///////////////////////////Initialisation variables/////////////////////////////////
    float consommation[365][24]; //consommation par jour et par heure
    bool utilisation_vehicule[365][24]; //utilisation des vehicules par jour et par heure
    float ensoleillement[365][24]; //ensoleillement (Wh/m^2) par jour et par heure
    bool heures_pleines[24];
    float nb_km[365];
    bool util_vehic;
    int mode;
    int heure;
    int jour;
    float consoHeure;
    float prodHeure;
    float ensoleilHeure;
    float consoExcelAv[8760];
    float consoExcelAvCout[8760];
    float consoExcelAp[8760];
    float consoExcelApCout[8760];

///////////////////////////Réglages////////////////////////////////////////////////
//Heures pleines/creuses
    for (int h=0;h<8;h++){
        heures_pleines[h]=false;
    }
    for (int h=8;h<12;h++){
        heures_pleines[h]=true;
    }
    for (int h=12;h<16;h++){
        heures_pleines[h]=false;
    }
    for (int h=16;h<21;h++){
        heures_pleines[h]=true;
    }
    for (int h=21;h<24;h++){
        heures_pleines[h]=false;
    }
//ensoleillement
ifstream donneesSoleil("bourges_ensoleillement.csv");
string ligne;
for (int j=0;j<365;j++){
    for (int h=0;h<24;h++){
        getline(donneesSoleil,ligne);
        ensoleillement[j][h]=stof(ligne);
    }
}

//utilisation vehicule
ifstream util_vehicule("util_vehic.csv");
string ligneVehi;
getline(util_vehicule,ligneVehi);
float nb_km_semaine=stof(ligneVehi);
for (int h=0;h<24;h++){ //semaine
        getline(util_vehicule,ligneVehi);
        if (stof(ligneVehi)==1){
            utilisation_vehicule[0][h]==true;
        }
        else utilisation_vehicule[0][h]==false;
    }
for (int h=0;h<24;h++){ //week end
        getline(util_vehicule,ligneVehi);
        if (stof(ligneVehi)==1){
            utilisation_vehicule[0][h]==true;
        }
        else utilisation_vehicule[0][h]==false;
    }

for (int j=0;j<364;j++){
    for (int j_s=0;j_s<5;j_s++){
        nb_km[j]=nb_km_semaine;
        for (int h=0;h<24;h++){
        if (j+j_s!=0)
        utilisation_vehicule[j+j_s][h]=utilisation_vehicule[0][h];
        }
    }
    for (int j_s=5;j_s<7;j_s++){
        for (int h=0;h<24;h++){
        if (j+j_s!=5)
        utilisation_vehicule[j+j_s][h]=utilisation_vehicule[0][h];
        }
    }
    j++;j++;j++;j++;j++;j++;
}
for (int h=0;h<24;h++){
        utilisation_vehicule[364][h]=utilisation_vehicule[0][h];
    }


////Consommation
ifstream consoClient("consoClientImport.csv");
string ligneConso;
for (int h=0;h<24;h++){ //semaine
        getline(consoClient,ligneConso);
        consommation[0][h]=stof(ligneConso);
    }
for (int h=0;h<24;h++){ //week end
        getline(consoClient,ligneConso);
        consommation[5][h]=stof(ligneConso);
    }

for (int j=0;j<364;j++){
    for (int j_s=0;j_s<5;j_s++){
        for (int h=0;h<24;h++){
        if (j+j_s!=0)
        consommation[j+j_s][h]=consommation[0][h];
        }
    }
    for (int j_s=5;j_s<7;j_s++){
        for (int h=0;h<24;h++){
        if (j+j_s!=5)
        consommation[j+j_s][h]=consommation[0][h];
        }
    }
    j++;j++;j++;j++;j++;j++;
}
for (int h=0;h<24;h++){
        consommation[364][h]=consommation[0][h];
    }




///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Dynamique//////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
int heure_annee=0;
for(jour=0;jour<365;jour++){
   for(heure=0;heure<24;heure++){
///////////////////////////Paramètres de l'heure///////////////////////////////////
    ensoleilHeure=ensoleillement[jour][heure];
    consoHeure = consommation[jour][heure];
    prodHeure = p1.getProduction(ensoleillement[jour][heure]);
    c1.ajoutProduction(prodHeure);
    v1.setPresent(utilisation_vehicule[jour][heure]);
    c1.setHeurePleine(heures_pleines[heure]);
    //Définition util_vehic (Besoin du vehicule ajd ou demain)
    if (nb_km[jour]!=0||nb_km[jour+1]!=0){
        util_vehic = true;
    }
    else util_vehic = false;
    consoExcelAv[heure_annee]=consoHeure;
    if(c1.isHeurePleine()==true){
        consoExcelAvCout[heure_annee]=consoHeure*c1.getPrixHP();
    }
    else consoExcelAvCout[heure_annee]=consoHeure*c1.getPrixHC();

    ///Mise à jour charge véhicule
    if (v1.isPresent()==true && utilisation_vehicule[jour][heure-1]==false){//le véhicule est revenu !
        v1.retourVehicule(nb_km[jour]); //On met à jour la charge du véhicule
    }

///////////////////////////////////////Action//////////////////////////////////////
    mode=definir_Mode(consoHeure,prodHeure,util_vehic,&b1,&v1,&c1,nb_km[jour]);
    cout << " /// Jour : " << jour << " , Heure : " << heure << endl;
    cout << "     Production des panneaux durant l'heure : " << prodHeure << " Wh" << endl; 
    cout << "     Mode : " << mode << endl << endl;
    switch (mode)
    {
        case 10:
        c1.ajoutAutoconso(consoHeure+v1.getTension());
        v1.ChargerBatterie();
        consoExcelAp[heure_annee]=0;
        consoExcelApCout[heure_annee]=0;
        break;
        
        case 11:
        c1.ajoutAutoconso(consoHeure+v1.getTension()+b1.getTension());
        v1.ChargerBatterie();
        b1.ChargerBatterie();
        consoExcelAp[heure_annee]=0;
        consoExcelApCout[heure_annee]=0;
        break;

        case 12:
        consoExcelAp[heure_annee]=0;
        if(prodHeure<consoHeure+v1.getTension()){
            c1.ajoutAutoconso(consoHeure);
            c1.ajoutVenteEdf(prodHeure-consoHeure);
            consoExcelApCout[heure_annee]=-(prodHeure-consoHeure)*c1.getPrixVt();
        }
        if(prodHeure>=consoHeure+v1.getTension()&&prodHeure<consoHeure+v1.getTension()+b1.getTension()){
            c1.ajoutAutoconso(consoHeure+v1.getTension());
            v1.ChargerBatterie();
            c1.ajoutVenteEdf(prodHeure-consoHeure-v1.getTension());
            consoExcelApCout[heure_annee]=-(prodHeure-consoHeure-v1.getTension())*c1.getPrixVt();
        }
        if(prodHeure>=consoHeure+v1.getTension()+b1.getTension()){
            c1.ajoutAutoconso(consoHeure+v1.getTension()+b1.getTension());
            v1.ChargerBatterie();
            b1.ChargerBatterie();
            c1.ajoutVenteEdf(prodHeure-consoHeure-v1.getTension()-b1.getTension());
            consoExcelApCout[heure_annee]=-(prodHeure-consoHeure-v1.getTension()-b1.getTension())*c1.getPrixVt();
        }
        break;

        case 13:
        consoExcelAp[heure_annee]=0;
        c1.ajoutAutoconso(consoHeure+b1.getTension());
        b1.ChargerBatterie();
        consoExcelApCout[heure_annee]=0;
        break;

        case 14:
        consoExcelAp[heure_annee]=0;
        if(prodHeure<consoHeure+b1.getTension()){
            c1.ajoutAutoconso(consoHeure);
            c1.ajoutVenteEdf(prodHeure-consoHeure);
            consoExcelApCout[heure_annee]=-(prodHeure-consoHeure)*c1.getPrixVt();
        }
        if(prodHeure>=consoHeure+b1.getTension()){
            c1.ajoutAutoconso(consoHeure+b1.getTension());
            b1.ChargerBatterie();
            c1.ajoutVenteEdf(prodHeure-consoHeure-b1.getTension());
            consoExcelApCout[heure_annee]=-(prodHeure-consoHeure-b1.getTension())*c1.getPrixVt();
        }
        break;

        case 15:
        consoExcelAp[heure_annee]=0;
        c1.ajoutAutoconso(consoHeure);
        c1.ajoutVenteEdf(prodHeure-consoHeure);
        consoExcelApCout[heure_annee]=-(prodHeure-consoHeure)*c1.getPrixVt();
        break;

        case 16:
        consoExcelAp[heure_annee]=0;
        if(prodHeure<consoHeure+v1.getTension()){
            c1.ajoutAutoconso(consoHeure);
            c1.ajoutVenteEdf(prodHeure-consoHeure);
            consoExcelApCout[heure_annee]=-(prodHeure-consoHeure)*c1.getPrixVt();
        }
        if(prodHeure>=consoHeure+v1.getTension()){
            c1.ajoutAutoconso(consoHeure+v1.getTension());
            v1.ChargerBatterie();
            c1.ajoutVenteEdf(prodHeure-consoHeure-v1.getTension());
            consoExcelApCout[heure_annee]=-(prodHeure-consoHeure-v1.getTension())*c1.getPrixVt();
        }
        break;

        case 20:
        consoExcelAp[heure_annee]=0;
        b1.DechargerBatterie();
        consoExcelApCout[heure_annee]=0;
        break;

        case 21:
        
        b1.DechargerBatterie();
        v1.ChargerBatterie();
        c1.ajoutConsommation(v1.getTension());
        consoExcelAp[heure_annee]=v1.getTension();
        if(c1.isHeurePleine()==true){
            consoExcelApCout[heure_annee]=v1.getTension()*c1.getPrixHP();
            }
        else consoExcelApCout[heure_annee]=v1.getTension()*c1.getPrixHC();
        break;

        case 30:
        consoExcelAp[heure_annee]=consoHeure;
        c1.ajoutConsommation(consoHeure);
        c1.ajoutVenteEdf(prodHeure);
        if(c1.isHeurePleine()==true){
            consoExcelApCout[heure_annee]=consoHeure*c1.getPrixHP()-prodHeure*c1.getPrixVt();
            }
        else consoExcelApCout[heure_annee]=consoHeure*c1.getPrixHC()-prodHeure*c1.getPrixVt();
        break;

        case 31:
        consoExcelAp[heure_annee]=consoHeure+v1.getTension();
        v1.ChargerBatterie();
        c1.ajoutConsommation(consoHeure+v1.getTension());
        c1.ajoutVenteEdf(prodHeure);
        if(c1.isHeurePleine()==true){
            consoExcelApCout[heure_annee]=(consoHeure+v1.getTension())*c1.getPrixHP()-prodHeure*c1.getPrixVt();
            }
        else consoExcelApCout[heure_annee]=(consoHeure+v1.getTension())*c1.getPrixHC()-prodHeure*c1.getPrixVt();
        break;

        case 32:
        c1.ajoutConsommation(consoHeure+v1.getTension()+b1.getTension());
        consoExcelAp[heure_annee]=consoHeure+v1.getTension()+b1.getTension();
        v1.ChargerBatterie();
        b1.ChargerBatterie();
        c1.ajoutVenteEdf(prodHeure);
        if(c1.isHeurePleine()==true){
            consoExcelApCout[heure_annee]=(consoHeure+v1.getTension()+b1.getTension())*c1.getPrixHP()-prodHeure*c1.getPrixVt();
            }
        else consoExcelApCout[heure_annee]=(consoHeure+v1.getTension()+b1.getTension())*c1.getPrixHC()-prodHeure*c1.getPrixVt();
        break;

        case 33:
        b1.ChargerBatterie();
        c1.ajoutConsommation(consoHeure+b1.getTension());
        consoExcelAp[heure_annee]=consoHeure+b1.getTension();
        c1.ajoutVenteEdf(prodHeure);
        if(c1.isHeurePleine()==true){
            consoExcelApCout[heure_annee]=(consoHeure+b1.getTension())*c1.getPrixHP()-prodHeure*c1.getPrixVt();
            }
        else consoExcelApCout[heure_annee]=(consoHeure+b1.getTension())*c1.getPrixHC()-prodHeure*c1.getPrixVt();
        break;

        case 40:
        v1.DechargerBatterie();
        consoExcelApCout[heure_annee]=0;
        break;
    }
    //cout << "jour : " << jour+1 << " ,heure : " << heure+1 << ", mode : " << mode << endl;
    heure_annee++;
   }

}

    ofstream fconsoExcelAv("consoExcelAv.csv"); //conso sans installation
    ofstream fconsoExcelAp("consoExcelAp.csv"); //conso avec installation
    ofstream fconsoExcelAvCout("consoExcelAvCout.csv");
    ofstream fconsoExcelApCout("consoExcelApCout.csv");

    for (int i=0 ; i<8760 ; i++){
        fconsoExcelAv << consoExcelAv[i] << endl;
        fconsoExcelAp << consoExcelAp[i] << endl;
        fconsoExcelAvCout << consoExcelAvCout[i] << endl;
        fconsoExcelApCout << consoExcelApCout[i] << endl;
    }





int nb_km_an=0;
for (int j=0; j<365;j++){
    nb_km_an+=nb_km[j];
}
    cout << endl << "///////////////////////////Test configuration : panneau : " << p1.getType() << " , voiture : " << v1.getType() << " , batterie : " << b1.getType() << "/////////" << endl;
    cout << endl << "Vente Edf : " << c1.getVenteEdf() << " Wh soit " << c1.getVenteEdfCout() << " €" << endl;
    cout << "Production : " << c1.getProductionAnnuelle() << " Wh" << endl;
    cout << "Autoconsommation : " << c1.getAutoconsommationAnnuelle() << " Wh soit " << c1.getAutoconsommationAnnuelleCout() << " € économisés" << endl;    
    cout << "Achat Edf : " << c1.getConsoAnnuelle() << " Wh soit " << c1.getConsoAnnuelleCout() << " € dépensés" << endl << endl;
    cout << "Economie essence par an : " << (nb_km_an*1.40)/6 << " €" << endl;
    cout << endl << "Budget : " << v1.getPrix()+b1.getPrix()+p1.getPrix() << " €" << "  Rentabilité : " << c1.getVenteEdfCout()+c1.getAutoconsommationAnnuelleCout()+(nb_km_an*1.40)/6 << " € par an";
    cout << endl << "Installation rentable dans " << (b1.getPrix()+p1.getPrix()+(nb_km_an*1.40)/6)/(c1.getVenteEdfCout()+c1.getAutoconsommationAnnuelleCout()) << " ans. (véhicule non inclus)" << endl;
}
