#include "item.h"
#include "jogador.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_TAM_NOME_ITEM 15

struct item
{
    char nome[MAX_TAM_NOME_ITEM];
    int preco;
    int bonus;

};


/**
 * @brief Converte o dado genérico para item e tenta comprá-lo: se o ouro do jogador for maior ou igual
 * ao preço, desconta o preço do ouro e soma o bônus à força. Caso contrário, não altera o jogador.
 * A compra é automática (não há opção de recusar) e o item nunca é removido da célula.
 * @param dados Ponteiro genérico para o item
 * @param j Jogador que parou na célula
 * @return 0 (a ação não gera deslocamento)
 */
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

/**
 * @brief Converte o dado genérico para item e imprime, sem quebra de linha:
 * "ITEM <nome> (P:<preco> F:+<bonus>)". Ex: "ITEM ESPADA (P:10 F:+2)"
 * @param dados Ponteiro genérico para o item
 */
void imprimeItem(void* dados)
{
    tItem *itemCast = (tItem*)dados;
    printf("ITEM %s (P:%d F:+%d)",itemCast->nome,itemCast->preco,itemCast->bonus);
}

/**
 * @brief Converte o dado genérico para item e libera a memória alocada para ele
 * @param dados Ponteiro genérico para o item
 */
void desalocaItem(void* dados)
{
    tItem *itemCast = (tItem*)dados;
    free(itemCast);
}

/**
 * @brief Aloca dinamicamente uma ação do tipo ITEM e guarda nela o nome (copiado), o preço e o bônus de força
 * @param nome Nome do item
 * @param preco Preço do item, em ouro
 * @param bonus Bônus somado à força do jogador que comprar o item
 * @return Ponteiro para o item criado
 */
tItem *criaDadosItem(char* nome, int preco, int bonus)
{
    tItem *itemCriado = (tItem*)malloc(sizeof(tItem));

    strcpy(itemCriado->nome,nome);
    itemCriado->preco = preco;
    itemCriado->bonus = bonus;

    return itemCriado;
}

/**
 * @brief Lê da entrada padrão, na mesma linha, o nome, o preço e o bônus do item (a palavra ITEM
 * já deve ter sido lida) e cria o item com criaDadosItem.
 * @return Ponteiro para o item criado
 */
tItem *leItem()
{
    char nome[MAX_TAM_NOME_ITEM] = {0};
    int preco, bonus;
    scanf("%s %d %d",nome,&preco,&bonus);

    return criaDadosItem(nome,preco,bonus);
}
