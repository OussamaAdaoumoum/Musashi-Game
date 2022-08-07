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



// des variables global
pion tableau[7][5];

void SDL_ExitWithError();

char table[7][5]= {{'P','P','P','P','P'},
    {'P',' ',' ',' ','P'},
    {'P',' ','M',' ','P'},
    {'P',' ',' ',' ','P'},
    {'P','P','P','P','P'},
    {'N',' ',' ',' ','N'},
    {' ',' ',' ',' ',' '}
};




SDL_Surface* image;
SDL_Window* window;
SDL_Surface* screen;

int main(int argc, char *argv[])
{

    //lancement SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        printf("SDL non initialisé");
        SDL_ExitWithError();
    }
    else
    {
        printf("SDL window is ready to go\n");
    }

    /****************************************** Music ********************************************************/
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 22050)!=0)
        SDL_ExitWithError();

    Mix_Chunk *effect1 = NULL;
    Mix_Chunk *effect2 = NULL;
    //effect1 = Mix_LoadWAV("you_win.wav");
    //effect2 = Mix_LoadWAV("you_lose.wav");    // red lbal lchemain
    Mix_Music *music = NULL;
    music = Mix_LoadMUS("src/mosika.mp3");

    SDL_Event event6;

    /**************************************************** images ******************************************************/

    /* ---------------------------------------------------------------------------- */

    window = SDL_CreateWindow("images-types", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 600, SDL_WINDOW_RESIZABLE);  //RESIZABLE

    screen = SDL_GetWindowSurface(window);

    SDL_Surface* image;
    image = IMG_Load("src/musashi1.jpg");

    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;

    SDL_BlitSurface(image,NULL,screen,&dstrect);
    SDL_FreeSurface(image);
    SDL_UpdateWindowSurface(window);



    /*************************************************** first page **********************************************************/
    int gameIsRunning0 = 1;
    int gameIsRunning1 = 1;
    int gameIsRunning2 = 1;

    while(gameIsRunning0)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameIsRunning0 = 0;
            }


            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if((event.button.x>=100 &&event.button.x<=380 && event.button.y>=470 && event.button.y<=535) || (event.button.x>=725 &&event.button.x<=972 && event.button.y>=470 && event.button.y<=535) )
                {
                    image = IMG_Load("src/menu.jpg");
                    SDL_BlitSurface(image,NULL,screen,&dstrect);
                    SDL_FreeSurface(image);
                    SDL_UpdateWindowSurface(window);
                      Mix_PlayMusic(music, 3);
                    goto accueil;    // you can replace it with break
                }
            }


        }
    }
    /****************************************** teeest *******************************************************************/


accueil:

    while(gameIsRunning1)
    {
            SDL_Event event1;




        // start our event loop
        while(SDL_PollEvent(&event1))
        {
                    Accueill:
            switch(event1.type)
            {
            case SDL_QUIT:
                gameIsRunning1 = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                // Play
                if(event1.button.x>=425 &&event1.button.x<=620 && event1.button.y>=185 &&event1.button.y<=260)
                {



                    image = IMG_Load("src/tableau.jpeg");
                    SDL_BlitSurface(image,NULL,screen,&dstrect);
                    SDL_FreeSurface(image);
                    SDL_UpdateWindowSurface(window);

                    tableau[7][5];

firstdraw(image, window, screen,tableau);

                    goto table;
                }

                // regles
                if(event1.button.x>=425 &&event1.button.x<=620 && event1.button.y>=305 &&event1.button.y<=380)
                {
                    image = IMG_Load("src/regles.jpg");
                    SDL_BlitSurface(image,NULL,screen,&dstrect);
                    SDL_FreeSurface(image);
                    SDL_UpdateWindowSurface(window);


                }

                // Quit
                if(event1.button.x>=425 &&event1.button.x<=620 && event1.button.y>=425 &&event1.button.y<=498)
                {
                    SDL_DestroyWindow(window);
                    //our program
                    SDL_Quit();
                }
            }
            break;
            }
        }
    }






    /****************************************** Table *******************************************************************/
table:
    while(gameIsRunning2)
    {
        SDL_Event event2;
        while(SDL_PollEvent(&event2))
        {
            if(event2.type == SDL_QUIT)
            {
                gameIsRunning2 = 0;
            }
            dstrect.x = 525;
            dstrect.y = 252;


            int x1 = 525, y1 = 252;
            int l1 = 2, c1 = 2;
            int cjoueur = 0, cOrdinateur = 0;
            int c=0; // compteur


            //  afficher(table);
            int ordi_humain=0;
            do
            {
                if(ordi_humain == 0)
                {
                    cOrdinateur = 0;
                    joueur_humain(image, window, screen, 'M',&c,table,&l1,&c1,tableau,&x1,&y1);//fonction d�di�e au joueur

                    cjoueur=cjoueur+c;
                    c=0;
                    ordi_humain=1;
                }
                else
                {

                    Joueur_ordinateur(image, window, screen,table, &c, cOrdinateur, cjoueur, tableau,x1,y1);
                    cOrdinateur=cOrdinateur+c;
                    c=0;
                    ordi_humain=0;
                }
            }
            while(!est_SolutionM(cjoueur, l1, c1) && !est_SolutionP(table, l1, c1) );

        }
    }


    SDL_DestroyWindow(window);
    //our program
    SDL_Quit();
    return 0;
}




void SDL_ExitWithError()
{
    printf("%s", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


