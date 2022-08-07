#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "AI.h"
#include "Fonctions.h"

void firstdraw(SDL_Surface* image, SDL_Window *window, SDL_Surface *screen,pion tableau[7][5]){
    SDL_Rect dstrect;



                        image = IMG_Load("src/black pion (1).png");

                    for(int i=0;i<7;i++){
                            for(int j=0;j<5;j++){
                                if((i==0 || i==4 || j==0 || j==4) && i<=4){
                                dstrect.x = 395+j * 65;
                                dstrect.y = 122+i *65;
                                        tableau[i][j].pionX = dstrect.x;
                                        tableau[i][j].pionY = dstrect.y;
                                        tableau[i][j].existe = 1;


                                        SDL_BlitSurface(image,NULL,screen,&dstrect);

                                        SDL_UpdateWindowSurface(window);
                                }
                                else{
                                        tableau[i][j].pionX = 0;
                                        tableau[i][j].pionY = 0;
                                        tableau[i][j].existe = 0;
                                }
                            }

                    	}



                        SDL_FreeSurface(image);

                        image = IMG_Load("src/blancpion (2).png");

                    dstrect.x = 525;
                    dstrect.y = 252;
                            tableau[2][2].pionX = dstrect.x;
                            tableau[2][2].pionY = dstrect.y;
                            tableau[2][2].existe = 1;

                    	SDL_BlitSurface(image,NULL,screen,&dstrect);
                        SDL_FreeSurface(image);
                        SDL_UpdateWindowSurface(window);

}


void captur_element(char table[7][5], int l, int c, int *pc, pion tableau[7][5])
{
    table[l][c] = ' ';
    tableau[l][c].pionX = 0;
    tableau[l][c].pionY = 0;
    tableau[l][c].existe = 0;
    *pc=*pc+1;
}

void capture(char table[7][5], int l, int c, int *pc, pion tableau[7][5])
{


    if( (l==0 || l == 4 || l ==6) && ( c!=0 && c!=4) )
    {
        if(table[l][c-1] =='P' && table[l][c+1] == 'P')
        {
            captur_element(table, l, c-1, pc, tableau);
            captur_element(table, l, c+1, pc, tableau);
        }
        else if(l==4 && c==2)
        {
            if( table[l-1][c+1] =='P' && table[l+1][c-1] == 'P')
            {
                captur_element(table, l+1, c-1, pc, tableau);
                captur_element(table, l-1, c+1, pc, tableau);
            }
            else if(table[l-1][c-1] =='P' &&  table[l+1][c+1] == 'P')
            {
                captur_element(table, l-1, c-1, pc, tableau);
                captur_element(table, l+1, c+1, pc, tableau);
            }
            else if(table[l-1][c] =='P' && table[l+1][c] == 'P')
            {
                captur_element(table, l-1, c, pc, tableau);
                captur_element(table, l+1, c, pc, tableau);
            }
        }
    }
    else if ( (c==0 || c==4) && (l!=0 && l!=4) )
    {
        if( table[l-1][c] =='P' && table[l+1][c] == 'P')
        {
            captur_element(table, l+1, c, pc, tableau);
            captur_element(table, l-1, c, pc, tableau);
        }

    }
    else if( ( l>0 && c>0) && (l<4 && c<4) )
    {
        if( table[l-1][c] =='P' && table[l+1][c] == 'P')
        {
            captur_element(table, l+1, c, pc, tableau);
            captur_element(table, l-1, c, pc, tableau);
        }
        else if(table[l][c-1] =='P' && table[l][c+1] == 'P')
        {
            captur_element(table, l, c-1, pc, tableau);
            captur_element(table, l, c+1, pc, tableau);
        }
        else if((c+l)%2 == 0 )
        {
            if( table[l-1][c+1]=='P' && table[l+1][c-1] == 'P')
            {
                captur_element(table, l+1, c-1, pc, tableau);
                captur_element(table, l-1, c+1, pc, tableau);
            }
            else if(table[l-1][c-1]=='P' && table[l+1][c+1] == 'P')
            {
                captur_element(table, l-1, c-1, pc, tableau);
                captur_element(table, l+1, c+1, pc, tableau);
            }
        }
    }
    else if(l==5)
    {
        if(c==2)
        {
            if(table[l][c-1] =='P' && table[l][c+1] == 'P')
            {
                captur_element(table, l, c-1, pc, tableau);
                captur_element(table, l, c+1, pc, tableau);
            }
            else if( table[l-1][c] =='P' && table[l+1][c] == 'P')
            {
                captur_element(table, l+1, c, pc, tableau);
                captur_element(table, l-1, c, pc, tableau);
            }

        }
        else if(c==1)
        {
            if( table[l-1][c+1] =='P' && table[l+1][c-1] == 'P')
            {
                captur_element(table, l+1, c-1, pc, tableau);
                captur_element(table, l-1, c+1, pc, tableau);
            }
        }
        else if(c==3)
        {
            if(table[l-1][c-1] =='P' && table[l+1][c+1] == 'P')
            {
                captur_element(table, l-1, c-1, pc, tableau);
                captur_element(table, l+1, c+1, pc, tableau);
            }
        }
    }
}



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


