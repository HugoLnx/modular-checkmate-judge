#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  M�dulo de defini��o: TAB  Tabuleiro
*
*  Arquivo gerado:              tabuleiro.h
*  Letras identificadoras:      TAB
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Matriz adaptada para ser tabuleiro.
*
*  Descri��o do m�dulo
*     M�dulo que manipula uma matriz gen�rica de largura e altura 8.
*     A estrutura matricial do tabuleiro � representada atravpes de um grafo.
*     Cada casa possui 8 arestas com destino �s casas existentes nas 8 dire��es
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


/* Tipo refer�ncia para um Tabuleiro */
typedef struct TAB_stTabuleiro* TAB_tppTabuleiro;

/***********************************************************************
*
*  Tipo de dados: TAB Condi��es de retorno
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/
   typedef enum {

         TAB_CondRetOK = 0,
               /* Executou correto */

         TAB_CondRetNaoEhCasa = 2,
               /* N�o � n� na dire��o desejada */

         TAB_CondRetTabuleiroNaoExiste = 3,
               /* Tabuleiro n�o existe */

         TAB_CondRetFaltouMemoria = 5
               /* Faltou mem�ria ao alocar dados */

   } TAB_tpCondRet;

/***********************************************************************
*
*  Fun��o: TAB Criar tabuleiro
*
*  Descri��o
*     Cria uma inst�ncia de tabuleiro.
*
*  Par�metros
*     ppTabuleiro      - Refer�ncia para retornar o novo tabuleiro.
*     destruirValor    - Refer�ncia para a fun��o que ser� utilizada para
*                        liberar os valores de cada casa do tabuleiro da
*                        mem�ria.
*
*  Condi��es de retorno
*     TAB_CondRetOK
*     TAB_CondRetFaltaMemoria
*
*  Retorno por refer�ncia
*     ppTabuleiro - Retorno da nova inst�ncia de tabuleiro.
*
*  Hip�teses
*     - ppTabuleiro n�o apontar� para nenhuma estrutura que necessite ser
*       tratada de forma alguma.
*
*  Assertivas de entrada
*     - ppTabuleiro � um ponteiro v�lido
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do Tabuleiro.
*     - ppTabuleiro possui uma inst�ncia v�lida de Tabuleiro.
*
***********************************************************************/
   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro, void (*destruirValor)(void *pValor));

/***********************************************************************
*
*  Fun��o: TAB Obter valor
*
*  Descri��o
*     Obter o valor da casa corrente.
*
*  Par�metros
*     pTabuleiro    - Tabuleiro que ser� usada como base.
*     ppValor       - Referencia para retornar o valor na casa corrente.
*
*  Condi��es de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Retorno por refer�ncia
*     ppValor        - valor da casa corrente.
*
*  Assertivas de entrada
*     Valem as assertivas estruturais do tabuleiro.
*
*  Assertivas de saida
*     - Tabuleiro n�o foi alterado.
*     - ppValor aponta para o valor da casa corrente.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterValor(TAB_tppTabuleiro pTabuleiro, void **ppValor);

/***********************************************************************
*
*  Fun��o: TAB Alterar valor
*
*  Descri��o
*     Substitui valor da casa corrente por um novo.
*
*  Par�metros
*     pTabuleiro   - Tabuleiro que ser� usada como base.
*     pValor       - Novo valor para a casa corrente.
*
*  Condi��es de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do tabuleiro.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do tabuleiro.
*     - Valor da casa corrente mudou para o passado por par�metro.
*
***********************************************************************/
   TAB_tpCondRet TAB_AlterarValor(TAB_tppTabuleiro pTabuleiro, void *pValor);

/***********************************************************************
*
*  Fun��o: TAB Destruir tabuleiro
*
*  Descri��o
*     Destroi a inst�ncia, liberando-a a mem�ria.
*
*  Par�metros
*     ppTabuleiro      - Referencia para o tabuleiro � ser destruido.
*
*  Condi��es de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Retorno por refer�ncia
*     ppTabuleiro  - retorna NULL
*
*  Assertivas de entrada
*     - ppTabuleiro � NULL ou aponta para uma Tabuleiro v�lida.
*
*  Assertivas de saida
*     - A inst�ncia apontada por ppTabuleiro � liberada da mem�ria.
*     - ppTabuleiro aponta para NULL
*
***********************************************************************/
   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro *ppTabuleiro);

/***********************************************************************
*
*  Fun��o: TAB Ir casa
*
*  Descri��o
*     Muda corrente baseado no nome da casa.
*
*  Par�metros
*     pTabuleiro - Tabuleiro que ser� usada como base.
*     nomeCasa - Nome de uma casa no tabuleiro da partida.
*
*  Condi��es de retorno
*     TAB_CondRetOK
*     TAB_CondRetNaoEhCasa
*     TAB_CondRetTabuleiroNaoExiste
*
*  Assertivas de entrada
*     - pTabuleiro aponta para um Tabuleiro v�lido.
*
*  Assertivas de saida
*     - O corrente de pTabuleiro aponta para a casa com o nome igual ao passado
*       por par�metro, ou permanece o mesmo, caso n�o exista casa com este nome.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrCasa(TAB_tppTabuleiro pTabuleiro, char *nome);


/***********************************************************************
*
*  Fun��o: TAB Percorrer casas
*
*  Descri��o
*     Percorre todas as casas aplicando opera��es definidas pelo m�dulo cliente
*     atrav�s de uma fun��o passada por ponteiro.
*
*  Par�metros
*     pTabuleiro - Tabuleiro que ser� usada como base.
*     fazerNaCasa - Ponteiro para fun��o que ser� aplicada em cada casa do tabuleiro.
*
*  Condi��es de retorno
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
*  Assertivas de entrada
*     - pTabuleiro aponta para um Tabuleiro v�lido.
*
*  Assertivas de saida
*     - Fun��o ter� sido aplicada em todas as casas do tabuleiro.
*
***********************************************************************/
   TAB_tpCondRet TAB_PercorrerCasas(TAB_tppTabuleiro pTabuleiro, int (*fazerNaCasa)(TAB_tppTabuleiro pTabuleiro, char *nome));

/***********************************************************************
*
*  Fun��o: TAB Nome da casa
*
*  Descri��o
*     Recebe as coordenadas e retorna o nome da casa nesta coordenada.
*
*  Par�metros
*     x, y   - Coordenada da casa.
*     pNome  - Refer�ncia para retornar o nome da casa
*
*  Condi��es de retorno
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     pNome  - Nome da casa nesta coordenada.
*
*  Assertivas de entrada
*     - x est� entre zero e a largura-1.
*     - y est� entre zero e a altura-1.
*     - pNome � um ponteiro v�lido.
*
*  Assertivas de saida
*     - pNome � uma string de 2 caracteres com o nome da casa.
*
***********************************************************************/
   TAB_tpCondRet TAB_NomeDaCasa(int x, int y, char **pNome);

/***************************************************************************
*
*  Fun��o: TAB Ir para
*  
*  Descri��o da fun��o
*  Muda a casa corrente do tabuleiro para a casa na dire��o apontada
*  
*  Par�metros
*     pTabuleiro - ponteiro para o tabuleiro que ser� manipulado.
*     direcao    - representa a dire��o que o n� corrente navegar�.
*
*  Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetNaoEhCasa
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do tabuleiro.
*     - Existe casa com o nome passado por par�metro.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do tabuleiro.
*     - Casa corrente � a casa com o nome passado por par�metro.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrPara(TAB_tppTabuleiro pTabuleiro, DIR_tpDirecao);


#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
