#if ! defined( MODELO_PECA_ )
#define MODELO_PECA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              MODELO_PECA.H
*  Letras identificadoras:      PEC
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

#if defined( MODELO_PECA_OWN )
#define MODELO_PECA_EXT
#else
#define MODELO_PECA_EXT extern
#endif

#include "lista.h"


typedef enum {
   ANDA = 0,
   VOA = 1
} MPEC_tpTipoMovimento;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

   MPEC_CondRetOK,
   /* Executou correto */
      
   MPEC_CondRetFaltouMemoria,
   /* Faltou mem�ria ao alocar dados */

   MPEC_CondRetNaoAlterou,
   /* N�o foi possivel alterar a peca */

   MPEC_CondRetModeloNaoExiste
   /* Pe�a n�o existe */

} MPEC_tpCondRet ;


typedef struct MPEC_stModeloPeca* MPEC_tppModeloPeca;

MPEC_tpCondRet MPEC_CriarModeloPeca(MPEC_tppModeloPeca *ppModelo, char* nome, LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);
MPEC_tpCondRet MPEC_DestruirModeloPeca(MPEC_tppModeloPeca *ppModelo);
MPEC_tpCondRet MPEC_AlterarModeloPeca(MPEC_tppModeloPeca ppModelo, char *novoNome, LIS_tppLista pPassos, MPEC_tpTipoMovimento novoTipoMovimento);
#undef MODELO_PECA_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
