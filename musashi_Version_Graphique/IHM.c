#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "AI.h"
#include "Fonctions.h"
#include "IHM.h"



// Fonction dediee au tour du joueur humain

void joueur_humain( SDL_Surface* image, SDL_Window *window, SDL_Surface* screen, char pBN,int* pc,char table[7][5], int *l1, int *c1, pion tableau[7][5], int *xMus_Suivant, int *yMus_Suivant)
{
    int l2, c2;
    int x2,y2;
    SDL_Rect dstrect;
    int mouse_Click = 1;
//Cc:
    SDL_Event event2;

    while(mouse_Click)
    {
        SDL_PollEvent(&event2);
        if(event2.type == SDL_QUIT)
        {
            //	gameIsRunning2 = 0;
        }



        if(event2.type == SDL_MOUSEBUTTONDOWN)
        {


            *xMus_Suivant=-1;
            *yMus_Suivant=-1;



            for(int i=0; i<7; i++)
            {
                for(int j=0; j<5; j++)
                {
                    int x =395 + j*65 +23;
                    int y = 122 + i*65 +23;


                    if( (event2.button.x<= x+20 && event2.button.x>= x-20) && (event2.button.y<= y+20 && event2.button.y>= y-20) )
                    {
                        *xMus_Suivant= x-23 ;
                        *yMus_Suivant= y-23;

                        l2= i;
                        c2= j;
                        mouse_Click = 0;
                        break;
                    }
                }
            }

            if( *xMus_Suivant!=-1 && *yMus_Suivant!=-1)
            {


                if(deplacement_possible(table, l2, c2, *l1, *c1))
                {

                    table[l2][c2] = table[*l1][*c1];
                    table[*l1][*c1] = ' ';

                    tableau[l2][c2].pionX = *xMus_Suivant;
                    tableau[l2][c2].pionY = *yMus_Suivant;
                    tableau[l2][c2].existe = 1;
                    tableau[*l1][*c1].pionX = 0;
                    tableau[*l1][*c1].pionY = 0;
                    tableau[*l1][*c1].existe = 0;



                    capture(table, l2, c2, pc, tableau);
                    *l1=l2;
                    *c1=c2;

                    drawtable(image, window, screen,tableau, *xMus_Suivant, *yMus_Suivant, 11110, 11110, 11110, 11110);
                    SDL_UpdateWindowSurface(window);

                    //     sleep(3000);




                }

                else
                {
                    printf("\nVeuillez changer votre destination:");
                    //      goto Cc;
                }
            }

        }
    }
}













// Fonction dediee a l'ordinateur avec intelligence evoluee
void Joueur_ordinateur( SDL_Surface* image, SDL_Window *window, SDL_Surface* screen,char table[7][5], int *pc, int *cOrdinateur,int cJoueur,  pion tableau[7][5], int xMos, int yMos)
{
    Pion pionsPossibles[20]= {0};
    Pion meilleurPion= {-1,-1};
    Pion meilleurEmp= {-1,-1};
    int L=0;

    // G�n�ration des successeurs (trouver les pions possibles) : etats fils
    pionsFils(table,'P',pionsPossibles, &L);

    // Trouver le meilleur pion : meilleur etat parmi les etats fils
    pionChoisi(table,pionsPossibles,&cOrdinateur,cJoueur,L,&meilleurPion, &meilleurEmp);

    // Jouer le mouvement
    table[meilleurPion.X][meilleurPion.Y]=' ';
    table[meilleurEmp.X][meilleurEmp.Y]='P';
    int x_pion;
    int y_pion;
    int x_pionSuivant;
    int y_pionSuivant;




    tableau[meilleurPion.X][meilleurPion.Y].pionX=0;
    tableau[meilleurPion.X][meilleurPion.Y].pionY=0;
    tableau[meilleurPion.X][meilleurPion.Y].existe=0;
    sleep(1);
    tableau[meilleurEmp.X][meilleurEmp.Y].pionX= 395 + meilleurEmp.Y*65;
    tableau[meilleurEmp.X][meilleurEmp.Y].pionY= 122 + meilleurEmp.X*65;
    tableau[meilleurEmp.X][meilleurEmp.Y].existe= 1;


//drawtable(image, window, screen,tableau, *xMus_Suivant, *yMus_Suivant, 11110, 11110, 11110, 11110);

    drawtable(image, window, screen, tableau, xMos,yMos, x_pion, y_pion, x_pionSuivant, y_pionSuivant);
    SDL_UpdateWindowSurface(window);

    compte(table, pc);
    //capture(table, meilleurEmp.X+1, meilleurEmp.Y+1, pc);
//    afficher(table);
}