void drawtable(SDL_Surface* image, SDL_Window *window, SDL_Surface* screen, pion tableau[7][5], int xMus_Suivant, int yMus_Suivant, int xPol, int yPol, int xPol_Suivant, int yPol_Suivant)
{
    int i=0, j=0;
    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;

    // affichage du Tableau
    image = IMG_Load("src/tableau.jpeg");
    SDL_BlitSurface(image,NULL,screen,&dstrect);

    // affichage du musashi
    image = IMG_Load("src/blancpion (2).png");
    dstrect.x = xMus_Suivant;
    dstrect.y = yMus_Suivant;
    SDL_BlitSurface(image,NULL,screen,&dstrect);

    // affichage de police
    image = IMG_Load("src/black pion (1).png");
    int mi,mj;

    for(i=0; i<7; i++)
    {
        for(j=0; j<5; j++)
        {

            if(tableau[i][j].existe==1)
            {
                image = IMG_Load("src/black pion (1).png");
                dstrect.x = tableau[i][j].pionX;
                dstrect.y = tableau[i][j].pionY;
                SDL_BlitSurface(image,NULL,screen,&dstrect);

                if(tableau[i][j].pionX == xMus_Suivant && tableau[i][j].pionY == yMus_Suivant )
                {

                    image = IMG_Load("src/blancpion (2).png");
                    dstrect.x = xMus_Suivant;
                    dstrect.y = yMus_Suivant;
                    SDL_BlitSurface(image,NULL,screen,&dstrect);
                    SDL_UpdateWindowSurface(window);
                    //   continue;

                }

                else if(tableau[i][j].pionX==xPol && tableau[i][j].pionY==yPol)
                {
                    tableau[i][j].pionX=xPol_Suivant;
                    tableau[i][j].pionY=yPol_Suivant;

                }

            }
        }
    }


}











/*****************************************************************************************************************************/



//Compteur ordinateur
void compte(char table[7][5], int *cOrdinateur)
{
    int i=0, j=0;
    for(i=0; i<7; i++)
    {
        for(j=0; j<5; j++)
        {
            if(table[i][j]=='M')
            {
                if((i+j)%2==0)
                {
                    if(table[i-1][j-1]=='P' && i-1>=0 && i-1<7 && j-1>=0 && j-1<5)
                    {
                        *cOrdinateur+=2;
                    }

                    if(table[i-1][j]=='P' && i-1>=0 && i-1<7 && j>=0 && j<5)
                    {
                        *cOrdinateur+=2;
                    }

                    if(table[i-1][j+1]=='P' && i-1>=0 && i-1<7 && j+1>=0 && j+1<5)
                    {
                        *cOrdinateur+=2;
                    }

                    if(table[i][j+1]=='P' && i>=0 && i<7 && j+1>=0 && j+1<5)
                    {
                        *cOrdinateur+=2;
                    }

                    if(table[i+1][j+1]=='P' && i+1>=0 && i+1<7 && j+1>=0 && j+1<5)
                    {
                        *cOrdinateur+=2;
                    }

                    if(table[i+1][j]=='P' && i+1>=0 && i+1<7 && j>=0 && j<5)
                    {
                        *cOrdinateur+=2;
                    }

                    if(table[i+1][j-1]=='P' && i+1>=0 && i+1<7 && j-1>=0 && j-1<5)
                    {
                        *cOrdinateur+=2;
                    }

                    if(table[i][j-1]=='P' && i>=0 && i<7 && j-1>=0 && j-1<5)
                    {
                        *cOrdinateur+=2;
                    }
                }
                else
                {
                    if(table[i-1][j]=='P' && i-1>=0 && i-1<7 && j>=0 && j<5)
                    {
                        *cOrdinateur+=4;
                    }

                    if(table[i][j+1]=='P' && i>=0 && i<7 && j+1>=0 && j+1<5)
                    {
                        *cOrdinateur+=4;
                    }

                    if(table[i][j-1]=='P' && i>=0 && i<7 && j-1>=0 && j-1<5)
                    {
                        *cOrdinateur+=4;
                    }

                    if(table[i+1][j]=='P' && i+1>=0 && i+1<7 && j>=0 && j<5)
                    {
                        *cOrdinateur+=4;
                    }
                }
            }
        }
    }
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
