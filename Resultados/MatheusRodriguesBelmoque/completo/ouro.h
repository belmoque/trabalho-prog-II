#ifndef _OURO_
#define _OURO_

#include "mapa.h"
#include "celula.h"
#include "jogador.h"
#include <stdio.h>

typedef struct ouro tOuro;

int executaOuro(void *dados, Jogador *j);


void imprimeOuro(void *dados);


void desalocaOuro(void *dados);


tOuro *leOuro();



#endif // _OURO_
