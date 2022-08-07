#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

typedef enum Bool
{
    false,
    true
}Bool ;

typedef struct pion
    {
        int X;
        int Y;
    }pion;

int calcul_poids (int cOrdinateur, int cJoueur);
int pionPossible(char table[7][5], int i, int j, int* Ligne2 , int* Colonne2 , char pBN);
void pionsFils(char table[7][5], char pBN , pion tab_fils[] ,int *L);
int minimax (char table[7][5],int prof_arbre, Bool max_Joueur,int compteurOr, int compteurJ );
int alpha_beta (char table[7][5],int prof_arbre, Bool max_Joueur,int compteurOr, int compteurJ, int alpha, int beta );
void pionChoisi(char table[7][5] , pion tab_fils[], int cOrdinateur, int cJoueur,int L, pion *meilleurPion, pion *meilleurEmp, int reponse);

#endif // AI_H_INCLUDED
