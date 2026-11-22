#ifndef _AVANCAR_VOLTAR_
#define _AVANCAR_VOLTAR_

#include "jogador.h"


typedef struct movimentar tVaiVolta;


/**
 * @brief Converte o dado genérico para AVANCA/VOLTA e informa o deslocamento da ação. A função não altera
 * o jogador nem o mapa: quem move o jogador é o módulo que conduz a partida.
 * @param dados Ponteiro genérico para a ação AVANCA/VOLTA (tVaiVolta)
 * @param j Jogador que parou na célula (não utilizado)
 * @return Deslocamento em casas (positivo para AVANCA, negativo para VOLTA)
 */
int executaVaiVolta(void* dados, Jogador* j);


/**
 * @brief Converte o dado genérico para AVANCA/VOLTA e imprime, sem quebra de linha, "AVANCA <n>" se n for
 * positivo ou "VOLTA <n>" (com o valor absoluto de n) caso contrário. Ex: "AVANCA 2", "VOLTA 3"
 * @param dados Ponteiro genérico para a ação AVANCA/VOLTA (tVaiVolta)
 */
void imprimeVaiVolta(void* dados);


/**
 * @brief Converte o dado genérico para AVANCA/VOLTA e libera a memória alocada para ele
 * @param dados Ponteiro genérico para a ação AVANCA/VOLTA (tVaiVolta)
 */
void desalocaVaiVolta(void* dados);

/**
 * @brief Lê da entrada padrão a quantidade de casas (a palavra AVANCA ou VOLTA já deve ter sido lida),
 * multiplica pelo sinal informado e cria a ação com criaVaiVolta.
 * @param vaiOuVolta Sinal do deslocamento: 1 para AVANCA e -1 para VOLTA
 * @return Ponteiro para a ação criada
 */
tVaiVolta *leVaiVolta(int vaiOuVolta);

#endif // _AVANCAR_VOLTAR_
