#include "partida.h"
#include "jogador.h"
#include "celula.h"
#include "dado.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Partida do Jogo da Void: agrupa o mapa, os jogadores cadastrados (vetor dinâmico na ordem de
 * cadastro), a quantidade de jogadores, o índice do jogador da próxima vez e o vencedor
 * (NULL enquanto a partida está em andamento).
 */
struct Partida
{
    Mapa *mapa;
    Jogador **jogadores;
    int qtd;
    int proximo;
    Jogador *vencedor;
};

/**
 * @brief Aloca dinamicamente uma partida sem jogadores e sem vencedor. A partida passa a ser dona
 * do mapa: ele é desalocado em desalocaPartida.
 * @param m Mapa já lido e cadastrado
 * @return Ponteiro para a partida criada
 */
Partida *criaPartida(Mapa *m)
{
    Partida *partidaCriada = (Partida *)malloc(sizeof(Partida));
    if (partidaCriada == NULL)
    {
        exit(1);
    }

    partidaCriada->mapa = m;
    partidaCriada->jogadores = NULL;
    partidaCriada->qtd = 0;
    partidaCriada->proximo = 0;
    partidaCriada->vencedor = NULL;
    return partidaCriada;
}

/**
 * @brief Lê um jogador da entrada padrão (o caractere J já deve ter sido lido) e o cadastra ao
 * final da lista. O jogador é sempre lido, para consumir a entrada; se já existir um jogador com o
 * mesmo nome, o novo jogador é desalocado sem ser cadastrado.
 * @param p Partida
 */
void cadastraJogadorPartida(Partida *p)
{
    Jogador *jogadorCriado = leJogador();

    for (int i = 0; i < p->qtd; i++)
    {
        if (comparaNomeJogador(p->jogadores[i], obtemNomeJogador(jogadorCriado)))
        {
            desalocaJogador(jogadorCriado);
            return;
        }
    }

    Jogador **novoVetor = (Jogador **)realloc(p->jogadores, (p->qtd + 1) * sizeof(Jogador *));
    if (novoVetor == NULL)
    {
        desalocaJogador(jogadorCriado);
        return;
    }
    p->jogadores = novoVetor;
    p->jogadores[p->qtd] = jogadorCriado;
    p->qtd++;
}

/**
 * @brief Desaloca o mapa, cada jogador, o vetor de jogadores e a própria partida. O mapa guarda
 * apenas referências aos jogadores, então a ordem de liberação não causa problema.
 * @param p Partida
 */
void desalocaPartida(Partida *p)
{
    desalocaMapa(p->mapa);
    for (int i = 0; i < p->qtd; i++)
    {
        desalocaJogador(p->jogadores[i]);
    }
    free(p->jogadores);
    free(p);
}

/**
 * @brief Leva o jogador até a casa 'destino', resolvendo disputa se ela estiver ocupada. O jogador
 * sai da casa de origem antes da chegada, para que a origem conte como livre em eventuais recuos.
 * Não executa a ação da célula de destino.
 * @param m Mapa
 * @param j Jogador que está chegando
 * @param destino Casa de destino
 * @return 1 se o jogador ficou em 'destino'; 0 se perdeu a disputa e recuou
 */
int chegaNaCasa(Mapa *m, Jogador *j, int destino)
{
    int fim = obtemPosicaoFimMapa(m);

    retiraJogadorMapa(m, j);

    if (destino >= fim)
    {
        moveJogadorMapa(m, j, fim);
        return 1;
    }

    Jogador *ocupante = obtemOcupanteMapa(m, destino);
    if (ocupante == NULL)
    {
        moveJogadorMapa(m, j, destino);
        return 1;
    }

    if (venceDisputaJogador(j, ocupante))
    {
        incrementaDisputasVencidasJogador(j);
        recuaJogadorMapa(m, ocupante, destino);
        moveJogadorMapa(m, j, destino);
        return 1;
    }

    incrementaDisputasVencidasJogador(ocupante);
    recuaJogadorMapa(m, j, destino);
    return 0;
}

/**
 * @brief Verifica se o jogador chegou à casa Fim
 * @param m Mapa
 * @param j Jogador
 * @return 1 se o jogador está no Fim, 0 caso contrário
 */
int chegouAoFim(Mapa *m, Jogador *j)
{
    return obtemPosicaoJogador(j) >= obtemPosicaoFimMapa(m);
}

/**
 * @brief Executa uma jogada completa do jogador: chama o dado exatamente uma vez, move o jogador,
 * resolve a disputa e executa a ação da célula. Se o jogador perder a disputa, o turno acaba. Em
 * AVANCA/VOLTA, a ação da nova casa não é executada. Atualiza o vencedor da partida se alguém
 * chegar ao Fim.
 * @param p Partida
 * @param j Jogador da vez
 */
