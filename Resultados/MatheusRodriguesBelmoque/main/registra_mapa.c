#include "registra_mapa.h"

#include "mapa.h"
#include "ouro.h"
#include "item.h"
#include "vazio.h"
#include "avancar_voltar.h"
#include "acao_monstro.h"
#include <stdio.h>
#include <string.h>

#define VAI 1
#define VOLTA -1

/**
 * @brief Lê da entrada padrão o cadastro do mapa: descarta a linha INICIO MAPA e, para cada palavra lida,
 * identifica o tipo da célula (OURO, VAZIA, ITEM, AVANCA ou VOLTA), lê os parâmetros desse tipo e insere
 * a célula no mapa com insereCelulaMapa. A leitura termina ao ler a palavra FIM (a palavra MAPA que
 * a segue não é consumida).
 * @param m Mapa onde as células serão inseridas
 * @return Sem valor definido (a função ainda não possui return)
 */
int leMapa(Mapa *m)
{
    char leituraAtual[10];
    int numCelulas = 0;

    scanf("%*[^\n]\n"); // Descarta a primeira linha da entrada de MAPA

    while (scanf("%s", leituraAtual) == 1 && strcmp(leituraAtual, "FIM") != 0)
    {
        numCelulas++;

        if (strcmp(leituraAtual, "OURO") == 0)
        {
            tOuro *o = leOuro();

            insereCelulaMapa(m, o, executaOuro, imprimeOuro, desalocaOuro);
        }
        else if (strcmp(leituraAtual, "VAZIA") == 0)
        {
            insereCelulaMapa(m, NULL, executaVazio, imprimeVazio, desalocaVazio);
        }
        else if (strcmp(leituraAtual, "ITEM") == 0)
        {
            tItem *i = leItem();
            insereCelulaMapa(m, i, executaItem, imprimeItem, desalocaItem);
        }
        else if (strcmp(leituraAtual, "AVANCA") == 0)
        {
            tVaiVolta *v = leVaiVolta(VAI);

            insereCelulaMapa(m,v,executaVaiVolta,imprimeVaiVolta,desalocaVaiVolta);
        }
        else if (strcmp(leituraAtual, "VOLTA") == 0)
        {
            tVaiVolta *v = leVaiVolta(VOLTA);

            insereCelulaMapa(m,v,executaVaiVolta,imprimeVaiVolta,desalocaVaiVolta);
        }
        else if(strcmp(leituraAtual, "MONSTRO")==0)
        {
            Monstro *monstro = leMonstro();

            insereCelulaMapa(m,monstro,executaMonstro,imprimeMonstro,desalocaMonstro);
        }
    }

    

    return 0;
}
