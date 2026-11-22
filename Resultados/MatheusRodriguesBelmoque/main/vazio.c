#include "vazio.h"

#include "jogador.h"
#include <stdio.h>

/**
 * @brief Executa a ação VAZIA: nada acontece e o jogador não é alterado.
 * @param dados Não utilizado (a ação VAZIA não possui dados)
 * @param j Não utilizado
 * @return 0 (a ação não gera deslocamento)
 */
int executaVazio(void* dados,Jogador *j)
{
    return 0;
}

/**
 * @brief Imprime, sem quebra de linha, "VAZIA"
 * @param dados Não utilizado (a ação VAZIA não possui dados)
 */
void imprimeVazio(void* dados)
{
    printf("VAZIA");
}

/**
 * @brief Não faz nada: a ação VAZIA não possui dados alocados (o ponteiro da ação é NULL)
 * @param dados Não utilizado
 */
void desalocaVazio(void* dados)
{
    //nada a ser feito
}
