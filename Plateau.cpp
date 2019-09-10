#include "plateau.h"
#include<bits/stdc++.h>
#include <cstdlib>
#include<time.h>
#include"case.h"
#include "joueur.h"


using namespace std;


/*constructeur de la classe plateau*/
Plateau::Plateau(){
    m_diml=11;
    m_dimc=18;
    nb_mine=42;
    int  m_matrice [100][100];
    nb_drapeau=0;
    nb_couts=0;
}
Plateau::Plateau(int diml,int dimc,int mine):m_diml(diml),m_dimc(dimc),nb_mine(mine)
{
    nb_drapeau=0;
    nb_couts=0;
}

void Plateau::creerMatrice()
{
    //initialiser la matrice par des zeros dans chaque case

    int n= m_diml, m=m_dimc;
    for(int i=0;i<n;i++)
       for(int j=0 ; j<m ; j++)
         {
             //m_matrice[i][j]=0;
             Case c;
             m_matrice[i][j]=c;
         }

}

void Plateau::cacheMatrice()
{
    //cacher les cases de la matrice par une #
    for(int i=0;i<m_diml;i++)
        {
            for(int j=0;j<m_dimc;j++)
                {
                    m_matriceCachee[i][j]='#';
                }

        }
}
void Plateau::placerBombe()
{
    //placer les bombes dans la matrice aléa
    srand(time(NULL));//initialisation de rand
    vector<pair<int,int> > v;
    for(int i=0;i<nb_mine;i++)
    {
        int randli=rand() % m_diml; //genérer des entier aléa pour placer les mines
        int randcol=rand() % m_dimc ;
        //cout<<randli<<" "<<randcol<<endl;
        if(verifRand(v,randli,randcol))
        {
            i--;
            continue;
        }
        if (randli>=0 && randli<m_diml && randcol>=0 && randcol<m_dimc)
        {  m_matrice[randli][randcol].setValue(9);
        v.push_back(make_pair(randli,randcol));}

    }
}
    /*les voisins de la case [i][j]   */


    int Plateau::getNWcase(int i,int j)
    {
        if(i-1>=0 && j-1>=0)
            return m_matrice[i-1][j-1].getValue();
            else return -1;
    }
    int Plateau::getNcase(int i,int j)
    {
        if(j>=0 && i-1>=0) // najmou j na7youha
            return m_matrice[i-1][j].getValue();
            else return -1;
    }
    int Plateau::getNEcase(int i,int j)
    {
        if(i-1>=0 && j+1<m_dimc)
            return m_matrice[i-1][j+1].getValue();
            else return -1;
    }

    int Plateau::getWcase(int i,int j)
    {
        if(j-1>=0 && i>=0)// i najmou n7youha
            return m_matrice[i][j-1].getValue();
            else return -1;
    }
    int Plateau::getEcase(int i,int j)
    {
        if(j+1<m_dimc && i>=0)// i najmou n7youha!!
            return m_matrice[i][j+1].getValue();
            else return -1;
    }
    int Plateau::getSWcase(int i,int j)
    {
        if(i+1<m_diml && j-1>=0)
            return m_matrice[i+1][j-1].getValue();
            else return -1;
    }
    int Plateau::getScase(int i,int j)
    {
        if(i+1<m_diml && j>=0)// j najmou n7youha
            return m_matrice[i+1][j].getValue();
            else return -1;
    }
    int Plateau::getSEcase(int i,int j)
    {
        if(i+1<m_diml && j+1<m_dimc )
            return m_matrice[i+1][j+1].getValue();
            else return -1;
    }

/*--------------------------------------------*/

/*remplir la matrices par les chiffres selon le nombres de bombes au voisinage de chaque bombes */

void Plateau::chiffrerMatrices()
{
        int n=m_diml, m=m_dimc;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(m_matrice[i][j].getValue()==9) //si on trouve dans la case une mine,on ajoute a ses voisin un "1"
                                            // s'il existe ou s'il n'est pas une mine
                    {
                            if(getNWcase(i,j)!=-1 && getNWcase(i,j)!=9 )
                                m_matrice[i-1][j-1].setValue(m_matrice[i-1][j-1].getValue()+1);
                            if(getNcase(i,j)!=-1 && getNcase(i,j)!=9)
                                m_matrice[i-1][j].setValue(m_matrice[i-1][j].getValue()+1);
                            if(getNEcase(i,j)!=-1 && getNEcase(i,j)!=9)
                                m_matrice[i-1][j+1].setValue(m_matrice[i-1][j+1].getValue()+1);
                            if(getWcase(i,j)!=-1 && getWcase(i,j)!=9)
                                m_matrice[i][j-1].setValue(m_matrice[i][j-1].getValue()+1);
                            if(getEcase(i,j)!=-1 && getEcase(i,j)!=9)
                                m_matrice[i][j+1].setValue(m_matrice[i][j+1].getValue()+1);
                            if(getSWcase(i,j)!=-1 && getSWcase(i,j)!=9)
                                m_matrice[i+1][j-1].setValue(m_matrice[i+1][j-1].getValue()+1);
                            if(getScase(i,j)!=-1 && getScase(i,j)!=9)
                                m_matrice[i+1][j].setValue(m_matrice[i+1][j].getValue()+1);
                            if(getSEcase(i,j)!=-1 && getSEcase(i,j)!=9)
                                m_matrice[i+1][j+1].setValue(m_matrice[i+1][j+1].getValue()+1);
                    }
            }
        }
}

