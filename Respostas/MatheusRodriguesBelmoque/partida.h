#ifndef _PARTIDA_H_
#define _PARTIDA_H_

#include "mapa.h"

/**
 * Partida do Jogo da Void: agrupa o mapa, os jogadores cadastrados (na ordem de cadastro),
 * a fila de turnos e o vencedor. A struct é opaca: o acesso é feito apenas pelas funções abaixo.
 */
typedef struct Partida Partida;

/**
 * @brief Aloca dinamicamente uma partida sem jogadores e sem vencedor.
 * A partida passa a ser dona do mapa: ele é desalocado em desalocaPartida.
 * @param m Mapa já lido e cadastrado
 * @return Ponteiro para a partida criada
 */
Partida *criaPartida(Mapa *m);

/**
 * @brief Lê um jogador da entrada padrão (o caractere J já deve ter sido lido) e o cadastra ao
 * final da lista. Se já existir um jogador com o mesmo nome, o novo é descartado sem cadastro.
 * @param p Partida
 */
void cadastraJogadorPartida(Partida *p);

/**
 * @brief Executa até n turnos em fila rotativa, na ordem de cadastro. Cada turno chama o dado
 * uma única vez, move o jogador, resolve disputas e executa a ação da célula. Para imediatamente
 * se algum jogador vencer; não faz nada se a partida já tiver vencedor ou não houver jogadores.
 * @param p Partida
 * @param n Quantidade de turnos a executar
 */
void rolagemPartida(Partida *p, int n);

/**
 * @brief Imprime o ESTADO da partida: início, células do mapa, fim, linha de cada jogador e situação.
 * @param p Partida
 */
void imprimeEstadoPartida(Partida *p);

/**
 * @brief Imprime o RANKING, ordenado por posição, força, XP e nome. A lista original não é alterada.
 * @param p Partida
 */
void imprimeRankingPartida(Partida *p);

/**
 * @brief Imprime o RELATORIO com os totais da partida e as estatísticas de cada jogador.
 * @param p Partida
 */
void imprimeRelatorioPartida(Partida *p);

/**
 * @brief Desaloca a partida: o mapa, cada jogador, o vetor de jogadores e a própria partida.
 * @param p Partida
 */
void desalocaPartida(Partida *p);

#endif // _PARTIDA_H_
