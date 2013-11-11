#if ! defined( ANALISE_PARTIDA_ )
#define ANALISE_PARTIDA_

/***************************************************************************
*
*  M�dulo de defini��o: APAR  Analise Partida
*
*  Arquivo gerado:              analise_partida.h
*  Letras identificadoras:      APAR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Marca��o sobre as casas que as pe�as podem chegar
*
*  Descri��o do m�dulo
*     Permite obter uma analise detalhada sobre uma partida, em rela��o �s casas
*     que as pe�as podem chegar, iinclusive as casas que as pe�as podem chegar.
*     O m�dulo utiliza a estrutura stPegada para marcar as casas que podem ser
*     alcan�adas por outras pe�as.
*     Uma vez criada sua estrutura n�o pode ser alterada pelo cliente.
*
***************************************************************************/
 
#if defined( ANALISE_PARTIDA_OWN )
   #define ANALISE_PARTIDA_EXT
#else
   #define ANALISE_PARTIDA_EXT extern
#endif

#include "direcao.h"
#include "partida.h"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma Analise de Partida */
typedef struct APAR_stAnalise* APAR_tppAnalise;

/***********************************************************************
*
*  Tipo de dados: <abreviacao> <descricao-do-enum>
*
*
*  Descri��o do tipo
*     <descricao do enum>
*
***********************************************************************/

   typedef enum {

         APAR_CondRetOK = 0,
               /* Executou correto */

         APAR_CondRetNaoEhCasa = 1,
               /* N�o � casa na dire��o ou com o nome desejado */

         APAR_CondRetAnaliseNaoExiste = 2,
               /* Analise n�o existe */

         APAR_CondRetFaltouMemoria = 3
               /* Faltou mem�ria ao alocar dados */

   } APAR_tpCondRet ;

/******************************************/

/***********************************************************************
*
*  Fun��o: APAR Criar analise
*
*  Descri��o
*     Cria uma inst�ncia da analise.
*
*  Par�metros
*     ppAnalise - Refer�ncia que ser� usada para retornar a inst�ncia
*     pPartida  - Partida que ser� usada como base na an�lise.
*
*  Condi��es de retorno
*     APAR_CondRetOK
*     APAR_CondRetNaoEhCasa
*     APAR_CondRetFaltouMemoria
*
*  Retorno por refer�ncia
*     ppAnalise - Nova instancia de Analise.
*
*  Assertivas de entrada
*     - ppAnalise � um ponteiro v�lido
*     - Valem as assertivas estruturais da Partida para pPartida.
*
*  Assertivas de saida
*     - A estrutura apontada por pPartida n�o foi alterada.
*     - ppAnalise possui uma inst�ncia v�lida de Analise Partida.
*
***********************************************************************/
   APAR_tpCondRet APAR_CriarAnalise(APAR_tppAnalise *ppAnalise, PAR_tppPartida pPartida);


/***********************************************************************
*
*  Fun��o: APAR Alguma pegada inimiga
*
*  Descri��o
*     Verifica se alguma pe�a inimiga pode mover para
*     a casa corrente.
*
*  Par�metros
*     pAnalise   - PartidaAnalise que ser� usada como base.
*     pResposta  - Referencia usada para retornar a resposta da fun��o.
*
*  Condi��es de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*
*  Retorno por refer�ncia
*     pResposta   - Ser� 1 caso haja alguma pe�a inimiga que possa se mover
*                   para a casa corrente, e 0 caso contr�rio.
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise v�lida.
*     - pResposta � um ponteiro v�lido.
*
*  Assertivas de saida
*     - A inst�ncia referenciada por pAnalise n�o foi alterada.
*     - pResposta aponta para 0 ou 1.
*
***********************************************************************/
   APAR_tpCondRet APAR_AlgumaPegadaInimiga(APAR_tppAnalise pAnalise, int *pResposta);