int Plateau::decouvrirCase(int i,int j)
{

    if(i>=0 && i<m_diml && j>=0 && j<m_dimc && m_matrice[i][j].getDiscovred()==false)
    {
        m_matrice[i][j].setDiscovred(true);
        if(m_matrice[i][j].getValue()==9 && m_matrice[i][j].getDiscovred()==true)
        {
            m_matriceCachee[i][j]='B';
            return 1;
        }
        else if(m_matrice[i][j].getValue()!=9 && m_matrice[i][j].getValue()!=0)
            {
                nb_couts++;
                m_matriceCachee[i][j]='0'+m_matrice[i][j].getValue();
                return 2;
            }
        if(m_matrice[i][j].getValue()==0)
        {
            nb_couts+=5;
            m_matriceCachee[i][j]='X';
            decouvrirCase(i-1,j-1);
            decouvrirCase(i-1,j);
            decouvrirCase(i-1,j+1);
            decouvrirCase(i,j-1);
            decouvrirCase(i,j+1);
            decouvrirCase(i+1,j-1);
            decouvrirCase(i+1,j);
            decouvrirCase(i+1,j+1);
            return 0;
        }
    }/*else if(m_matrice[i][j].getDiscovred()==false)
    {
        //cout<<"entrer des coordonnée valide"<<endl;
        return 3;
    }*/
    else return -1 ;
}

void Plateau::perdu()
{
    cout<<"___|";
    for(int i=0;i<m_diml;i++)
    {
        if(i+1<10)
            cout<<"0"<<i+1<<" ";
        else
            cout<<i+1<<" ";
    }
    cout<<endl;
    cout<<"___|";
    for(int i=0;i<m_diml;i++)
        cout<<"___";
    cout<<endl;
    for(int i=0;i<m_diml;i++)
    {
        if(i+1<10)
                cout<<"0"<<i+1<<" |";
            else
                cout<<i+1<<" |";
        for(int j=0;j<m_dimc;j++)
        {
            if(m_matrice[i][j].getValue()==0)
                cout<<" X ";
            else if(m_matrice[i][j].getValue()==9)
                cout<<" B ";
            else
                cout<<" "<<m_matrice[i][j].getValue()<<" ";
        }
        cout<<endl;
    }
}

void Plateau::poserDrapeau(int i,int j)
{
    /*si la case est déjà une flag rendre la case a nouveau non découvertes
    substutié 1 be nombre de drapeau
    sinon poser un drapeau sur cette case
    et ajout 1 nb_de drapeau poser*/
    if(m_matriceCachee[i][j]=='#'){
            m_matrice[i][j].setFlag(true);
            cout<<"la case n"<<i<<" "<<j<<"a un drapeau?:"<<m_matrice[i][j].getFlag()<<endl;
            m_matriceCachee[i][j]='D';
            nb_drapeau++;
        }
        else if(m_matriceCachee[i][j]=='D')
        {
            m_matrice[i][j].setFlag(false);
            m_matriceCachee[i][j]='#';
            nb_drapeau--;
        }
    //}
    else
        cout<<"s'il vouz plaît entrer les coordonnées d'une case qui n'est pas decouverte"<<endl;
}

    //retourne le nombre de drapeau poser
    int Plateau::getNbDrapeau()
    {
        return nb_drapeau;
    }
    //retourne le nombre de mine dans le jeu
    int Plateau::getNbMine()
    {
        return nb_mine;
    }

    bool Plateau::testerSiGagne()
    {
    int x=0;
    for(int i=0;i<m_diml;i++)
    {

        for(int j=0;j<m_dimc;j++)
            {
                if((m_matrice[i][j].getFlag()) && (m_matrice[i][j].getValue()==9))
                    x++;
            }
            cout<<endl;
    }
    if(nb_drapeau==x)
        return true;
    else return false;
    }




void Plateau::affiche()
{
    for(int i=0;i<m_diml;i++)
    {
        for(int j=0;j<m_dimc;j++)
        {
            int n=m_matrice[i][j].getValue();
            cout<<n;
        }
        cout<<endl;
    }
}

// afichage de la matrice cachée
void Plateau::afficheMatriceCachee()
{
    cout<<"___|";
    for(int i=0;i<m_diml;i++)
    {
        if(i+1<10)
            cout<<"0"<<i+1<<" ";
        else
            cout<<i+1<<" ";
    }
    cout<<endl;
    cout<<"___|";
    for(int i=0;i<m_diml;i++)
        cout<<"___";
        cout<<endl;
        for(int i=0;i<m_diml;i++)
        {
            if(i+1<10)
                cout<<"0"<<i+1<<" |";
            else
                cout<<i+1<<" |";
            for(int j=0;j<m_dimc;j++)
                cout<<" "<<m_matriceCachee[i][j]<<" ";
            cout<<endl;
        }
}



bool verifRand(vector<pair<int,int> >v,int a,int b){
    //vérifier si l'entier génerer par le compilateur aléatoirement a été deja génerer ou pas
    //un simple verif sur les pairs déja generer
    pair<int,int> p;
    bool test=false;
    p=make_pair(a,b);
    if (find(v.begin(),v.end(),p)!=v.end())
        test=true;
    return test;

}

