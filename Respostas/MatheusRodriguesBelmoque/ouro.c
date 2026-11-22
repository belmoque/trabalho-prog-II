#include "ouro.h"
#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>


struct ouro
{
    int qtd;
};

/**
 * @brief Converte o dado genérico para ouro e soma a quantidade de ouro da célula ao ouro do jogador.
 * A célula é permanente: o ouro pode ser coletado várias vezes.
 * @param dados Ponteiro genérico para a ação OURO
 * @param j Jogador que parou na célula
 * @return Quantidade de ouro da célula
 */
int executaOuro(void *dados, Jogador *j)
{
    tOuro *ouroCast = (tOuro*)dados;

    adicionaOuroJogador(j,ouroCast->qtd);

    return ouroCast->qtd;
}

/**
 * @brief Converte o dado genérico para ouro e imprime, sem quebra de linha: "OURO <qtd>". Ex: "OURO 10"
 * @param dados Ponteiro genérico para a ação OURO
 */
void imprimeOuro(void *dados)
{
    tOuro *ouroCast = (tOuro*)dados;

    printf("OURO %d",ouroCast->qtd);
}

/**
 * @brief Converte o dado genérico para ouro e libera a memória alocada para ele
 * @param dados Ponteiro genérico para a ação OURO
 */
void desalocaOuro(void *dados)
{
    tOuro *ouroCast = (tOuro*)dados;

    free(ouroCast);
}

/**
 * @brief Aloca dinamicamente uma ação do tipo OURO e guarda nela a quantidade de ouro
 * @param qtd Quantidade de ouro coletada por quem parar na célula
 * @return Ponteiro para a ação criada
 */
tOuro *criaDadosOuro(int qtd)
{
    tOuro *ouroCriado = (tOuro*)malloc(sizeof(tOuro));

    ouroCriado->qtd = qtd;

    return ouroCriado;
}

/**
 * @brief Lê da entrada padrão a quantidade de ouro (a palavra OURO já deve ter sido lida)
 * e cria a ação com criaDadosOuro.
 * @return Ponteiro para a ação criada
 */
tOuro *leOuro()
{
    int qtd;

    scanf(" %d\n",&qtd);

    tOuro *ouroCriado = criaDadosOuro(qtd);

    return ouroCriado;
}

