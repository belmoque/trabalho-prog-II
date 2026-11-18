#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_NOME_JOGADOR 51
#define MAX_TAM_COR_JOGADOR 16

typedef struct 
{

    char nome[MAX_TAM_NOME_JOGADOR];
    char cor[MAX_TAM_COR_JOGADOR];
    int forca;
    int posicao;
    int xp;
    int ouro;
    int jogadas;
    int disputasVencidas;
    int monstrosDerrotados;
    
}Jogador;

/**
 * @brief Aloca dinamicamente um jogador e copia o nome e a cor informados. O jogador inicia no
 * Início do mapa (posição 0), com 0 de XP, 0 de ouro e todas as estatísticas (jogadas, disputas
 * vencidas e monstros derrotados) zeradas.
 * @param nome Nome do jogador (identificador único)
 * @param cor Cor do jogador
 * @param forca Força inicial do jogador
 * @return Ponteiro para o jogador criado
 */
Jogador *criaJogador(char *nome, char *cor, int forca)
{
    Jogador *jogadorCriado = (Jogador*)malloc(sizeof(Jogador));

    strcpy(jogadorCriado->nome,nome);
    strcpy(jogadorCriado->cor, cor);
    
    jogadorCriado->forca = forca;
    jogadorCriado->posicao = 1;
    jogadorCriado->xp = 0;
    jogadorCriado->ouro = 0;
    jogadorCriado->jogadas = 0;
    jogadorCriado->disputasVencidas = 0;
    jogadorCriado->monstrosDerrotados = 0;
}

/**
 * @brief Lê da entrada padrão, nesta ordem e um por linha, o nome, a cor e a força inicial de um
 * jogador (o caractere J já deve ter sido lido) e cria o jogador com criaJogador.
 * @return Ponteiro para o jogador criado
 */
Jogador *leJogador()
{
    char nome[MAX_TAM_NOME_JOGADOR] = {0}, cor[MAX_TAM_COR_JOGADOR] = {0};
    int forca;

    scanf("%[^\n]",nome);
    scanf("%*[\n]");
    scanf("%[^\n]",cor);
    scanf("%*[\n]");
    scanf("%d",&forca);

    Jogador *jogadorCriado = criaJogador(nome,cor,forca); 

    return jogadorCriado;
}

/**
 * @brief Aloca um novo jogador e copia para ele todos os campos do jogador informado (nome, cor,
 * força, XP, ouro, posição e estatísticas). Usada para gerar o ranking sem alterar a lista original.
 * @param d Ponteiro genérico para o jogador a ser copiado
 * @return Ponteiro genérico para a cópia
 */
void *copiaJogador(void *d)
{
    Jogador *ptr_copiado = (Jogador*)d;
    Jogador *jogadorCopia = criaJogador(ptr_copiado->nome,ptr_copiado->cor,ptr_copiado->forca);

    return jogadorCopia;
}

/**
 * @brief Converte o dado genérico para jogador e compara (strcmp) o seu nome com o nome informado.
 * Usada para buscar jogadores na lista e impedir o cadastro de nomes repetidos.
 * @param dado Ponteiro genérico para o jogador
 * @param nome Ponteiro genérico para a string com o nome a ser comparado
 * @return 1 se os nomes forem iguais, 0 caso contrário
 */
