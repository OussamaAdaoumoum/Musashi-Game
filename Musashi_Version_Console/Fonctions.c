#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "AI.h"
#include "Fonctions.h"


void affiche(char *textBox){
    char c;
    FILE *f=NULL;
   f=fopen(textBox,"r");
   if(f!=NULL)
   {
       do
       {
           c=fgetc(f);
           printf("%c",c);
       }while(c!=EOF);
   }
   fclose(f);
}



//Fonction pour afficher la table de jeu
void afficher(char table[7][5])
{
    //%c%c%c%c%c%c%c%c%c%c
  //  printf("\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    printf("\n\n\n\n\n\n\n");
    printf("\n\t\t\t\t\t\t\t                     0     1     2     3     4\n");
    printf("\n\t \t\t\t\t\t\t\t     0>      %c-----%c-----%c-----%c-----%c",table[0][0],table[0][1],table[0][2],table[0][3],table[0][4]);
    printf("\n\t\t\t\t\t\t\t\t\t     | \\   |   / | \\   |   / |");
    printf("\n\t\t\t\t\t\t\t\t\t     |  \\  |  /  |  \\  |  /  |");
    printf("\n\t\t\t\t\t\t\t\t\t     |   \\ | /   |   \\ | /   |");
    printf("\n\t \t\t\t\t\t\t\t     1>      %c-----%c-----%c-----%c-----%c",table[1][0],table[1][1],table[1][2],table[1][3],table[1][4]);

    printf("\n\t\t\t\t\t\t\t\t\t     |   / | \\   |   / | \\   |");
    printf("\n\t\t\t\t\t\t\t\t\t     |  /  |  \\  |  /  |  \\  |");
    printf("\n\t\t\t\t\t\t\t\t\t     | /   |   \\ | /   |   \\ |");

    printf("\n\t \t\t\t\t\t\t\t     2>      %c-----%c-----%c-----%c-----%c",table[2][0],table[2][1],table[2][2],table[2][3],table[2][4]);
    printf("\n\t\t\t\t\t\t\t\t\t     | \\   |   / | \\   |   / |");
    printf("\n\t\t\t\t\t\t\t\t\t     |  \\  |  /  |  \\  |  /  |");
    printf("\n\t\t\t\t\t\t\t\t\t     |   \\ | /   |   \\ | /   |");
    printf("\n\t \t\t\t\t\t\t\t     3>      %c-----%c-----%c-----%c-----%c",table[3][0],table[3][1],table[3][2],table[3][3],table[3][4]);

    printf("\n\t\t\t\t\t\t\t\t\t     |   / | \\   |   / | \\   |");
    printf("\n\t\t\t\t\t\t\t\t\t     |  /  |  \\  |  /  |  \\  |");
    printf("\n\t\t\t\t\t\t\t\t\t     | /   |   \\ | /   |   \\ |");

    printf("\n\t \t\t\t\t\t\t\t     4>      %c-----%c-----%c-----%c-----%c",table[4][0],table[4][1],table[4][2],table[4][3],table[4][4]);
    printf("\n\t\t\t\t\t\t\t\t\t              /  |  \\        ");
    printf("\n\t\t\t\t\t\t\t\t\t             /   |   \\");
    printf("\n\t\t\t\t\t\t\t\t\t            /    |    \\");
    printf("\n\t \t\t\t\t\t\t\t     5>            / %c---%c---%c \\",table[5][1],table[5][2],table[5][3]);
    printf("\n\t\t\t\t\t\t\t\t\t          /  |\\  |  /|  \\");
    printf("\n\t\t\t\t\t\t\t\t\t         /   | \\ | / |   \\");
    printf("\n\t\t\t\t\t\t\t\t\t        /    |  \\|/  |    \\");
    printf("\n\t \t\t\t\t\t\t\t     6>        %c-----%c---%c---%c-----%c ",table[6][0],table[6][1],table[6][2],table[6][3],table[6][4]);

}


//Fonction pour verifier si un deplacement d'une position a une autre bien precise est possible ou pas
int deplacement_possible(char table[7][5], int l2, int c2, int l1, int c1)
{
    if(table[l1][c1] == 'M' && l2<7 && c2<5 && table[l2][c2]==' ')
    {
        if(abs(l2-l1)<=1 && abs(c2-c1)<=1)
        {
            if(l1%2==c1%2) return 1;//Meme parit� c�d le pion est au centre de la croie (Tous les sens sont possible pr le mvt)
            else
            {
                if(abs(l2-l1)==1 && abs(c2-c1)==1) return 0;
                else return 1;
            }
        }
        else return 0;
    }
    else return 0;
}


//Fonction pour capturer les policiers
void capture(char table[7][5], int l, int c, int *pc)
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


