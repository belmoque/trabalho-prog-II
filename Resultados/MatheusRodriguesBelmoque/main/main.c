#include "mapa.h"
#include "registra_mapa.h"
#include "partida.h"

#include <stdio.h>
#include <string.h>

#define MAX_COMANDO 32

/**
 * @brief Função principal: cria e lê o mapa, cria a partida e interpreta os comandos da entrada
 * padrão (J, ROLAGEM, E ESTADO/RANKING/RELATORIO e F), delegando as regras ao TAD Partida.
 * @return 0
 */
int main() {
    Mapa *m = criaMapa();
    leMapa(m);

    Partida *p = criaPartida(m); /* a partida passa a ser dona do mapa */
    char cmd[MAX_COMANDO];

    while (scanf("%31s", cmd) == 1) {
        if (strcmp(cmd, "F") == 0) {
            break;
        } else if (strcmp(cmd, "J") == 0) {
            cadastraJogadorPartida(p);
        } else if (strcmp(cmd, "ROLAGEM") == 0) {
            int n;
            if (scanf("%d", &n) == 1)
                rolagemPartida(p, n);
        } else if (strcmp(cmd, "E") == 0) {
            char sub[MAX_COMANDO];
            if (scanf("%31s", sub) != 1)
                break;
            if (strcmp(sub, "ESTADO") == 0)
                imprimeEstadoPartida(p);
            else if (strcmp(sub, "RANKING") == 0)
                imprimeRankingPartida(p);
            else if (strcmp(sub, "RELATORIO") == 0)
                imprimeRelatorioPartida(p);
        }
        /* Qualquer outro token (ex: o "MAPA" de "FIM MAPA") é ignorado. */
    }

    desalocaPartida(p);
    return 0;
}
