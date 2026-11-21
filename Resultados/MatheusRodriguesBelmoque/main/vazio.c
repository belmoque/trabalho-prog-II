#ifndef _VAZIO_
#define _VAZIO_

#include "mapa.h"
#include "celula.h"
#include "jogador.h"
#include <stdio.h>

int executaVazio(void* dados,Jogador *j)
{
    return 0;
}

void imprimeVazio(void* dados)
{
    printf("VAZIA");
}

void desalocaVazio(void* dados)
{
    //nada a ser feito
}

Celula *criaCelulaVazia(Celula *c)
{
    return criaCelula(NULL,executaVazio,imprimeVazio,desalocaVazio);
}


#endif // _VAZIO_
