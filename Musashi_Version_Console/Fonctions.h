#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

typedef struct
{
    char table[7][5]; //Position des différents pions à un certain instant
    int l, c; //Position du musashi
    //int p; //Nbr actuel des policiers
}etat;

void affiche(char *textBox);
void afficher(char table[7][5]);
int deplacement_possible(char Table[7][5], int l2, int c2, int l1, int c1);
void capture(char table[7][5], int l, int c, int *pc);
void transferer(etat *p_etat1, etat etat2);
int fct_heuristique(int table[7][5], int l1, int c1);
int est_SolutionP(int table[7][5], int l1, int c1);
int est_SolutionM(int cMusashi, int l1, int c1);

#endif // FONCTIONS_H_INCLUDED
