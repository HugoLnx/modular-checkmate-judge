#if ! defined( CHECKMATE_JUDGE_ )
#define CHECKMATE_JUDGE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              CHECKMATE_JUDGE.H
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
 
#if defined( CHECKMATE_JUDGE_OWN )
   #define CHECKMATE_JUDGE_EXT
#else
   #define CHECKMATE_JUDGE_EXT extern
#endif

#include "partida.h"

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         JUD_CondRetOK = 0 ,
               /* Executou correto */

         JUD_CondRetNaoCriouOrigem = 1 ,
               /* N�o criou n� origem */

         JUD_CondRetNaoEhNo = 2 ,
               /* N�o � n� na dire��o desejada */

         JUD_CondRetMatrizNaoExiste = 3 ,
               /* Matriz n�o existe */

         JUD_CondRetNaoTemCorrente = 4 ,
               /* Matriz est� vazia */

         JUD_CondRetFaltouMemoria = 5 ,
               /* Faltou mem�ria ao alocar dados */
         JUD_CondRetPecaNaoEncontrada = 6

   } JUD_tpCondRet ;

   JUD_tpCondRet JUD_EhCheckmate(PAR_tppPartida pPartida, int *pResposta);

#undef CHECKMATE_JUDGE_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
