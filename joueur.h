#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include<bits/stdc++.h>

using namespace std;
class Jouer{
    //créer les attributs liée au jouer
    Plateau m_plateau; //la matrices de jeu
    bool partieEnCours; //si le joueur et encore n'a pas perdu cette valeur est true
public:
    Jouer();
    void joueur();
    void debut();
    bool getParieEnCours(){return partieEnCours;}
    void setParieEnCours(bool pec){partieEnCours=pec;}
    void action();
    void meilleurScore(char* n,char* p,int s);
    void menu();
    void scoreActuelle();
    ~Jouer(){};


};

#endif // JOUEUR_H_INCLUDED
