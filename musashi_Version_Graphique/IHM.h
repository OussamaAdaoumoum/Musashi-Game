#ifndef IHM_H_INCLUDED
#define IHM_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
void joueur_humain( SDL_Surface* image, SDL_Window *window, SDL_Surface* screen, char pBN,int* pc,char table[7][5], int *l1, int *c1, pion tableau[7][5], int *xMus_Suivant, int *yMus_Suivant);
void Joueur_ordinateur( SDL_Surface* image, SDL_Window *window, SDL_Surface* screen,char table[7][5], int *pc , int *cOrdinateur,int cJoueur,  pion tableau[7][5], int xMos, int yMos);


#endif // IHM_H_INCLUDED
