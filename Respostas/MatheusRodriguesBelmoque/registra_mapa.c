
#include "mapa.h"
#include "ouro.h"
#include "item.h"
#include "vazio.h"
#include <stdio.h>
#include <string.h>

int leMapa(Mapa *m)
{
    char leituraAtual[10];
    int numCelulas = 0;

    scanf("%*[^\n]\n");//Descarta a primeira linha da entrada de MAPA

    while (scanf("%s",leituraAtual) == 1 && strcmp(leituraAtual,"FIM") != 0)
    {
        numCelulas++;

        if(strcmp(leituraAtual,"OURO")==0)
        {
            tOuro *o = leOuro();

            insereCelulaMapa(m,o,executaOuro,imprimeOuro,desalocaOuro);
        }

        if(strcmp(leituraAtual,"VAZIA")==0)
        {
            insereCelulaMapa(m,NULL,executaVazio,imprimeVazio,desalocaVazio);
        }

        if(strcmp(leituraAtual,"ITEM")==0)
        {
            tItem *i = leItem();
            insereCelulaMapa(m,i,executaItem,imprimeItem,desalocaItem);
        }
    }
    
}

