#if ! defined( CHECKMATE_JUDGE_ )
#define CHECKMATE_JUDGE_
/***************************************************************************
*
*  Módulo de definição: JUD
*
*  Arquivo gerado:              checkmate_judge.h
*  Letras identificadoras:      JUD
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Verificações que envolvem locomoção de peças
*
*  Descrição do módulo
*     Encapsula a lógica responsável por verificar se uma partida resulta em um checkmate
*     ou não.
*
***************************************************************************/
 
#if defined( CHECKMATE_JUDGE_OWN )
   #define CHECKMATE_JUDGE_EXT
#else
   #define CHECKMATE_JUDGE_EXT extern
#endif

#include "partida.h"


/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  Tipo de dados: JUD Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/

   typedef enum {

         JUD_CondRetOK = 0,
               /* Executou correto */

         JUD_CondRetNaoFoiPossivelVerificar = 1,
               /* Não criou nó origem */

         JUD_CondRetFaltouMemoria = 2,
               /* Faltou memória ao alocar dados */

   } JUD_tpCondRet;

   
/***********************************************************************/


/***********************************************************************
*
*  Função: JUD Eh checkmate
*
*  Descrição
*     Verifica se a partida resultará em checkmate.
*
*  Parâmetros
*     pPartida   - Partida que será avaliada.
*     pResposta  - Referência que será utilizada para retornar a resposta.
*
*  Condições de retorno
*     JUD_CondRetOK
*     JUD_CondRetNaoFoiPossivelVerificar
*     JUD_CondRetFaltouMemoria
*
*  Retorno por referência
*     pResposta   - Retornará 1 caso seja checkmate e 0 caso não seja.
*
*  Hipóteses
*     - O movimento de peças que não sejam o rei não devem ser levadas
*       em conta para a verificação do checkmate.
*     - Possíveis movimentos de uma peça aliada para bloquear ou eliminar
*       a inimiga que esteja ameaçando o rei não devem ser levados em conta.
*
*  Assertivas de entrada
*     - partida possui rei.
*
*  Assertivas de saida
*     - retorno será 0 caso o rei não esteja em checkmate e 1 caso esteja.
*
***********************************************************************/
   JUD_tpCondRet JUD_EhCheckmate(PAR_tppPartida pPartida, int *pResposta);

#undef CHECKMATE_JUDGE_EXT

/********** Fim do módulo de definição: Módulo Checkmate Judge **********/

#else
#endif
