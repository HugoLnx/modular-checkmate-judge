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
#define TOTAL_DIRECOES 8

#include "lista.h"

typedef struct stMatriz TAB_tpMatriz;

typedef enum {
   ANDA = 0,
   VOA = 1
} TAB_tpTipoMovimento;


typedef enum {
   ALIADA = 0,
   INIMIGA = 1
} TAB_tpTimePeca;

typedef enum {
   NORTE    = 0,

   NORDESTE = 1,

   ESTE     = 2,

   SUDESTE  = 3,  

   SUL      = 4,
   
   SUDOESTE = 5,

   OESTE    = 6,

   NOROESTE = 7
} TAB_tpDirecao;

typedef struct TAB_stPasso
{
   TAB_tpDirecao direcao;
   int quantidade;
} TAB_tpPasso;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK = 0 ,
               /* Executou correto */

         TAB_CondRetNaoCriouOrigem = 1 ,
               /* N�o criou n� origem */

         TAB_CondRetNaoEhNo = 2 ,
               /* N�o � n� na dire��o desejada */

         TAB_CondRetMatrizNaoExiste = 3 ,
               /* Matriz n�o existe */

         TAB_CondRetNaoTemCorrente = 4 ,
               /* Matriz est� vazia */

         TAB_CondRetFaltouMemoria = 5 ,
               /* Faltou mem�ria ao alocar dados */
         TAB_CondRetPecaNaoEncontrada = 6

   } TAB_tpCondRet ;


   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpMatriz **ppMatriz);

   TAB_tpCondRet TAB_AlgumaPegadaInimiga(TAB_tpMatriz *pTabuleiro, int *pResposta);

   TAB_tpCondRet TAB_InserirRei(TAB_tpMatriz *pTabuleiro);
   
   TAB_tpCondRet TAB_RemoverRei(TAB_tpMatriz *pTabuleiro);

   TAB_tpCondRet TAB_IrCasaRei(TAB_tpMatriz *pTabuleiro);
   
   TAB_tpCondRet TAB_EhCheckmate(TAB_tpMatriz *pTabuleiro, int *pResposta);

   TAB_tpCondRet TAB_CriarPegadas(TAB_tpMatriz *pTabuleiro);

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
*     TAB_CondRetMatrizNaoExiste
*
***********************************************************************/
   TAB_tpCondRet TAB_DestruirMatriz( TAB_tpMatriz ** ppMatriz ) ;


   TAB_tpCondRet TAB_IrCasa(TAB_tpMatriz *pTabuleiro, char *nomeCasa);

   TAB_tpCondRet TAB_CriarPeca(TAB_tpMatriz *pTabuleiro, char *nome,
      LIS_tppLista pPassos, TAB_tpTipoMovimento tipoMovimento);

   TAB_tpCondRet TAB_AlterarPeca(TAB_tpMatriz *pTabuleiro, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, TAB_tpTipoMovimento novoTipoMovimento);

   TAB_tpCondRet TAB_InserirPeca(TAB_tpMatriz *pTabuleiro, char *nome, TAB_tpTimePeca time);

   TAB_tpCondRet TAB_CopiarTabuleiro(TAB_tpMatriz *pTabuleiro, TAB_tpMatriz **ppCopia);

   TAB_tpCondRet TAB_RemoverPeca(TAB_tpMatriz *pTabuleiro);

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
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
*  ****/
   TAB_tpCondRet TAB_IrPara(TAB_tpMatriz *pTabuleiro, TAB_tpDirecao);



#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
