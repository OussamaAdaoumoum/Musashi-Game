#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

typedef struct pion{
int pionX;
int pionY;
int existe;
}pion;

void capture(char table[7][5], int l, int c, int *pc, pion tableau[7][5]);
int deplacement_possible(char table[7][5], int l2, int c2, int l1, int c1);
void drawtable(SDL_Surface* image, SDL_Window *window, SDL_Surface* screen, pion tableau[7][5], int xMus_Suivant, int yMus_Suivant, int xPol, int yPol, int xPol_Suivant, int yPol_Suivant);

void firstdraw(SDL_Surface* image, SDL_Window *window, SDL_Surface *screen,pion tableau[7][5]);
void captur_element(char table[7][5], int l, int c, int *pc, pion tableau[7][5]);

void compte(char table[7][5], int *cOrdinateur);
int fct_heuristique(int table[7][5], int l1, int c1);
int est_SolutionP(int table[7][5], int l1, int c1);
int est_SolutionM(int cMusashi, int l1, int c1);
void capture_console(char table[7][5], int l, int c, int *pc);



#endif // FONCTIONS_H_INCLUDED
