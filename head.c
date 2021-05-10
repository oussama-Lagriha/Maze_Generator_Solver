
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

/**
* Retourne une Pile vide
*/

Stack nouveau_pile(void)
{
	return NULL;
}

/*-----------------------------------------------------------------*/

/**
* Vérifie si une Pile est vide
*/

bool pile_vide(Stack st)
{
	if(st == NULL)
		return true;

	return false;
}

/*-----------------------------------------------------------------*/

/**
* Empiler un entier dans la Pile
*/
Stack Empiler(Stack st, int x)
{
	StackElement *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->value = x;
	element->next = st;

	return element;
}

/*-----------------------------------------------------------------*/

/**
* Dépile un entier de la Pile
*/
Stack Depiler(Stack st)
{
	StackElement *element;

	if(pile_vide(st))
		return nouveau_pile();

	element = st->next;
	free(st);

	return element;
}



/*-----------------------------------------------------------------*/

/**
* Vide la Pile de ses éléments
*/

Stack Vider_Pile(Stack st)
{
	while(!pile_vide(st))
		st = Depiler(st);

	return nouveau_pile();
}
