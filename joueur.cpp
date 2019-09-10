#include "plateau.h"
#include<bits/stdc++.h>
#include <cstdlib>
#include<time.h>
#include "plateau.h"
#include <cstdlib>
#include<time.h>
#include"case.h"
#include "joueur.h"
#include<stdlib.h>

using namespace std;



Jouer::Jouer(){
    partieEnCours=true;
    //this->debut();
}

void Jouer::debut()
{
    int nbl,nbc,nbm; //donner le nombre de ligne par l'utulisateur
    cout<<"              ________________________________\n";
    cout<<"             |                                |\n";
    cout<<"             |        Jeu du demineur         |\n";
    cout<<"             |________________________________|\n\n";
    cout<<"     debut d'une nouvelle parite"<<endl;
    cout<<"     pour commencer donnez les dimentions de la grille, ansi le nombre de mines souhaiter\n";
    cout<<"Nombre Ligne:";
    cin>>nbl;
    cout<<endl;
    cout<<"Nombre Colonne:";
    cin>>nbc;
    cout<<endl;
    cout<<"Nombre MineS:";
    cin>>nbm;
    cout<<endl;
    cout<<"Ok c bon! Le jeu commance"<<endl;
    Plateau pl(nbl,nbc,nbm);
    m_plateau=pl;

}

void Jouer::menu()
{
    cout<<"         1.Nouvelle partie\n";
    cout<<"         2.meilleur score\n";
    cout<<"         3.Quiter\n";
    int don;
    //cin>>don;
    while(cin>>don){
        if(don==1)
        {
            this->debut();
            this->joueur();
            cout<<"         1.Nouvelle partie\n";
            cout<<"         2.meilleur score\n";
            cout<<"         3.Quiter\n";
        }
        else if(don==3) exit(1);
    }

}

void Jouer::joueur()
{
    m_plateau.creerMatrice();
    m_plateau.placerBombe();
    m_plateau.chiffrerMatrices();
    m_plateau.cacheMatrice();
    //m_plateau.affiche();
    system("cls");
    this->scoreActuelle();
    m_plateau.afficheMatriceCachee();
    this->action();

}

void Jouer::action()
{
    /*permer de choisir entre decouvrir ou poser Drapeau
    aprés avoir choisir la case pour l'une des deux méthodes*/
    /* entrer les cordonner de la case puis demander au utilisateur de choisir entre
    D decouvrir case et P pour poser Drapeau*/
    while(partieEnCours==true)
    {
        int ligne,colonne,a;
        char choix;
        cout<<"entre la ligne [espace] colonne\n";
        cin>>ligne>>colonne;
        cout<<"Voulez vous poser un drapeau ? si oui ecrit D sinon ecrit C pour decouvrir une case"<<endl;
        cin>>choix;
        if(toupper(choix) =='C')
            {
                a=m_plateau.decouvrirCase(ligne-1,colonne-1);
                if(a==1)
                    {
                        partieEnCours=false;
                        system("cls");
                        cout<<"B  O  O  M!"<<endl;
                        cout<<"vous avez perdu"<<endl;
                        m_plateau.perdu();
                    }
                    else
                        {
                            system("cls");
                            this->scoreActuelle();
                            m_plateau.afficheMatriceCachee();
                        }
            }
            else if(toupper(choix)=='D')
            {
                m_plateau.poserDrapeau(ligne-1,colonne-1);
                system("cls");
                this->scoreActuelle();
                m_plateau.afficheMatriceCachee();
                if(m_plateau.getNbDrapeau()==m_plateau.getNbMine())
                    {
                        if(m_plateau.testerSiGagne())
                            {
                                system("cls");
                                this->scoreActuelle();
                                m_plateau.afficheMatriceCachee();
                                cout<<"Bravo tu as decouvert toute les bomb :D donner votre nom et prenom pour sauvgarder votre score"<<endl;
                                cout<<"entrer votre nom et prenom"<<endl;
                                char nom[256];
                                char prenom[256];
                                cout<<"Donner votre nom et prenom"<<endl;
                                cin>>nom>>prenom;
                                this->meilleurScore(nom,prenom,m_plateau.getNbCouts());
                                break;

                            }
                        else
                            {
                                system("cls");
                                cout<<"B  O  O  M!"<<endl;
                                cout<<"vous avez perdu"<<endl;
                                m_plateau.perdu();
                                break;

                            }
                    }
            }
            else
                cout<<"s'il vouz plaît entrer C pour decouvrire ou bien D pour poser un drapeau"<<endl;

    }

}

void Jouer::scoreActuelle()
{
    cout<<"votre score:"<<m_plateau.getNbCouts()<<endl;
    cout<<"mine restant:"<<m_plateau.getNbMine()-m_plateau.getNbDrapeau()<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
}
/* sauvgarder le meilleur score dans un fichier score*/
void Jouer::meilleurScore(char* n,char* p,int s)
{
    FILE *fc= fopen("score.txt","r");

    signed char nom[256];
    signed char prenom[256];
    int score;
    if(fc== NULL)
        exit(1);

    fscanf(fc,"%s %s %d",nom,prenom,&score);
    fclose(fc);

    if(s<score)
    {
        cout<<"le meilleur score appartient a"<<nom<<"  "<<prenom<<":"<<score<<endl;
    }
    else
    {
        FILE *fc= fopen("score.txt","w");
        if(fc== NULL)
        exit(1);
        fprintf(fc,"%s %s %d",n,s);
        cout<<"tu as actuellement la meilleur score avec"<<s<<endl;
        fclose(fc);

    }

}
