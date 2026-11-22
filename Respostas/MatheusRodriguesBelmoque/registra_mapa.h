#ifndef _REGISTRA_MAPA_
#define _REGISTRA_MAPA_

#include "mapa.h"

/**
 * @brief Lê da entrada padrão o cadastro do mapa: descarta a linha INICIO MAPA e, para cada palavra lida,
 * identifica o tipo da célula (OURO, VAZIA, ITEM, AVANCA ou VOLTA), lê os parâmetros desse tipo e insere
 * a célula no mapa com insereCelulaMapa. A leitura termina ao ler a palavra FIM (a palavra MAPA que
 * a segue não é consumida).
 * @param m Mapa onde as células serão inseridas
 * @return Sem valor definido (a função ainda não possui return)
 */
int leMapa(Mapa *m);


#endif // _REGISTRA_MAPA_
