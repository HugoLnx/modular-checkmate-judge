#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar matrizes.
*     A matriz possui uma cabe�a que cont�m uma refer�ncia para a ra�z da
*     matriz e outra para um n� corrente da matriz.
*     O modulo permite a manipula��o de m�ltiplas matrizes, por�m as fun��es
*     s� manipulam uma matriz de cada vez.
*     Ao iniciar a execu��o do programa n�o existe matriz.
*     A matriz poder� estar vazia. Neste caso a origem e o n� corrente
*     ser�o nulos, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se a matriz estiver vazia.
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

typedef struct TAB_stTabuleiro* TAB_tppTabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK = 0,
               /* Executou correto */

         TAB_CondRetNaoEhNo = 2,
               /* N�o � n� na dire��o desejada */

         TAB_CondRetTabuleiroNaoExiste = 3,
               /* Tabuleiro n�o existe */

         TAB_CondRetFaltouMemoria = 5,
               /* Faltou mem�ria ao alocar dados */

         TAB_CondRetPecaNaoEncontrada = 6

   } TAB_tpCondRet;

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro, void (*destruirValor)(void *pValor));

   TAB_tpCondRet TAB_ObterValor(TAB_tppTabuleiro pTabuleiro, void **ppValor);

   TAB_tpCondRet TAB_AlterarValor(TAB_tppTabuleiro pTabuleiro, void *pValor);

/***********************************************************************
*
*  $FC Fun��o: TAB Destruir matriz
*
*  $ED Descri��o da fun��o
*     Destr�i o corpo e a cabe�a da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente n�o exista.
*
*  $EP Par�metros
*     $P ppMatriz - � o ponteiro para a matriz que ser� destruida.
*                    Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
***********************************************************************/
   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro *ppTabuleiro);

   TAB_tpCondRet TAB_IrCasa(TAB_tppTabuleiro pTabuleiro, char *nome);

   TAB_tpCondRet TAB_PercorrerCasas(TAB_tppTabuleiro pTabuleiro, int (*fazerNaCasa)(char *nome, void *pValor));

/***************************************************************************
*
*  $FC Fun��o: MAT Ir para n� gen�rico.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o apontada
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*     direcao - representa a dire��o que o n� corrente navegar�.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
*  ****/
   TAB_tpCondRet TAB_IrPara(TAB_tppTabuleiro pTabuleiro, DIR_tpDirecao);


#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
