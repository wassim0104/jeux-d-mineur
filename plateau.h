#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include<bits/stdc++.h>
#include "case.h"

using namespace std;

class Plateau{

    int m_diml,m_dimc;
    int nb_mine;
    Case  m_matrice [100][100];
    char  m_matriceCachee [100][100];
    int nb_drapeau;
    int nb_couts;
public:
    Plateau();
    Plateau(int diml,int dimc,int mine);
    void creerMatrice();
    void cacheMatrice();

    /*les voisins de la case [i][j]   */
    int getNWcase(int i,int j); //rendre la valeur de m_matrice[i-1][j-1]
    int getNcase(int i,int j); //rendre la valeur de m_matrice[i-1][j]
    int getNEcase(int i,int j); //rendre la valeur de m_matrice[i-1][j+1]
    int getWcase(int i,int j); //rendre la valeur de m_matrice[i][j-1]
    int getEcase(int i,int j); //rendre la valeur de m_matrice[i][j+1]
    int getSWcase(int i,int j); //rendre la valeur de m_matrice[i+1][j-1]
    int getScase(int i,int j); //rendre la valeur de m_matrice[i+1][j]
    int getSEcase(int i,int j); //rendre la valeur de m_matrice[i+1][j+1]
    int getNbDrapeau();
    int getNbMine();
    int getNbCouts(){return nb_couts;};
    /*remplir les cases du plateau aléatoirement par des bombes */
    void placerBombe();
    /*places les chiffres dans la matrices */
    void chiffrerMatrices();
    void affiche() ;
    int decouvrirCase(int i,int j);
    void afficheMatriceCachee();
    void perdu();
    void poserDrapeau(int i,int j);
    bool testerSiGagne();
    ~Plateau(){};

};
bool verifRand(vector<pair<int,int> >v,int a,int b);
#endif // PLATEAU_H_INCLUDED