int comparaNomeJogador(void *dado, void *nome)
{
    Jogador *ptr_jogador = (Jogador*)dado;

    if(strcmp(ptr_jogador->nome,nome)==0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Função de comparação no formato do qsort para ordenar um vetor de ponteiros para jogador
 * (cada parâmetro é, na verdade, um Jogador **). Critérios, em ordem: maior posição primeiro; em caso
 * de empate, maior força primeiro; depois, maior XP primeiro; por fim, ordem alfabética do nome.
 * @param d1 Ponteiro para o primeiro elemento do vetor (Jogador **)
 * @param d2 Ponteiro para o segundo elemento do vetor (Jogador **)
 * @return Valor negativo se d1 deve vir antes de d2, positivo se deve vir depois e 0 se forem equivalentes
 */
int comparaOrdJogador(const void *d1, const void *d2)
{
    Jogador *ptr_elemento1 = (Jogador*)d1;
    Jogador *ptr_elemento2 = (Jogador*)d2;

    if(ptr_elemento1->posicao > ptr_elemento2->posicao)
    {
        return -1;
    }
    else if(ptr_elemento1->posicao < ptr_elemento2->posicao)
    {
        return 1;
    }
    else //Em caso de empate verifica a força
    {
        if(ptr_elemento1->forca > ptr_elemento2->forca)
        {
            return -1;
        }
        else if(ptr_elemento1->forca < ptr_elemento2->forca)
        {
            return 1;
        }
        else //Em caso de a força também empatar verifica o XP
        {
            if(ptr_elemento1->xp > ptr_elemento2->xp)
            {
                return -1;
            }
            else if(ptr_elemento1->xp < ptr_elemento2->xp)
            {
                return 1;
            }
            else //caso de empate tambem do xp retorna o valor de strcmp dos nomes (ordem alfabetica)
            {
                return strcmp(ptr_elemento1->nome,ptr_elemento2->nome);
            }
        }
    }

}

/**
 * @brief Decide a disputa por uma célula. O desafiante vence se tiver mais força que o ocupante; se
 * as forças forem iguais, vence se tiver mais XP; se também houver empate na XP, o ocupante vence.
 * Esta função apenas decide o vencedor: não altera os jogadores nem as estatísticas.
 * @param desafiante Jogador que chegou à célula
 * @param ocupante Jogador que já estava na célula
 * @return 1 se o desafiante vencer, 0 se o ocupante vencer
 */
int venceDisputaJogador(Jogador *desafiante, Jogador *ocupante)
{
    if(desafiante->forca > ocupante->forca)
    {
        return 1;
    }
    else if(desafiante->forca == ocupante->forca)
    {
        if(desafiante->xp > ocupante->xp)
        {
            return 1;
        }
        else if(desafiante->xp == ocupante->xp)
        {
            return 0;
        }
    }

    return 0;
}

/**
 * @brief Retorna o nome do jogador
 * @param j Jogador
 * @return Ponteiro para a string com o nome do jogador
 */
char *obtemNomeJogador(Jogador *j)
{
    return j->nome;
}

/**
 * @brief Retorna a casa do mapa em que o jogador está (0 = Início, N + 1 = Fim)
 * @param j Jogador
 * @return Posição atual do jogador
 */
int obtemPosicaoJogador(Jogador *j)
{
    return j->posicao;
}

/**
 * @brief Retorna a força atual do jogador
 * @param j Jogador
 * @return Força do jogador
 */
int obtemForcaJogador(Jogador *j)
{
    return j->forca;
}

/**
 * @brief Retorna a XP atual do jogador
 * @param j Jogador
 * @return XP do jogador
 */
int obtemXPJogador(Jogador *j)
{
    return j->xp;
}

/**
 * @brief Retorna a quantidade de ouro atual do jogador
 * @param j Jogador
 * @return Ouro do jogador
 */
int obtemOuroJogador(Jogador *j)
{
    return j->ouro;
}

/**
 * @brief Retorna quantas jogadas o jogador já realizou
 * @param j Jogador
 * @return Quantidade de jogadas do jogador
 */
int obtemJogadasJogador(Jogador *j)
{
    return j->jogadas;
}

/**
 * @brief Retorna quantas disputas territoriais o jogador já venceu (como desafiante ou como ocupante)
 * @param j Jogador
 * @return Quantidade de disputas vencidas
 */
int obtemDisputasVencidasJogador(Jogador *j)
{
    return j->disputasVencidas;
}

/**
 * @brief Retorna quantos monstros o jogador já derrotou
 * @param j Jogador
 * @return Quantidade de monstros derrotados
 */
int obtemMonstrosDerrotadosJogador(Jogador *j)
{
    return j->monstrosDerrotados;
}

/**
 * @brief Altera a posição do jogador para a casa informada. Apenas atualiza o campo do jogador:
 * não altera a ocupação das células do mapa.
 * @param j Jogador
 * @param posicao Nova posição do jogador
 */
void definePosicaoJogador(Jogador *j, int posicao)
{
    j->posicao = posicao;
}

/**
 * @brief Soma o valor informado à força do jogador
 * @param j Jogador
 * @param forca Valor a ser somado à força
 */
void adicionaForcaJogador(Jogador *j, int forca)
{
    j->forca += forca;
}

/**
 * @brief Soma o valor informado à XP do jogador
 * @param j Jogador
 * @param xp Valor a ser somado à XP
 */
void adicionaXPJogador(Jogador *j, int xp)
{
    j->xp += xp;
}

/**
 * @brief Soma o valor informado ao ouro do jogador (um valor negativo desconta ouro, ex: compra de item)
 * @param j Jogador
 * @param ouro Valor a ser somado ao ouro
 */
void adicionaOuroJogador(Jogador *j, int ouro)
{
    j->ouro += ouro;
}

/**
 * @brief Soma 1 à quantidade de jogadas do jogador
 * @param j Jogador
 */
void incrementaJogadasJogador(Jogador *j)
{
    j->jogadas++;
}

/**
 * @brief Soma 1 à quantidade de disputas vencidas pelo jogador
 * @param j Jogador
 */
void incrementaDisputasVencidasJogador(Jogador *j)
{
    j->disputasVencidas++;
}

/**
 * @brief Soma 1 à quantidade de monstros derrotados pelo jogador
 * @param j Jogador
 */
void incrementaMonstrosDerrotadosJogador(Jogador *j)
{
    j->monstrosDerrotados++;
}

/**
 * @brief Converte o dado genérico para jogador e imprime uma linha no formato do ESTADO:
 * "- <nome>: casa <posicao> | forca <forca> | xp <xp> | ouro <ouro>" seguido de quebra de linha.
 * @param dado Ponteiro genérico para o jogador
 */
void printEstadoJogador(void *dado)
{
    Jogador *ptr_jogador = (Jogador*)dado;

    printf("- %s: casa %d | forca %d | xp %d | ouro %d\n",ptr_jogador->nome,ptr_jogador->posicao,ptr_jogador->forca,ptr_jogador->xp,ptr_jogador->ouro);
}

/**
 * @brief Imprime uma linha no formato do RANKING:
 * "<colocacao>. <nome> (<cor>) | casa <posicao> | forca <forca> | xp <xp>" seguido de quebra de linha.
 * @param j Jogador
 * @param colocacao Colocação do jogador no ranking (começando em 1)
 */
void printRankingJogador(Jogador *j, int colocacao)
{
    printf("%d. %s (%s) | casa %d | forca %d | xp %d\n",colocacao,j->nome,j->cor,j->posicao,j->forca,j->xp);
}

/**
 * @brief Converte o dado genérico para jogador e imprime uma linha no formato do RELATORIO:
 * "- <nome>: jogadas <jogadas> | disputas vencidas <disputas> | forca <forca> | xp <xp> | ouro <ouro>"
 * seguido de quebra de linha.
 * @param dado Ponteiro genérico para o jogador
 */
void printRelatorioJogador(void *dado)
{
    Jogador *ptr_jogador = (Jogador*)dado;

    printf("- %s: jogadas %d | disputas vencidas %d | forca %d | xp %d | ouro %d\n",ptr_jogador->nome,ptr_jogador->jogadas,ptr_jogador->disputasVencidas,ptr_jogador->forca,ptr_jogador->xp,ptr_jogador->ouro);
}

/**
 * @brief Converte o dado genérico para jogador e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o jogador
 */
void desalocaJogador(void *dado)
{
    Jogador *ptr_jogador = (Jogador*)dado;
    //free(ptr_jogador->cor);
    //free(ptr_jogador->nome);
    free(ptr_jogador);
}

