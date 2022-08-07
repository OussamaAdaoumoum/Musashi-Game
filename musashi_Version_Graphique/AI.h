#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED




typedef enum Bool
{
    false,
    true
}Bool ;

typedef struct Pion
    {
        int X;
        int Y;
    }Pion;

int calcul_poids (int cOrdinateur, int cJoueur);
int pionPossible(char table[7][5], int i, int j, int* Ligne2 , int* Colonne2 , char pBN);
void pionsFils(char table[7][5], char pBN , Pion tab_fils[] ,int *L);
//int minimax (char table[7][5],int prof_arbre, Bool max_Joueur,int compteurOr, int compteurJ );
int alpha_beta (char table[7][5],int prof_arbre, Bool max_Joueur,int compteurOr, int compteurJ, int alpha, int beta );
void pionChoisi(char table[7][5] , Pion tab_fils[], int cOrdinateur, int cJoueur,int L, Pion *meilleurPion, Pion *meilleurEmp);





#endif // AI_H_INCLUDED
