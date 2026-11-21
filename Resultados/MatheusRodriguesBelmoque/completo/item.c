#include "mapa.h"
#include "celula.h"
#include "jogador.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_TAM_NOME_ITEM 15

typedef struct 
{
    char nome[MAX_TAM_NOME_ITEM];
    int preco;
    int bonus;

}tItem;


int executaItem(void* dados, Jogador* j)
{
    tItem *itemCast = (tItem*)dados;
    if(obtemOuroJogador(j)>=itemCast->preco)
    {
        adicionaOuroJogador(j,-1*itemCast->preco);
        adicionaForcaJogador(j,itemCast->bonus);
    }

    return 0;
}

void imprimeItem(void* dados)
{
    tItem *itemCast = (tItem*)dados;
    printf("ITEM %s (P:%d F:+%d)",itemCast->nome,itemCast->preco,itemCast->bonus);
}

void desalocaItem(void* dados)
{
    tItem *itemCast = (tItem*)dados;
    free(itemCast);
}

tItem *criaDadosItem(char* nome, int preco, int bonus)
{
    tItem *itemCriado = (tItem*)malloc(sizeof(tItem));

    strcpy(itemCriado->nome,nome);
    itemCriado->preco = preco;
    itemCriado->bonus = bonus;

    return itemCriado;
}

tItem *leItem()
{
    char nome[MAX_TAM_NOME_ITEM] = {0};
    int preco, bonus;
    scanf("%s %d %d",nome,&preco,&bonus);

    return criaDadosItem(nome,preco,bonus);
}
