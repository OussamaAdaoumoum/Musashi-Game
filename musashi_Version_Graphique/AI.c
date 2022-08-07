#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "AI.h"
#include "Fonctions.h"


//Fonction qui remplie tab par toutes les positions qui entourent la position (k,l)
void parcourir(int tab[16], int k, int j)
{
    int tab1[16] = {k-1, j-1, k-1, j, k-1, j+1, k, j-1, k, j+1, k+1, j-1, k+1, j, k+1, j+1};

    for(int i=0; i<16; i++)
    {
        tab[i] = tab1[i];
    }
}


// Fonction calcule le poids d'un etat de jeu (fonction heuristique) en se basant sur les compteurs
int calcul_poids (int cOrdinateur, int cJoueur)
{
    if (cOrdinateur >= cJoueur){return 10;}
    else if (cOrdinateur <= cJoueur){return -10;}
    else {return 0;}

}


//Fonction qui verifie si un pion est possible d'etre joue ou pas
int pionPossible(char table[7][5], int i, int j, int* Ligne2 , int* Colonne2 , char pBN){
    int x=0;
    int ml = 0, mc = 0;
    int Mx=0, My = 0;
    int tab1[16] = {i-1, j-1, i-1, j, i-1, j+1, i, j-1, i, j+1, i+1, j-1, i+1, j, i+1, j+1};
    int tab2[16];
    int n, m;

    if(pBN == 'P')
    {
            //Recherche du pion 'M'
            for(ml=0; ml<7; ml++)
            {
                for(mc=0; mc<5; mc++)
                {
                    if(table[ml][mc] == 'M')
                    {
                        Mx = ml;
                        My = mc;
                    }
                }
            }

            if(i == Mx)
            {
                    if(j < My && j+1>=0 && j+1<5 && table[i][j+1] == ' ')
                    {
                        *Ligne2=i;
                        *Colonne2=j+1;
                         x=1;
                    }
                    else if(j > My && j-1>=0 && j-1<5 && table[i][j-1] == ' ')
                    {
                        *Ligne2=i;
                        *Colonne2=j-1;
                         x=1;
                    }

            }
            else if(j == My)
            {
                    if(i < Mx && i+1>=0 && i+1<7 && table[i+1][j] == ' ')
                    {
                        *Ligne2=i+1;
                        *Colonne2=j;
                         x=1;
                    }
                    else if(i > Mx && i-1>=0 && i-1<7 && table[i-1][j] == ' ')
                    {
                        *Ligne2=i-1;
                        *Colonne2=j;
                         x=1;
                    }
            }

            else if(((i-Mx>0 && j-My>0) || (i-Mx<0 && j-My<0)) && (i+j)%2 == 0)
            {
                    if(j < My && j+1>=0 && j+1<5 && i+1>=0 && i+1<7 && table[i+1][j+1] ==' ')
                    {
                        *Ligne2=i+1;
                        *Colonne2=j+1;
                         x=1;
                    }
                    else if(j > My && j-1>=0 && j-1<5 && i-1>=0 && i-1<7 && table[i-1][j-1] ==' ')
                    {
                        *Ligne2=i-1;
                        *Colonne2=j-1;
                         x=1;
                    }
            }
            else if( ((i-Mx<0 && j-My>0) || (i-Mx>0 && j-My<0)) && (i+j)%2 == 0 )
            {
                    if(j < My && j+1>=0 && j+1<5 && i-1>=0 && i-1<7 && table[i-1][j+1] ==' ')
                    {
                        *Ligne2=i-1;
                        *Colonne2=j+1;
                         x=1;
                    }
                    else if(j < My && j-1>=0 && j-1<5 && i+1>=0 && i+1<7 && table[i+1][j-1] ==' ')
                    {
                        *Ligne2=i+1;
                        *Colonne2=j-1;
                         x=1;
                    }
            }
    }
    else if(pBN == 'M'){
        for(int k=0; k<16; k+=2)
        {
            if(table[tab1[k]][tab1[k+1]] == ' ')
            {
                parcourir(tab2, k, k+1);
                for(int r=0; r<16; r+=2)
                {
                    if(tab2[r]>=0 && tab2[r]<7 && tab2[r+1]>=0 && tab2[r+1]<5 && table[tab2[r]][tab2[r+1]] == 'P')
                    {
                            n = tab2[r]-tab2[k];
                            m = tab2[r+1]-tab2[k+1];
                            if(tab2[k]-n>=0 && tab2[k]-n < 7 && tab2[k+1]-m >= 0 && tab2[k+1]-m<5 && deplacement_possible(table, tab2[r], tab2[r+1], tab2[k], tab2[k+1]) == 1 && table[tab2[k]-n][tab2[k+1]-m] == 'P')
                            {
                                    *Ligne2 = tab2[k];
                                    *Colonne2 = tab2[k+1];
                                    return 1;
                            }
                    }
                }
            }
        }
        return 0;


    }

return x;
}


