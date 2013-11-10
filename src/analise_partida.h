#if ! defined( ANALISE_PARTIDA_ )
#define ANALISE_PARTIDA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              ANALISE_PARTIDA.H
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
 
#if defined( ANALISE_PARTIDA_OWN )
   #define ANALISE_PARTIDA_EXT
#else
   #define ANALISE_PARTIDA_EXT extern
#endif

#include "lista.h"
#include "direcao.h"
#include "tabuleiro.h"
#include "peca.h"
#include "modelo_peca.h"
#include "partida.h"

typedef struct APAR_stAnalise* APAR_tppAnalise;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         APAR_CondRetOK = 0 ,
               /* Executou correto */

         APAR_CondRetNaoCriouOrigem = 1 ,
               /* N�o criou n� origem */

         APAR_CondRetNaoEhNo = 2 ,
               /* N�o � n� na dire��o desejada */

         APAR_CondRetMatrizNaoExiste = 3 ,
               /* Matriz n�o existe */

         APAR_CondRetNaoTemCorrente = 4 ,
               /* Matriz est� vazia */

         APAR_CondRetFaltouMemoria = 5 ,
               /* Faltou mem�ria ao alocar dados */
         APAR_CondRetPecaNaoEncontrada = 6

   } APAR_tpCondRet ;

   
   APAR_tpCondRet APAR_CriarAnalise(APAR_tppAnalise *ppAnalise, PAR_tppPartida pPartida);

   APAR_tpCondRet APAR_AlgumaPegadaInimiga(APAR_tppAnalise pAnalise, int *pResposta);

   APAR_tpCondRet APAR_IrCasaRei(APAR_tppAnalise pAnalise);

/***********************************************************************
*
*  $FC Fun��o: TAB Destruir matriz
*
*  $ED Descri��o da fun��o
*     Destr�i o corpo e a cabe�a da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente n�o exista.
*
*  $EP Par�metros
*     $P ppAnalise - � o ponteiro para a matriz que ser� destruida.
*                    Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*     APAR_CondRetOK
*     APAR_CondRetMatrizNaoExiste
*
***********************************************************************/
   APAR_tpCondRet APAR_DestruirAnalise(APAR_tppAnalise *ppAnalise);

   APAR_tpCondRet APAR_IrCasa(APAR_tppAnalise pAnalise, char *nomeCasa);
   
   APAR_tpCondRet APAR_IrPara(APAR_tppAnalise pAnalise , DIR_tpDirecao direcao);

   APAR_tpCondRet APAR_CriarPeca(APAR_tppAnalise pAnalise, char *nome,
      LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);
   
   APAR_tpCondRet APAR_AlterarPeca(APAR_tppAnalise pAnalise, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, MPEC_tpTipoMovimento novoTipoMovimento);
   
   APAR_tpCondRet APAR_InserirPeca(APAR_tppAnalise pAnalise, char *nome, PEC_tpTimePeca time);
   
   APAR_tpCondRet APAR_RemoverPeca(APAR_tppAnalise pAnalise);



#undef ANALISE_PARTIDA_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
