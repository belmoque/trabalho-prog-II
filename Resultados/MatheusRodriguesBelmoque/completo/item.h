#ifndef _ITEM_
#define _ITEM_

#include "mapa.h"
#include "celula.h"
#include "jogador.h"
#include <stdio.h>

typedef struct item tItem;


int executaItem(void* dados, Jogador* j);


void imprimeItem(void* dados);


void desalocaItem(void* dados);

tItem *leItem();


#endif // _ITEM_