// pionsFils : fonction cherche les pions possibles de jouer avec
void pionsFils(char table[7][5], char pBN , Pion tab_fils[] ,int *L)
{

    int i,j,n=0;
    int Ligne2=0, Colonne2=0;

    for(i=0;i<7;i++){
    for(j=0;j<5;j++){
    if (table[i][j]==pBN && pionPossible(table,i,j , &Ligne2, &Colonne2,pBN) == 1)
        {
            (tab_fils[n]).X=i;
            (tab_fils[n]).Y=j;
            (tab_fils[n+1]).X= Ligne2;
            (tab_fils[n+1]).Y= Colonne2;
            n=n+2;
        }
    }}

    *L=n;
}


// Fonction Alpha Beta
int alpha_beta (char table[7][5],int prof_arbre, Bool max_Joueur,int compteurOr, int compteurJ, int alpha, int beta )
{
    // variables de travail
    int C_Ordi=compteurOr, C_Joueur = compteurJ;
    int n;
    Pion tab_fils[20];
    int longueur=0;
    int Poids=0;

    char copieTableau[7][5];

    // condition d'arret
    if (prof_arbre == 0 || compteurOr==16 || compteurJ==16)
        {return calcul_poids(C_Ordi,C_Joueur);}


    if (max_Joueur == true)
    {
        int max_poids= -INT_MAX;
        longueur=0;
        Poids= 0;
        // trouver les etats fils
        pionsFils(table, 'P', tab_fils ,&longueur);

            for(n=0;n<longueur;n=n+2)
        {

            memcpy(copieTableau,table,7*5*sizeof(char));

            // jouer le mouvement

            copieTableau[(tab_fils[n]).X][(tab_fils[n]).Y]=' ';
            copieTableau[(tab_fils[n+1]).X][(tab_fils[n+1]).Y]='P';
         //   Capture_Pions((tab_fils[n]).Y+1,(tab_fils[n+1]).Y+1,(tab_fils[n]).X+1,(tab_fils[n+1]).X+1,&C_Ordi,copieTableau,'B');

            // evaluer l'etat
            Poids = alpha_beta(copieTableau,prof_arbre -1 ,false, C_Ordi, C_Joueur, alpha, beta);
            // annuler le mouvement
            memcpy(copieTableau,table,7*5*sizeof(char));
            C_Ordi=compteurOr;
            C_Joueur = compteurJ;
            if (Poids >= max_poids)
            {
                max_poids = Poids;
            }
            if (Poids >= alpha)
            {
                alpha=Poids;
            }
            if (beta <=alpha)
                break;
        }
        return max_poids;
    }
     else
     {
        Poids= 0;
        int min_poids= INT_MAX;
        longueur=0;
         pionsFils(table, 'M', tab_fils, &longueur);

         for(n=0 ; n<longueur ; n=n+2)
        {
             memcpy(copieTableau,table,7*5*sizeof(char));


            // jouer le mouvement

            copieTableau[(tab_fils[n]).X][(tab_fils[n]).Y]=' ';
            copieTableau[(tab_fils[n+1]).X][(tab_fils[n+1]).Y]='M';
            capture_console(copieTableau,(tab_fils[n+1]).X+1,(tab_fils[n+1]).Y+1,&C_Joueur);



            // evaluer l'etat
            Poids = alpha_beta(copieTableau,prof_arbre -1, true, C_Ordi,C_Joueur, alpha, beta);

            // annuler le mouvement
            memcpy(copieTableau,table,7*5*sizeof(char));
            C_Ordi=compteurOr;
            C_Joueur = compteurJ;

            if (Poids <= min_poids)
            {
                min_poids = Poids;
            }
            if (min_poids <= beta)
            {
                beta = min_poids;
            }
            if (beta <=alpha)
                break;
        }
    return min_poids;

}

}


