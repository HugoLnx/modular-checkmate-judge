#if ! defined( MODELO_PECA_ )
#define MODELO_PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MODELO_PECA.H
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
   /* Faltou memória ao alocar dados */

   MPEC_CondRetNaoAlterou,
   /* Não foi possivel alterar a peca */

   MPEC_CondRetModeloNaoExiste
   /* Peça não existe */

} MPEC_tpCondRet ;


typedef struct MPEC_stModeloPeca* MPEC_tppModeloPeca;

MPEC_tpCondRet MPEC_CriarModeloPeca(MPEC_tppModeloPeca *ppModelo, char* nome, LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);
MPEC_tpCondRet MPEC_DestruirModeloPeca(MPEC_tppModeloPeca *ppModelo);
MPEC_tpCondRet MPEC_AlterarModeloPeca(MPEC_tppModeloPeca ppModelo, char *novoNome, LIS_tppLista pPassos, MPEC_tpTipoMovimento novoTipoMovimento);
#undef MODELO_PECA_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
