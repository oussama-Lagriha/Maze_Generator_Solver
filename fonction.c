#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "head.h"
#include <SDL2/SDL.h>
//-----------------------------------------------------------
#define GRILLE_LARGEUR 29
#define GRILLE_LONGUEUR 30
#define HAUT 0
#define DROITE 1
#define BAS 2
#define GAUCHE 3

//***************

int grille[GRILLE_LARGEUR][GRILLE_LONGUEUR];
int solution[GRILLE_LARGEUR][GRILLE_LONGUEUR];
Stack Colonne, Ligne;
int c;

//FONCTION-----------------------------------------------------------

void INIT_Grille(int grille[GRILLE_LARGEUR][GRILLE_LONGUEUR])
{
    for(int y = 0; y < GRILLE_LONGUEUR; y++)
    {
        for(int x = 0; x < GRILLE_LARGEUR; x++)
        {
            grille[x][y] = 0;                   // initialiser la matrice grille avec des 0
        }
    }
}


//FONCTION-----------------------------------------------------------
int Test_Bornes( int x, int y )
{
    if(x < 0 || x >= GRILLE_LARGEUR)
        return false;
    if(y < 0 || y > GRILLE_LONGUEUR)
        return false;
    return true;                         // la position ([x],[y]) appartient à la matrice
}

//FONCTION-----------------------------------------------------------

void Visiter( int x, int y )
{
    grille[x][y] = 1;

    int dirs[4];
    dirs[0] = HAUT;

    dirs[1] = DROITE;
    dirs[2] = BAS;
    dirs[3] = GAUCHE;
    for(int i = 0; i < 4; i++)
    {
        int r = rand() % 4;
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }
    for(int i = 0; i < 4; i++)
    {
        int dx = 0;
        int dy = 0;
        switch(dirs[i])
        {
            case HAUT : dy = -1; break;
            case BAS : dy = 1; break;
            case DROITE : dx = 1; break;
            case GAUCHE : dx = -1; break;
        }

        int x2 = x + (dx * 2);
        int y2 = y + (dy * 2);

        if(Test_Bornes(x2, y2))
        {
            if(grille[x2][y2] == 0)          // la position x2,y2 n'est pas encore visitée
            {
                grille[x2 - dx][y2 - dy] = 1;
                Visiter(x2, y2);
            }
        }
    }
}
//FONCTION-----------------------------------------------------------

void faire_un_pas(int k)
{
    for(int y = 0; y < GRILLE_LONGUEUR; y++)
    {
        for(int x = 0; x < GRILLE_LARGEUR; x++)
        {
            if(k == solution[x][y])
            {
                if(x > 0 && grille[x-1][y] != 0 && solution[x-1][y] == 0)
                {
                    solution[x-1][y] = k+1;
                }
                if(y > 0 && grille[x][y-1] != 0 && solution[x][y-1] == 0)
                {
                    solution[x][y-1] = k+1;
                }
                if(y < (GRILLE_LONGUEUR-1) && grille[x][y+1] != 0 && solution[x][y+1] == 0)
                {
                    solution[x][y+1] = k+1;
                }
                if(x < (GRILLE_LARGEUR-1) && grille[x+1][y] != 0 && solution[x+1][y] == 0)
                {
                    solution[x+1][y] = k+1;
                }
            }
        }
    }
}

//FONCTION-----------------------------------------------------------

void solveur(int x, int y)
{
    int k = 0;
    while(solution[x][y] == 0)
    {
        k += 1;              // on incrémente k pour pouvoir parcourir notre labyrinthe et trouver la sortie
        faire_un_pas(k);        // avancer vers la position suivante
    }
}
//FONCTION-----------------------------------------------------------

void plus_court_chemin(int i, int j)
{
    int k = solution[i][j];
    while(k > 1)
    {
        Colonne = Empiler(Colonne, i);
        Ligne = Empiler(Ligne, j);
        if(i > 0 && solution[i-1][j] == k-1)
        {
            i -= 1;
            Colonne = Empiler(Colonne, i);
            Ligne = Empiler(Ligne, j);
            k -= 1;
        }else if(j > 0 && solution[i][j-1] == k-1)
        {
            j -= 1;
            Colonne = Empiler(Colonne, i);
            Ligne = Empiler(Ligne, j);
            k -= 1;
        }else if(i <(GRILLE_LARGEUR-1) && solution[i+1][j] == k-1)
        {
            i += 1;
            Colonne = Empiler(Colonne, i);
            Ligne = Empiler(Ligne, j);
            k -= 1;
        }else if(j <(GRILLE_LONGUEUR-1) && solution[i][j+1] == k-1)
        {
            j += 1;
            Colonne = Empiler(Colonne, i);
            Ligne = Empiler(Ligne, j);
            k -= 1;
        }
    }
}

//FONCTION-----------------------------------------------------------

void Dessiner_Solution(SDL_Renderer *renderer)
{
    SDL_Rect rect1;
    rect1.h = 8;
    rect1.w = 8;
    rect1.x = 26;
    rect1.y = 26;

    for(int y = 0; y < GRILLE_LONGUEUR; y++)
    {
        for(int x = 0; x < GRILLE_LARGEUR; x++)
        {

            if(x == Colonne->value && y == Ligne->value)  // on change la condition par 'solution[x][y]!=0' pour voir la recherche de la sortie
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &rect1);
                    SDL_RenderFillRect(renderer, &rect1);
                    Colonne = Depiler(Colonne);
                    Ligne = Depiler(Ligne);
                    SDL_Delay(30);
                    }
            rect1.x += 20;
        }
        rect1.x = 26;
        rect1.y += 20;
    }
}

//FONCTION-----------------------------------------------------------

void Dessiner_Labyrinthe(SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.h = 20;
    rect.w = 20;
    rect.x = 20;
    rect.y = 20;

    for(int y = 0; y < GRILLE_LONGUEUR; y++)
        {
            for(int x = 0; x < GRILLE_LARGEUR; x++)
            {
                    if(grille[x][y] == 0)
                    {
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                    }else if(grille[x][y] == 2)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                    }else if(grille[x][y] == 3)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    }
                    SDL_RenderDrawRect(renderer, &rect);
                    SDL_RenderFillRect(renderer, &rect);
                    rect.x += 20;
            }
            rect.x = 20;
            rect.y += 20;
        }
        for(int i = 0; i < GRILLE_LARGEUR; i++)
        {
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &rect);
            rect.x += 20;
        }
}

//FONCTION-----------------------------------------------------------

void print_labyrinthe(int sol[GRILLE_LARGEUR][GRILLE_LONGUEUR])
{
    for (int y=0;y < GRILLE_LONGUEUR ; y++)
    {
        for (int x=0; x < GRILLE_LARGEUR; x++)
        {
            printf(" %d ", grille[x][y]);
        }
    printf("\n");
    }
}