// Trouver le meilleur pion parmi les pions de tab_fils
void pionChoisi(char table[7][5] , Pion tab_fils[], int cOrdinateur, int cJoueur,int L, Pion *meilleurPion, Pion *meilleurEmp)
{
    // variables de travail
    int n,poids=0;
    int compteurOr = cOrdinateur , compteurJ = cJoueur;
    char copieTableau[7][5];
    int meilleurPoids = -INT_MAX;


    for (n=0 ;n<L ; n=n+2) // pour chaque etat
    {

        memcpy(copieTableau,table,7*5*sizeof(char));

        // jouer le mouvement
        copieTableau[(tab_fils[n]).X][(tab_fils[n]).Y]=' ';
        copieTableau[(tab_fils[n+1]).X][(tab_fils[n+1]).Y]='P';
     //   Capture_Pions((tab_fils[n]).Y+1,(tab_fils[n+1]).Y+1,(tab_fils[n]).X+1,(tab_fils[n+1]).X+1,&compteurOr,copieTableau,'B');

        // evaluer le mouvement

            poids = alpha_beta(copieTableau,4,false,compteurOr,compteurJ, -INT_MAX, INT_MAX);

        // annuler le mouvement
        memcpy(copieTableau,table,7*5*sizeof(char));
        compteurJ=cJoueur;
        compteurOr=cOrdinateur;
        if (poids>=meilleurPoids)
        {
            meilleurPoids=poids;
            meilleurPion->X=tab_fils[n].X;
            meilleurPion->Y=tab_fils[n].Y;
            meilleurEmp->X=tab_fils[n+1].X;
            meilleurEmp->Y=tab_fils[n+1].Y;
        }

    }

}







void capture_console(char table[7][5], int l, int c, int *pc)
{
    if(l == 0 || (l == 4 && c != 2) || l == 6 || l == 5) //Les bords
    {
        if(l==5)
        {
            if(table[l+1][c-1] == table[l-1][c+1] && l-1>=0 && l-1<7 && c+1>=0 && c+1<5 && l+1>=0 && l+1<7 && c-1>=0 && c-1<5 && table[l+1][c-1] == 'P')
            {
                table[l+1][c-1] = ' ';
                table[l-1][c+1] = ' ';
                *pc=*pc+2;
            }
            if(table[l-1][c-1] == table[l+1][c+1] && l+1>=0 && l+1<7 && c+1>=0 && c+1<5 && l-1>=0 && l-1<7 && c-1>=0 && c-1<5 && table[l-1][c-1] == 'P')
            {
                table[l-1][c-1] = ' ';
                table[l+1][c+1] = ' ';
                *pc=*pc+2;
            }
        }
        if(c!=0 && c!=4 && table[l][c-1] == table[l][c+1] && c+1>=0 && c+1<5 && c-1>=0 && c-1<5 && table[l][c-1] == 'P')
        {
            table[l][c-1] = ' ';
            table[l][c+1] = ' ';
            *pc=*pc+2;
        }
    }
    else if(l%2 == c%2) //Milieu de la croie
    {
        if(table[l][c-1] == table[l][c+1] && c+1>=0 && c+1<5 && c-1>=0 && c-1<5 && table[l][c-1] == 'P')
        {
            table[l][c-1] = ' ';
            table[l][c+1] = ' ';
            *pc=*pc+2;
        }
        if(table[l-1][c] == table[l+1][c] && l-1>=0 && l-1<7 && l+1>=0 && l+1<7 && table[l+1][c] == 'P')
        {
            table[l-1][c] = ' ';
            table[l+1][c] = ' ';
            *pc=*pc+2;
        }
        if(table[l+1][c-1] == table[l-1][c+1] && l-1>=0 && l-1<7 && c+1>=0 && c+1<5 && l+1>=0 && l+1<7 && c-1>=0 && c-1<5 && table[l+1][c-1] == 'P')
        {
            table[l+1][c-1] = ' ';
            table[l-1][c+1] = ' ';
            *pc=*pc+2;
        }
        if(table[l-1][c-1] == table[l+1][c+1] && l-1>=0 && l-1<7 && c-1>=0 && c-1<5 && l+1>=0 && l+1<7 && c+1>=0 && c+1<5 && table[l+1][c+1] == 'P')
        {
            table[l-1][c-1] = ' ';
            table[l+1][c+1] = ' ';
            *pc=*pc+2;
        }
    }
    else //Milieu du losange
    {
        if(table[l][c-1] == table[l][c+1] && c+1>=0 && c+1<5 && c-1>=0 && c-1<5 && table[l][c-1] == 'P')
        {
            table[l][c-1] = ' ';
            table[l][c+1] = ' ';
            *pc=*pc+2;
        }
        if(table[l-1][c] == table[l+1][c] && l-1>=0 && l-1<7 && l+1>=0 && l+1<7 && table[l+1][c] == 'P')
        {
            table[l-1][c] = ' ';
            table[l+1][c] = ' ';
            *pc=*pc+2;
        }
    }
}