void executaJogada(Partida *p, Jogador *j)
{
    Mapa *m = p->mapa;

    int d = RolaDado();
    incrementaJogadasJogador(j);

    if (!chegaNaCasa(m, j, obtemPosicaoJogador(j) + d))
    {
        return;
    }

    if (chegouAoFim(m, j))
    {
        p->vencedor = j;
        return;
    }

    Celula *c = obtemCelulaMapa(m, obtemPosicaoJogador(j));
    if (c == NULL)
    {
        return;
    }

    int resultado = executaAcaoCelula(c, j);

    if (resultado == RECUO_CELULA)
    {
        recuaJogadorMapa(m, j, obtemPosicaoJogador(j));
    }
    else if (resultado != 0)
    {
        int destino = obtemPosicaoJogador(j) + resultado;
        if (destino < 0)
        {
            destino = 0;
        }
        if (chegaNaCasa(m, j, destino) && chegouAoFim(m, j))
        {
            p->vencedor = j;
        }
    }
}

/**
 * @brief Executa até n turnos em fila rotativa, na ordem de cadastro. Para imediatamente se algum
 * jogador vencer; não faz nada se a partida já tiver vencedor ou não houver jogadores.
 * @param p Partida
 * @param n Quantidade de turnos a executar
 */
void rolagemPartida(Partida *p, int n)
{
    for (int k = 0; k < n && p->vencedor == NULL && p->qtd > 0; k++)
    {
        Jogador *j = p->jogadores[p->proximo];
        p->proximo = (p->proximo + 1) % p->qtd;
        executaJogada(p, j);
    }
}

/**
 * @brief Imprime a linha de situação da partida (EM ANDAMENTO ou VENCEDOR <nome>)
 * @param p Partida
 */
void imprimeSituacao(Partida *p)
{
    if (p->vencedor == NULL)
    {
        printf("- Situacao: EM ANDAMENTO\n");
    }
    else
    {
        printf("- Situacao: VENCEDOR %s\n", obtemNomeJogador(p->vencedor));
    }
}

/**
 * @brief Imprime a linha [INICIO] seguida dos jogadores que estão na casa 0, na ordem de cadastro
 * @param p Partida
 */
void imprimeInicio(Partida *p)
{
    printf("[INICIO]");
    int primeiro = 1;
    for (int i = 0; i < p->qtd; i++)
    {
        if (obtemPosicaoJogador(p->jogadores[i]) == 0)
        {
            printf(primeiro ? " <- %s" : ", %s", obtemNomeJogador(p->jogadores[i]));
            primeiro = 0;
        }
    }
    printf("\n");
}

/**
 * @brief Imprime a linha [FIM] seguida do vencedor, se houver
 * @param p Partida
 */
void imprimeFim(Partida *p)
{
    printf("[FIM]");
    if (p->vencedor != NULL)
    {
        printf(" <- %s", obtemNomeJogador(p->vencedor));
    }
    printf("\n");
}

/**
 * @brief Imprime o ESTADO da partida: início, células do mapa, fim, linha de cada jogador e situação
 * @param p Partida
 */
void imprimeEstadoPartida(Partida *p)
{
    printf("=========== ESTADO ============\n");
    imprimeInicio(p);
    imprimeCelulasMapa(p->mapa);
    imprimeFim(p);
    printf("-------------------------------\n");
    for (int i = 0; i < p->qtd; i++)
    {
        printEstadoJogador(p->jogadores[i]);
    }
    imprimeSituacao(p);
    printf("===============================\n");
}

/**
 * @brief Imprime o RANKING ordenando um vetor auxiliar de ponteiros (qsort com comparaOrdJogador),
 * de modo que a lista original de jogadores não é alterada
 * @param p Partida
 */
void imprimeRankingPartida(Partida *p)
{
    Jogador **ordenados = NULL;
    if (p->qtd > 0)
    {
        ordenados = (Jogador **)malloc(p->qtd * sizeof(Jogador *));
        if (ordenados == NULL)
        {
            return;
        }
        memcpy(ordenados, p->jogadores, p->qtd * sizeof(Jogador *));
        qsort(ordenados, p->qtd, sizeof(Jogador *), comparaOrdJogador);
    }

    printf("=========== RANKING ===========\n");
    for (int i = 0; i < p->qtd; i++)
    {
        printRankingJogador(ordenados[i], i + 1);
    }
    printf("===============================\n");

    free(ordenados);
}

/**
 * @brief Imprime o RELATORIO com os totais da partida e as estatísticas de cada jogador. Cada disputa
 * tem exatamente um vencedor, então o total de disputas é a soma das disputas vencidas
 * @param p Partida
 */
void imprimeRelatorioPartida(Partida *p)
{
    int jogadas = 0, disputas = 0, monstros = 0;
    for (int i = 0; i < p->qtd; i++)
    {
        jogadas += obtemJogadasJogador(p->jogadores[i]);
        disputas += obtemDisputasVencidasJogador(p->jogadores[i]);
        monstros += obtemMonstrosDerrotadosJogador(p->jogadores[i]);
    }

    printf("========= RELATORIO ===========\n");
    printf("- Celulas do mapa: %d\n", obtemQtdCelulasMapa(p->mapa));
    printf("- Jogadores: %d\n", p->qtd);
    printf("- Jogadas totais: %d\n", jogadas);
    printf("- Disputas: %d\n", disputas);
    printf("- Monstros derrotados: %d\n", monstros);
    imprimeSituacao(p);
    printf("-------------------------------\n");
    for (int i = 0; i < p->qtd; i++)
    {
        printRelatorioJogador(p->jogadores[i]);
    }
    printf("===============================\n");
}
