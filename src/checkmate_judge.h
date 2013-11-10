#if ! defined( CHECKMATE_JUDGE_ )
#define CHECKMATE_JUDGE_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              CHECKMATE_JUDGE.H
*  Letras identificadoras:      TAB
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*       1.00   hg e nf  15/09/2013 Adaptação do módulo para manipular matrizes
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar matrizes.
*     A matriz possui uma cabeça que contém uma referência para a raíz da
*     matriz e outra para um nó corrente da matriz.
*     O modulo permite a manipulação de múltiplas matrizes, porém as funções
*     só manipulam uma matriz de cada vez.
*     Ao iniciar a execução do programa não existe matriz.
*     A matriz poderá estar vazia. Neste caso a origem e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a matriz estiver vazia.
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
               /* Não criou nó origem */

         JUD_CondRetNaoEhNo = 2 ,
               /* Não é nó na direção desejada */

         JUD_CondRetMatrizNaoExiste = 3 ,
               /* Matriz não existe */

         JUD_CondRetNaoTemCorrente = 4 ,
               /* Matriz está vazia */

         JUD_CondRetFaltouMemoria = 5 ,
               /* Faltou memória ao alocar dados */
         JUD_CondRetPecaNaoEncontrada = 6

   } JUD_tpCondRet ;

   JUD_tpCondRet JUD_EhCheckmate(PAR_tppPartida pPartida, int *pResposta);

#undef CHECKMATE_JUDGE_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
