#ifndef _VAZIO_
#define _VAZIO_

#include "jogador.h"

/**
 * @brief Executa a ação VAZIA: nada acontece e o jogador não é alterado.
 * @param dados Não utilizado (a ação VAZIA não possui dados)
 * @param j Não utilizado
 * @return 0 (a ação não gera deslocamento)
 */
int executaVazio(void* dados, Jogador* j);

/**
 * @brief Imprime, sem quebra de linha, "VAZIA"
 * @param dados Não utilizado (a ação VAZIA não possui dados)
 */
void imprimeVazio(void* dados);

/**
 * @brief Não faz nada: a ação VAZIA não possui dados alocados (o ponteiro da ação é NULL)
 * @param dados Não utilizado
 */
void desalocaVazio(void* dados);

#endif // _VAZIO_
