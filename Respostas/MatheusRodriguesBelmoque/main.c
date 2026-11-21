#include "mapa.h"
#include "jogador.h"
#include "acao_monstro.h"
#include "registra_mapa.h"
#include "dado.h"
#include "celula.h"

#include <stdio.h>
#include <stdlib.h>

int main(){

    Mapa *m = criaMapa();

    leMapa(m);

    imprimeCelulasMapa(m);

    desalocaMapa(m);

    return 0;
}