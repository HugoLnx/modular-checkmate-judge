#if !defined(PASSO_)
#define PASSO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              PASSO.H
*  Letras identificadoras:      PAS
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
 
#if defined( PASSO_OWN )
   #define PASSO_EXT
#else
   #define PASSO_EXT extern
#endif

#include "lista.h"
#include "direcao.h"

typedef struct PAS_stPasso* PAS_tppPasso;

/***********************************************************************
*
*  $TC Tipo de dados: PAS Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PAS_CondRetOK = 0 ,
               /* Executou correto */

         PAS_CondRetNaoCriouOrigem = 1 ,
               /* N�o criou n� origem */

         PAS_CondRetNaoEhNo = 2 ,
               /* N�o � n� na dire��o desejada */

         PAS_CondRetMatrizNaoExiste = 3 ,
               /* Matriz n�o existe */

         PAS_CondRetNaoTemCorrente = 4 ,
               /* Matriz est� vazia */

         PAS_CondRetFaltouMemoria = 5 ,
               /* Faltou mem�ria ao alocar dados */
         PAS_CondRetPecaNaoEncontrada = 6

   } PAS_tpCondRet;

   PAS_tpCondRet PAS_CriarPasso(PAS_tppPasso *ppPasso, DIR_tpDirecao direcao, int quantidade);
   PAS_tpCondRet PAS_DestruirPasso(PAS_tppPasso *ppPasso);
   PAS_tpCondRet PAS_CompararPassos(PAS_tppPasso pPasso1, PAS_tppPasso pPasso2, int *pResposta);
   PAS_tpCondRet PAS_Percorrer(PAS_tppPasso pPasso, int (*FazerNaDirecao)(DIR_tpDirecao direcao));
   PAS_tpCondRet PAS_PercorrerPassos(LIS_tppLista pPassos, int (*fazerNaDirecao)(DIR_tpDirecao direcao));
   PAS_tpCondRet PAS_Salvar(LIS_tppLista ppPassos, FILE* pFile);

   PAS_tpCondRet PAS_ObterQuantidade(PAS_tppPasso pPassoParm, int *pQuantidade);
   PAS_tpCondRet PAS_ObterDirecao(PAS_tppPasso pPassoParm, DIR_tpDirecao *pDirecao);
   PAS_tpCondRet PAS_EhInfinito(PAS_tppPasso pPassoParm, int *pEhInfinito);

   PAS_tpCondRet PAS_Salvar(LIS_tppLista ppPassos, FILE* pFile);

#undef PASSO_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
