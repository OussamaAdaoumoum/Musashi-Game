#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "AI.h"
#include "Fonctions.h"
#include "IHM.h"

// Fonction dediee au tour du joueur humain
void joueur_humain(char pBN,int* pc,char table[7][5], int *l1, int *c1)
{
    int l2, c2;
    printf("\nVeuillez entrer votre destination:");
        Cc:
        printf("\nLigne: ");
        scanf("%d",&l2);
        printf("Colonne: ");
        scanf("%d",&c2);

        if(deplacement_possible(table, l2, c2, *l1, *c1))
        {
            table[l2][c2] = table[*l1][*c1];
            table[*l1][*c1] = ' ';
            capture(table, l2, c2, pc);
            *l1=l2;
            *c1=c2;
            afficher(table);
        }
        else
        {
            printf("\nVeuillez changer votre destination:");
            goto Cc;
        }
}


// Fonction dediee a l'ordinateur avec intelligence evoluee
void Joueur_ordinateur(char table[7][5], int *pc , int *cOrdinateur,int cJoueur, int reponse)
{
    pion pionsPossibles[20]={0};
    pion meilleurPion={-1,-1};
    pion meilleurEmp={-1,-1};
    int L=0;

    // Génération des successeurs (trouver les pions possibles) : etats fils
    pionsFils(table,'P',pionsPossibles, &L);

    // Trouver le meilleur pion : meilleur etat parmi les etats fils
    pionChoisi(table,pionsPossibles,&cOrdinateur,cJoueur,L,&meilleurPion, &meilleurEmp, reponse);

    // Jouer le mouvement
    table[meilleurPion.X][meilleurPion.Y]=' ';
    table[meilleurEmp.X][meilleurEmp.Y]='P';


    compte(table, pc);
    //capture(table, meilleurEmp.X+1, meilleurEmp.Y+1, pc);
    afficher(table);
}
