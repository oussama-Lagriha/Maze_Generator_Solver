#ifndef __STACK__H__
#define __STACK__H__
#include <stdbool.h>

	/*------------------------------------------*/

	/* Définition d'une Pile */
	typedef struct StackElement
	{
		int value;
		struct StackElement *next;
	}StackElement, *Stack;


	/*------------------------------------------*/

	/* Prototypes des fonctions */
	Stack nouveau_pile(void);
	bool pile_vide(Stack st);
	Stack Empiler(Stack st, int x);
	Stack Depiler(Stack st);
	Stack Vider_Pile(Stack st);

#endif
