#include "mapa.h"
#include "jogador.h"
#include "acao_monstro.h"
#include "registra_mapa.h"
#include "dado.h"
#include "celula.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Função principal do programa: cria o mapa, lê o seu cadastro da entrada padrão (leMapa),
 * imprime as células (imprimeCelulasMapa) e desaloca o mapa.
 * @return 0
 */
int main(){

    Mapa *m = criaMapa();

    leMapa(m);

    imprimeCelulasMapa(m);

    desalocaMapa(m);

    return 0;
}