/***********************************************************************
*
*  Fun��o: APAR Rei pode mover para corrente
*
*  Descri��o
*     Verifica se o rei pode mover para a casa corrente.
*
*  Par�metros
*     pAnalise   - PartidaAnalise que ser� usada como base.
*     pResposta  - Referencia usada para retornar a resposta da fun��o.
*
*  Condi��es de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*
*  Retorno por refer�ncia
*     pResposta   - Ser� 1 caso o rei possa se mover
*                   para a casa corrente, e 0 caso contr�rio.
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise v�lida.
*     - pResposta � um ponteiro v�lido.
*
*  Assertivas de saida
*     - A inst�ncia referenciada por pAnalise n�o foi alterada.
*     - pResposta aponta para 0 ou 1.
*
***********************************************************************/
   APAR_tpCondRet APAR_ReiPodeMoverParaCorrente(APAR_tppAnalise pAnalise, int *pResposta);


/***********************************************************************
*
*  Fun��o: APAR Ir casa rei
*
*  Descri��o
*     Muda corrente para apontar para a casa onde se encontra o rei.
*
*  Par�metros
*     pAnalise       - PartidaAnalise que ser� usada como base.
*
*  Condi��es de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*     APAR_CondRetNaoEhCasa
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise v�lida.
*
*  Assertivas de saida
*     - O corrente de pAnalise aponta para a casa onde se encontra o rei.
*
***********************************************************************/
   APAR_tpCondRet APAR_IrCasaRei(APAR_tppAnalise pAnalise);

/***********************************************************************
*
*  Fun��o: APAR Destruir analise
*
*  Descri��o da fun��o
*     Destroi a instancia de an�lise, liberando seu espa�o da mem�ria.
*
*  Par�metros
*     ppAnalise - � o ponteiro para a an�lise que ser� destruida.
*                 Este par�metro � passado por refer�ncia.
*
*  Condi��es de retorno
*     APAR_CondRetOK
*     APAR_CondRetAnaliseNaoExiste
*
*  Retorno por refer�ncia
*     ppAnalise - retorno � NULL
*
*  Assertivas de entrada
*     - ppAnalise � NULL ou aponta para uma PartidaAnalise v�lida.
*
*  Assertivas de saida
*     - A instancia apontada por ppAnalise � liberada da mem�ria.
*     - ppAnalise aponta para NULL
*
***********************************************************************/
   APAR_tpCondRet APAR_DestruirAnalise(APAR_tppAnalise *ppAnalise);


/***********************************************************************
*
*  Fun��o: APAR Ir casa
*
*  Descri��o
*     Muda corrente baseado no nome da casa.
*
*  Par�metros
*     pAnalise - PartidaAnalise que ser� usada como base.
*     nomeCasa - Nome de uma casa no tabuleiro da partida.
*
*  Condi��es de retorno
*     APAR_CondRetOK
*     APAR_CondRetNaoEhCasa
*     APAR_CondRetAnaliseNaoExiste
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise v�lida.
*
*  Assertivas de saida
*     - O corrente de pAnalise aponta para a casa com o nome igual ao passado
*       por par�metro, ou permanece o mesmo, caso n�o exista casa com este nome.
*
***********************************************************************/
   APAR_tpCondRet APAR_IrCasa(APAR_tppAnalise pAnalise, char *nomeCasa);


/***********************************************************************
*
*  Fun��o: APAR Ir Para
*
*  Descri��o
*     Muda corrente navegando para casa que est� na dire��o passada por
*     par�metro, tendo como base o corrente atual.
*
*  Par�metros
*     pAnalise - PartidaAnalise que ser� usada como base.
*     direcao  - Dire��o que ser� seguida.
*
*  Condi��es de retorno
*     APAR_CondRetOK
*     APAR_CondRetNaoEhCasa
*     APAR_CondRetAnaliseNaoExiste
*
*  Assertivas de entrada
*     - pAnalise aponta para uma PartidaAnalise v�lida.
*
*  Assertivas de saida
*     - O corrente de pAnalise aponta para a casa na dire��o passada
*       por par�metro, ou permanece o mesmo caso n�o exista casa nesta dire��o.
*
***********************************************************************/
   APAR_tpCondRet APAR_IrPara(APAR_tppAnalise pAnalise , DIR_tpDirecao direcao);

#undef ANALISE_PARTIDA_EXT

/********** Fim do m�dulo de defini��o: APAR Analise partida **********/

#else
#endif

