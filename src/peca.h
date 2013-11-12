#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
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

#if defined( PECA_OWN )
#define PECA_EXT
#else
#define PECA_EXT extern
#endif

#include "lista.h"
#include "modelo_peca.h"

typedef enum {
   ALIADA = 0,
   INIMIGA = 1
} PEC_tpTimePeca;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

   PEC_CondRetOK,
   /* Executou correto */
      
   PEC_CondRetFaltouMemoria,
   /* Faltou memória ao alocar dados */

   PEC_CondRetNaoAlterou,
   /* Não foi possivel alterar a peca */

   PEC_CondRetPecaNaoExiste
   /* Peça não existe */

} PEC_tpCondRet;

typedef struct PEC_stPeca* PEC_tppPeca;

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, MPEC_tppModeloPeca pModelo, PEC_tpTimePeca time);
PEC_tpCondRet PEC_DestruirPeca(PEC_tppPeca *ppPeca);

PEC_tpCondRet PEC_CriarRei(PEC_tppPeca *ppPeca);
PEC_tpCondRet PEC_DestruirRei(PEC_tppPeca *ppPeca);

PEC_tpCondRet PEC_AlterarModeloPeca(PEC_tppPeca ppPeca, MPEC_tppModeloPeca pNovoModelo);

PEC_tpCondRet PEC_EhORei(PEC_tppPeca pPecaParm, int *ehRei);
PEC_tpCondRet PEC_ObterModelo(PEC_tppPeca pPecaParm, MPEC_tppModeloPeca *ppModelo);
PEC_tpCondRet PEC_ObterTime(PEC_tppPeca pPecaParm, PEC_tpTimePeca *pTime);

PEC_tpCondRet PEC_SalvarPeca(PEC_tppPeca ppPeca,FILE* pFile);
#undef PECA_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
