#include "avancar_voltar.h"

#include "jogador.h"
#include <stdlib.h>
#include <stdio.h>

struct movimentar
{
    int n;
};

/**
 * @brief Converte o dado genérico para AVANCA/VOLTA e informa o deslocamento da ação. A função não altera
 * o jogador nem o mapa: quem move o jogador é o módulo que conduz a partida.
 * @param dados Ponteiro genérico para a ação AVANCA/VOLTA (tVaiVolta)
 * @param j Jogador que parou na célula (não utilizado)
 * @return Deslocamento em casas (positivo para AVANCA, negativo para VOLTA)
 */
int executaVaiVolta(void* dados, Jogador* j)
{
    tVaiVolta *movimentarCast = (tVaiVolta*)dados;

    (void)j;

    return movimentarCast->n;
}


/**
 * @brief Converte o dado genérico para AVANCA/VOLTA e imprime, sem quebra de linha, "AVANCA <n>" se n for
 * positivo ou "VOLTA <n>" (com o valor absoluto de n) caso contrário. Ex: "AVANCA 2", "VOLTA 3"
 * @param dados Ponteiro genérico para a ação AVANCA/VOLTA (tVaiVolta)
 */
void imprimeVaiVolta(void* dados)
{
    tVaiVolta *movimentarCast = (tVaiVolta*)dados;
    if(movimentarCast->n > 0)
    {
        printf("AVANCA %d",movimentarCast->n);
    }
    else
    {
        printf("VOLTA %d",abs(movimentarCast->n));
    }
}


/**
 * @brief Converte o dado genérico para AVANCA/VOLTA e libera a memória alocada para ele
 * @param dados Ponteiro genérico para a ação AVANCA/VOLTA (tVaiVolta)
 */
void desalocaVaiVolta(void* dados)
{
    tVaiVolta *movimentarCast = (tVaiVolta*)dados;
    free(movimentarCast);
}

/**
 * @brief Aloca dinamicamente uma ação do tipo AVANCA/VOLTA e guarda nela o deslocamento
 * @param qtd Deslocamento em casas (positivo para AVANCA, negativo para VOLTA)
 * @return Ponteiro para a ação criada
 */
tVaiVolta *criaVaiVolta(int qtd)
{
    tVaiVolta *v = (tVaiVolta*)malloc(sizeof(tVaiVolta));

    v->n = qtd;

    return v;
}

/**
 * @brief Lê da entrada padrão a quantidade de casas (a palavra AVANCA ou VOLTA já deve ter sido lida),
 * multiplica pelo sinal informado e cria a ação com criaVaiVolta.
 * @param vaiOuVolta Sinal do deslocamento: 1 para AVANCA e -1 para VOLTA
 * @return Ponteiro para a ação criada
 */
tVaiVolta *leVaiVolta(int vaiOuVolta)
{
    int qtd =0;

    scanf("%d\n",&qtd);

    qtd = qtd * vaiOuVolta;

    return criaVaiVolta(qtd);
}
 