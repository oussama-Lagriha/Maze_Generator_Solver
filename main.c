//=====================================================================
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "head.h"

//----LES CONSTANTES-------------------------------------------------------
#define GRILLE_LARGEUR 29
#define GRILLE_LONGUEUR 30
#define HAUT 0
#define DROITE 1
#define BAS 2
#define GAUCHE 3
//----LES VARIABLES GLOBALES------------------------------------------------
int grille[GRILLE_LARGEUR][GRILLE_LONGUEUR];
int solution[GRILLE_LARGEUR][GRILLE_LONGUEUR];
Stack Colonne, Ligne;

//----FONCTIONS PROTOTYPES---------------------------------------------

void INIT_Grille(int grille[GRILLE_LARGEUR][GRILLE_LONGUEUR]);
int Test_Bornes( int x, int y );
void Visiter( int x, int y );
void faire_un_pas(int k);
void solveur(int x, int y);
void Dessiner_Solution(SDL_Renderer *renderer);
void Dessiner_Labyrinthe(SDL_Renderer *renderer);
void print_labyrinthe(int sol[GRILLE_LARGEUR][GRILLE_LONGUEUR]);

//----FONCTION main---------------------------------------------------

int main(int argc, char * argv[]){
    srand(time(0));
    INIT_Grille(grille);        // initialisation du Grille avec des 0
    INIT_Grille(solution);      // initialisation du Grille avec des 0
    Visiter(1, 1);
    grille[1][1] = 3;            // l'entréé
    grille[27][1] = 2;           // sortie 1
    grille[1][29] = 2;           // sortie 2
    solution[1][1] = 1;
  //  print_labyrinthe(grille);     // Afficher la matrice grille qui est la base du labyrinthe
    solveur(27, 1);              // trouver la sortie 1
    solveur(1, 29);              // trouver la sortie 1
    Colonne = nouveau_pile();
    Ligne = nouveau_pile();
    plus_court_chemin(27, 1);    // trouver le plus court chemin à la sortie 1
    plus_court_chemin(1, 29);    // trouver le plus court chemin à la sortie 2

    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(630, 660, 0, &window, &renderer) == 0)
            {
                SDL_SetWindowTitle(window, "LABYRINTHE :: OTHMANE-D");
                SDL_bool done = SDL_FALSE;
                while (!done)
                {
                    SDL_Event event;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    Dessiner_Labyrinthe(renderer);
                    Dessiner_Solution(renderer);
                    SDL_RenderPresent(renderer);
                    while (SDL_PollEvent(&event))
                    {
                        if (event.type == SDL_QUIT)
                        {
                            done = SDL_TRUE;
                        }
                    }
                }
            }
            if (renderer)
                {
                    SDL_DestroyRenderer(renderer);
                }
                if (window)
                    {
                        SDL_DestroyWindow(window);
                    }
    }
    SDL_Quit();
    Vider_Pile(Colonne);
    Vider_Pile(Ligne);

    return 0;

}
