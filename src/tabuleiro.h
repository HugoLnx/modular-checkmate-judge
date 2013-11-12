#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              tabuleiro.h
*  Letras identificadoras:      TAB
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Matriz adaptada para ser tabuleiro.
*
*  Descrição do módulo
*     Módulo que manipula uma matriz genérica de largura e altura 8.
*     A estrutura matricial do tabuleiro é representada atravpes de um grafo.
*     Cada casa possui 8 arestas com destino às casas existentes nas 8 direções
*     ao redor da casa.
*
***************************************************************************/
 
#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

#define LARGURA        8
#define ALTURA         8

#include "lista.h"
#include "direcao.h"


/* Tipo referência para um Tabuleiro */
typedef struct TAB_stTabuleiro* TAB_tppTabuleiro;

/***********************************************************************
*
*  Tipo de dados: TAB Condições de retorno
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/
   typedef enum {

         TAB_CondRetOK = 0,
               /* Executou correto */

         TAB_CondRetNaoEhCasa = 2,
               /* Não é nó na direção desejada */

         TAB_CondRetTabuleiroNaoExiste = 3,
               /* Tabuleiro não existe */

         TAB_CondRetFaltouMemoria = 5
               /* Faltou memória ao alocar dados */

   } TAB_tpCondRet;

/***********************************************************************
*
*  Função: TAB Criar tabuleiro
*
*  Descrição
*     Cria uma instância de tabuleiro.
*
*  Parâmetros
*     ppTabuleiro      - Referência para retornar o novo tabuleiro.
*     destruirValor    - Referência para a função que será utilizada para
*                        liberar os valores de cada casa do tabuleiro da
*                        memória.
*
*  Condições de retorno
*     TAB_CondRetOK
*     TAB_CondRetFaltaMemoria
*
*  Retorno por referência
*     ppTabuleiro - Retorno da nova instância de tabuleiro.
*
*  Hipóteses
*     - ppTabuleiro não apontará para nenhuma estrutura que necessite ser
*       tratada de forma alguma.
*
*  Assertivas de entrada
*     - ppTabuleiro é um ponteiro válido
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do Tabuleiro.
*     - ppTabuleiro possui uma instância válida de Tabuleiro.
*
***********************************************************************/
   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro, void (*destruirValor)(void *pValor));

/***********************************************************************
*
*  Função: TAB Obter valor
*
*  Descrição
*     Obter o valor da casa corrente.
*
*  Parâmetros
*     pTabuleiro    - Tabuleiro que será usada como base.
*     ppValor       - Referencia para retornar o valor na casa corrente.
*
*  Condições de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Retorno por referência
*     ppValor        - valor da casa corrente.
*
*  Assertivas de entrada
*     Valem as assertivas estruturais do tabuleiro.
*
*  Assertivas de saida
*     - Tabuleiro não foi alterado.
*     - ppValor aponta para o valor da casa corrente.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterValor(TAB_tppTabuleiro pTabuleiro, void **ppValor);

/***********************************************************************
*
*  Função: TAB Alterar valor
*
*  Descrição
*     Substitui valor da casa corrente por um novo.
*
*  Parâmetros
*     pTabuleiro   - Tabuleiro que será usada como base.
*     pValor       - Novo valor para a casa corrente.
*
*  Condições de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do tabuleiro.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do tabuleiro.
*     - Valor da casa corrente mudou para o passado por parâmetro.
*
***********************************************************************/
   TAB_tpCondRet TAB_AlterarValor(TAB_tppTabuleiro pTabuleiro, void *pValor);

/***********************************************************************
*
*  Função: TAB Destruir tabuleiro
*
*  Descrição
*     Destroi a instância, liberando-a a memória.
*
*  Parâmetros
*     ppTabuleiro      - Referencia para o tabuleiro à ser destruido.
*
*  Condições de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Retorno por referência
*     ppTabuleiro  - retorna NULL
*
*  Assertivas de entrada
*     - ppTabuleiro é NULL ou aponta para uma Tabuleiro válida.
*
*  Assertivas de saida
*     - A instância apontada por ppTabuleiro é liberada da memória.
*     - ppTabuleiro aponta para NULL
*
***********************************************************************/
   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro *ppTabuleiro);

/***********************************************************************
*
*  Função: TAB Ir casa
*
*  Descrição
*     Muda corrente baseado no nome da casa.
*
*  Parâmetros
*     pTabuleiro - Tabuleiro que será usada como base.
*     nomeCasa - Nome de uma casa no tabuleiro da partida.
*
*  Condições de retorno
*     TAB_CondRetOK
*     TAB_CondRetNaoEhCasa
*     TAB_CondRetTabuleiroNaoExiste
*
*  Assertivas de entrada
*     - pTabuleiro aponta para um Tabuleiro válido.
*
*  Assertivas de saida
*     - O corrente de pTabuleiro aponta para a casa com o nome igual ao passado
*       por parâmetro, ou permanece o mesmo, caso não exista casa com este nome.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrCasa(TAB_tppTabuleiro pTabuleiro, char *nome);


/***********************************************************************
*
*  Função: TAB Percorrer casas
*
*  Descrição
*     Percorre todas as casas aplicando operações definidas pelo módulo cliente
*     através de uma função passada por ponteiro.
*
*  Parâmetros
*     pTabuleiro - Tabuleiro que será usada como base.
*     fazerNaCasa - Ponteiro para função que será aplicada em cada casa do tabuleiro.
*
*  Condições de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Assertivas de entrada
*     - pTabuleiro aponta para um Tabuleiro válido.
*
*  Assertivas de saida
*     - Função terá sido aplicada em todas as casas do tabuleiro.
*
***********************************************************************/
   TAB_tpCondRet TAB_PercorrerCasas(TAB_tppTabuleiro pTabuleiro, int (*fazerNaCasa)(TAB_tppTabuleiro pTabuleiro, char *nome));

/***********************************************************************
*
*  Função: TAB Nome da casa
*
*  Descrição
*     Recebe as coordenadas e retorna o nome da casa nesta coordenada.
*
*  Parâmetros
*     x, y   - Coordenada da casa.
*     pNome  - Referência para retornar o nome da casa
*
*  Condições de retorno
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  Retorno por referência
*     pNome  - Nome da casa nesta coordenada.
*
*  Assertivas de entrada
*     - x está entre zero e a largura-1.
*     - y está entre zero e a altura-1.
*     - pNome é um ponteiro válido.
*
*  Assertivas de saida
*     - pNome é uma string de 2 caracteres com o nome da casa.
*
***********************************************************************/
   TAB_tpCondRet TAB_NomeDaCasa(int x, int y, char **pNome);

/***************************************************************************
*
*  Função: TAB Ir para
*  
*  Descrição da função
*  Muda a casa corrente do tabuleiro para a casa na direção apontada
*  
*  Parâmetros
*     pTabuleiro - ponteiro para o tabuleiro que será manipulado.
*     direcao    - representa a direção que o nó corrente navegará.
*
*  Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetNaoEhCasa
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do tabuleiro.
*     - Existe casa com o nome passado por parâmetro.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do tabuleiro.
*     - Casa corrente é a casa com o nome passado por parâmetro.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrPara(TAB_tppTabuleiro pTabuleiro, DIR_tpDirecao);


#undef TABULEIRO_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
