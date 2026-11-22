#ifndef _ITEM_
#define _ITEM_

#include "jogador.h"

typedef struct item tItem;


/**
 * @brief Converte o dado genérico para item e tenta comprá-lo: se o ouro do jogador for maior ou igual
 * ao preço, desconta o preço do ouro e soma o bônus à força. Caso contrário, não altera o jogador.
 * A compra é automática (não há opção de recusar) e o item nunca é removido da célula.
 * @param dados Ponteiro genérico para o item
 * @param j Jogador que parou na célula
 * @return 0 (a ação não gera deslocamento)
 */
int executaItem(void* dados, Jogador* j);


/**
 * @brief Converte o dado genérico para item e imprime, sem quebra de linha:
 * "ITEM <nome> (P:<preco> F:+<bonus>)". Ex: "ITEM ESPADA (P:10 F:+2)"
 * @param dados Ponteiro genérico para o item
 */
void imprimeItem(void* dados);


/**
 * @brief Converte o dado genérico para item e libera a memória alocada para ele
 * @param dados Ponteiro genérico para o item
 */
void desalocaItem(void* dados);

/**
 * @brief Lê da entrada padrão, na mesma linha, o nome, o preço e o bônus do item (a palavra ITEM
 * já deve ter sido lida) e cria o item com criaDadosItem.
 * @return Ponteiro para o item criado
 */
tItem *leItem();


#endif // _ITEM_
