#if ! defined( CHECKMATE_JUDGE_ )
#define CHECKMATE_JUDGE_
/***************************************************************************
*
*  M�dulo de defini��o: JUD
*
*  Arquivo gerado:              checkmate_judge.h
*  Letras identificadoras:      JUD
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Verifica��es que envolvem locomo��o de pe�as
*
*  Descri��o do m�dulo
*     Encapsula a l�gica respons�vel por verificar se uma partida resulta em um checkmate
*     ou n�o.
*
***************************************************************************/
 
#if defined( CHECKMATE_JUDGE_OWN )
   #define CHECKMATE_JUDGE_EXT
#else
   #define CHECKMATE_JUDGE_EXT extern
#endif

#include "partida.h"


/***** Declara��es exportadas pelo m�dulo *****/

/***********************************************************************
*
*  Tipo de dados: JUD Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/

   typedef enum {

         JUD_CondRetOK = 0,
               /* Executou correto */

         JUD_CondRetNaoFoiPossivelVerificar = 1,
               /* N�o criou n� origem */

         JUD_CondRetFaltouMemoria = 2,
               /* Faltou mem�ria ao alocar dados */

   } JUD_tpCondRet;

   
/***********************************************************************/


/***********************************************************************
*
*  Fun��o: JUD Eh checkmate
*
*  Descri��o
*     Verifica se a partida resultar� em checkmate.
*
*  Par�metros
*     pPartida   - Partida que ser� avaliada.
*     pResposta  - Refer�ncia que ser� utilizada para retornar a resposta.
*
*  Condi��es de retorno
*     JUD_CondRetOK
*     JUD_CondRetNaoFoiPossivelVerificar
*     JUD_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     pResposta   - Retornar� 1 caso seja checkmate e 0 caso n�o seja.
*
*  Hip�teses
*     - O movimento de pe�as que n�o sejam o rei n�o devem ser levadas
*       em conta para a verifica��o do checkmate.
*     - Poss�veis movimentos de uma pe�a aliada para bloquear ou eliminar
*       a inimiga que esteja amea�ando o rei n�o devem ser levados em conta.
*
*  Assertivas de entrada
*     - partida possui rei.
*
*  Assertivas de saida
*     - retorno ser� 0 caso o rei n�o esteja em checkmate e 1 caso esteja.
*
***********************************************************************/
   JUD_tpCondRet JUD_EhCheckmate(PAR_tppPartida pPartida, int *pResposta);

#undef CHECKMATE_JUDGE_EXT

/********** Fim do m�dulo de defini��o: M�dulo Checkmate Judge **********/

#else
#endif
