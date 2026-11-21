#include "mapa.h"
#include "celula.h"
#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int qtd;
}tOuro;

int executaOuro(void *dados, Jogador *j)
{
    tOuro *ouroCast = (tOuro*)dados;

    adicionaOuroJogador(j,ouroCast->qtd);

    return ouroCast->qtd;
}

void imprimeOuro(void *dados)
{
    tOuro *ouroCast = (tOuro*)dados;

    printf("OURO %d",ouroCast->qtd);
}

void desalocaOuro(void *dados)
{
    tOuro *ouroCast = (tOuro*)dados;

    free(ouroCast);
}

tOuro *criaDadosOuro(int qtd)
{
    tOuro *ouroCriado = (tOuro*)malloc(sizeof(tOuro));

    ouroCriado->qtd = qtd;

    return ouroCriado;
}

tOuro *leOuro()
{
    int qtd;

    scanf(" %d\n",&qtd);

    tOuro *ouroCriado = criaDadosOuro(qtd);

    return ouroCriado;
}