//Compteur ordinateur
void compte(char table[7][5], int *cOrdinateur){
    int i=0, j=0;
    for(i=0; i<7; i++)
    {
        for(j=0; j<5; j++)
        {
            if(table[i][j]=='M')
            {
                if((i+j)%2==0)
                {
                    if(table[i-1][j-1]=='P' && i-1>=0 && i-1<7 && j-1>=0 && j-1<5){*cOrdinateur+=2;}

                    if(table[i-1][j]=='P' && i-1>=0 && i-1<7 && j>=0 && j<5){*cOrdinateur+=2;}

                    if(table[i-1][j+1]=='P' && i-1>=0 && i-1<7 && j+1>=0 && j+1<5){*cOrdinateur+=2;}

                    if(table[i][j+1]=='P' && i>=0 && i<7 && j+1>=0 && j+1<5){*cOrdinateur+=2;}

                    if(table[i+1][j+1]=='P' && i+1>=0 && i+1<7 && j+1>=0 && j+1<5){*cOrdinateur+=2;}

                    if(table[i+1][j]=='P' && i+1>=0 && i+1<7 && j>=0 && j<5){*cOrdinateur+=2;}

                    if(table[i+1][j-1]=='P' && i+1>=0 && i+1<7 && j-1>=0 && j-1<5){*cOrdinateur+=2;}

                    if(table[i][j-1]=='P' && i>=0 && i<7 && j-1>=0 && j-1<5){*cOrdinateur+=2;}
                }
                else
                {
                    if(table[i-1][j]=='P' && i-1>=0 && i-1<7 && j>=0 && j<5){*cOrdinateur+=4;}

                    if(table[i][j+1]=='P' && i>=0 && i<7 && j+1>=0 && j+1<5){*cOrdinateur+=4;}

                    if(table[i][j-1]=='P' && i>=0 && i<7 && j-1>=0 && j-1<5){*cOrdinateur+=4;}

                    if(table[i+1][j]=='P' && i+1>=0 && i+1<7 && j>=0 && j<5){*cOrdinateur+=4;}
                }
            }
        }
    }
}


//Fonction qui transfere toutes les informations de l'etat etat2 a l'etat etat1 a travers son pointeur
void transferer(etat *p_etat1, etat etat2)
{
    memcpy((*p_etat1).table, etat2.table, 7*5*sizeof(char));
    (*p_etat1).l = etat2.l;
    (*p_etat1).c = etat2.c;
}


//Pour definir l'etat final

//Fonction qui calcule combien de policiers entourent le musashi
int fct_heuristique(int table[7][5], int l1, int c1)
{
    int pentoure = 0, i = 0;
    char c;
    int tab[16] = {l1-1, c1-1, l1-1, c1, l1-1, c1+1, l1, c1-1, l1, c1+1, l1+1, c1-1, l1+1, c1, l1+1, c1+1};
    for(i = 0; i < 16; i+=2)
    {
        c = table[tab[i]][tab[i+1]];
        if(tab[i]>=0 && tab[i]<7 && tab[i+1]>=0 && tab[i+1]<5 && c == 'P')
        {
            pentoure++;
        }
    }
    return pentoure;
}


//Fonction qui verifie si on est a l'etat final ou pas (cas P gagne)
int est_SolutionP(int table[7][5], int l1, int c1)
{
    if(l1 == 0 || l1 == 4)
    {
        if(c1 == 2)
        {
            if(fct_heuristique(table, l1, c1) == 5) return 1;
            else return 0;
        }
        else
        {
            if(fct_heuristique(table, l1, c1) == 3) return 1;
            else return 0;
        }
    }
    else if(l1 == 5)
    {
        if(c1 == 1 || c1 == 3)
        {
            if(fct_heuristique(table, l1, c1) == 5) return 1;
            else return 0;
        }
        if(c1 == 2)
        {
            if(fct_heuristique(table, l1, c1) == 4) return 1;
            else return 0;
        }
    }
    else if(l1 == 6)
    {
        if(c1 == 0 || c1 == 4)
        {
            if(fct_heuristique(table, l1, c1) == 2) return 1;
            else return 0;
        }
        else if(c1 == 2)
        {
            if(fct_heuristique(table, l1, c1) == 5) return 1;
            else return 0;
        }
        else
        {
            if(fct_heuristique(table, l1, c1) == 3) return 1;
            else return 0;
        }
    }
    else
    {
        if(c1 == 0 || c1 == 4)
        {
            if(fct_heuristique(table, l1, c1) == 5) return 1;
            else return 0;
        }
        else
        {
            if(fct_heuristique(table, l1, c1) == 8) return 1;
            else return 0;
        }
    }
    return 0;
}


//Fonction qui verifie si on est a l'etat final ou pas (cas M gagne)
int est_SolutionM(int cMusashi, int l1, int c1)
{
    int cPolicier = 16 - cMusashi;

    if(l1 == 0 || l1 == 4)
    {
        if(c1 == 2)
        {
            if(cPolicier < 5) return 1;
            else return 0;
        }
        else
        {
            if(cPolicier < 3) return 1;
            else return 0;
        }
    }
    else if(l1 == 5)
    {
        if(c1 == 1 || c1 == 3)
        {
            if(cPolicier < 5) return 1;
            else return 0;
        }
        if(c1 == 2)
        {
            if(cPolicier < 4) return 1;
            else return 0;
        }
    }
    else if(l1 == 6)
    {
        if(c1 == 0 || c1 == 4)
        {
            if(cPolicier < 2) return 1;
            else return 0;
        }
        else if(c1 == 2)
        {
            if(cPolicier < 5) return 1;
            else return 0;
        }
        else
        {
            if(cPolicier < 3) return 1;
            else return 0;
        }
    }
    else
    {
        if(c1 == 0 || c1 == 4)
        {
            if(cPolicier < 5) return 1;
            else return 0;
        }
        else
        {
            if(cPolicier < 8) return 1;
            else return 0;
        }
    }
    return 0;
}
