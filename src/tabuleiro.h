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

#include "lista.h"

typedef struct stMatriz TAB_tpMatriz ;

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

         TAB_CondRetFaltouMemoria = 5
               /* Faltou mem�ria ao alocar dados */

   } TAB_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: TAB Criar matriz
*
*  $ED Descri��o da fun��o
*     Cria uma nova matriz vazia.
*     Caso j� exista uma matriz, esta ser� destru�da.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet TAB_CriarMatriz( TAB_tpMatriz ** ppMatriz ) ;



/***********************************************************************
*
*  $FC Fun��o: TAB Inicializar a matriz
*
*  $EP Par�metros
*     $P pMatriz - matriz que ser� inicializada.
*                    Este par�metro � passado por refer�ncia.
*     $P Linhas - quantidade de linhas que a matriz ter�.
*     $P Colunas - quantidade de colunas que a matriz ter�.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet TAB_InicializarMatriz( TAB_tpMatriz * pMatriz , int Linhas , int Colunas ) ;



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


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� ao norte.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o norte
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
***********************************************************************/
   TAB_tpCondRet TAB_IrNoNorte( TAB_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� ao sul.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o sul
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
***********************************************************************/
   TAB_tpCondRet TAB_IrNoSul( TAB_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� � este.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o este.
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
***********************************************************************/
   TAB_tpCondRet TAB_IrNoEste( TAB_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� � oeste.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o oeste
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
***********************************************************************/
   TAB_tpCondRet TAB_IrNoOeste( TAB_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� � nordeste.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o nordeste
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
***********************************************************************/
   TAB_tpCondRet TAB_IrNoNordeste( TAB_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� � sudeste.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o sudeste
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
***********************************************************************/
   TAB_tpCondRet TAB_IrNoSudeste( TAB_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� � sudoeste.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o sudoeste
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
***********************************************************************/
   TAB_tpCondRet TAB_IrNoSudoeste( TAB_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Fun��o: TAB Ir para n� � noroeste.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o noroeste
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*  
***********************************************************************/
   TAB_tpCondRet TAB_IrNoNoroeste( TAB_tpMatriz * pMatriz ) ;



/***********************************************************************
*
*  $FC Fun��o: TAB Obter valor corrente
*
*  $EP Par�metros
*     $P ValorParm - � o par�metro que receber� o valor contido no n�.
*                    Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorCorr( TAB_tpMatriz * pMatriz , LIS_tppLista * ValorParm ) ;

/***********************************************************************
*
*  $FC Fun��o: TAB Atribuir valor corrente
*
*  $EP Par�metros
*     $P ValorParm - o valor que ser� atribuido ao n� corrente.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*
***********************************************************************/
   
   TAB_tpCondRet TAB_AtribuirValorCorr( TAB_tpMatriz * pMatriz , LIS_tppLista ValorParm ) ;

#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
