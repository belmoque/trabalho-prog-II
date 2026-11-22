#ifndef _OURO_
#define _OURO_

#include "jogador.h"

typedef struct ouro tOuro;

/**
 * @brief Converte o dado genérico para ouro e soma a quantidade de ouro da célula ao ouro do jogador.
 * A célula é permanente: o ouro pode ser coletado várias vezes.
 * @param dados Ponteiro genérico para a ação OURO
 * @param j Jogador que parou na célula
 * @return Quantidade de ouro da célula
 */
int executaOuro(void *dados, Jogador *j);


/**
 * @brief Converte o dado genérico para ouro e imprime, sem quebra de linha: "OURO <qtd>". Ex: "OURO 10"
 * @param dados Ponteiro genérico para a ação OURO
 */
void imprimeOuro(void *dados);


/**
 * @brief Converte o dado genérico para ouro e libera a memória alocada para ele
 * @param dados Ponteiro genérico para a ação OURO
 */
void desalocaOuro(void *dados);


/**
 * @brief Lê da entrada padrão a quantidade de ouro (a palavra OURO já deve ter sido lida)
 * e cria a ação com criaDadosOuro.
 * @return Ponteiro para a ação criada
 */
tOuro *leOuro();



#endif // _OURO_
