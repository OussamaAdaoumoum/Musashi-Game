#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <windows.h>
#include "AI.h"
#include "Fonctions.h"
#include "IHM.h"

char table[7][5]= {{'P','P','P','P','P'},
    {'P',' ',' ',' ','P'},
    {'P',' ','M',' ','P'},
    {'P',' ',' ',' ','P'},
    {'P','P','P','P','P'},
    {'N',' ',' ',' ','N'},
    {' ',' ',' ',' ',' '}
};


int main()
{
    system("color 0b");                            // changer la couleur du console

    char choix ;
    int reponse;
    char r;


    do
    {
acceuil :
        system("cls");
        affiche("text/accueil.txt");
        scanf("%s",&choix);
        switch(choix)
        {

        case '1':
        {
            // option de jouer
            do
            {
rejouer:
                system("cls");
                affiche("text/jouerFonction.txt");
                scanf("%d",&reponse);

                if(reponse == 3)
                {
                    goto acceuil;
                }
                else
                {
                    system("cls");
                    int l1, c1; //etat initial(position de M)
                    int cjoueur = 0, cOrdinateur = 0;
                    int c=0; // compteur intermediaire

                    etat etat_Initial, etat_Courant;

                    //Definition de l'etat initial
                    memcpy(etat_Initial.table, table, 7*5*sizeof(char));
                    etat_Initial.l = 2;
                    etat_Initial.c = 2;

                    transferer(&etat_Courant, etat_Initial);
                    l1 = etat_Courant.l;
                    c1 = etat_Courant.c;
                    memcpy(table, etat_Courant.table, 7*5*sizeof(char));


                    afficher(table);
                    do
                    {
                        joueur_humain('M',&c,table,&l1,&c1);
                        cjoueur=cjoueur+c;
                        c=0;
                        printf("\n\n\t\tSCORE : %d",cjoueur);

                        printf("\n\n\t  Cliquez sur entrer... ");
                        getch();
                        system("cls");

                        Joueur_ordinateur(table, &c, cOrdinateur, cjoueur, reponse);
                        cOrdinateur=cOrdinateur+c;
                        c=0;
                    }
                    while(!est_SolutionM(cjoueur, l1, c1) && !est_SolutionP(table, l1, c1) );

                    system("cls");
                    printf("\n\n");
                    affiche("text/congratulation.txt");
                    if(est_SolutionM(cjoueur, l1, c1))
                    {
                        printf("\n joueur , you won !");
                    }
                    else if(est_SolutionP(table, l1, c1))
                    {
                        printf("\n Computer, you won !");
                    }

                    printf("\n\n\t\t\t\t\t\t\t\t  voulez-vous rejouer? ");
                    char re = 'oui';
                    scanf("%s",&re);
                    if(re=='o' || re=='oui' || re=='Oui')
                    {
                        goto rejouer;
                    }
                    else
                    {
                        exit(EXIT_SUCCESS);
                    }
                }

            }
            while(reponse!=1 && reponse!=2 && reponse!=3 );
            printf("\n\n\n\n\n\n\n\n");
        }
        break;

        case '2':
        {
            system("cls");
            affiche("text/regles.txt");
regle:
            scanf("%s",&r);
            if(r=='o' || r=='oui' || r =='Oui' )
            {
                goto acceuil;
            }
            else if(r=='n' || r=='non' || r =='Non' )
            {
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("\t\t\t\t\t\t\t\t\t\t  Erreur!");
                goto regle;
            }
        }
        break;

        case '3':
            system("cls");
            break;
        }
    }
    while(choix!='1' && choix!='2' && choix!='3' );
    return 0;
}
