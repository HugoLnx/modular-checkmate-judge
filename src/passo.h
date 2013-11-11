#if !defined(PASSO_)
#define PASSO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              PASSO.H
*  Letras identificadoras:      PAS
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
               /* Não criou nó origem */

         PAS_CondRetNaoEhNo = 2 ,
               /* Não é nó na direção desejada */

         PAS_CondRetMatrizNaoExiste = 3 ,
               /* Matriz não existe */

         PAS_CondRetNaoTemCorrente = 4 ,
               /* Matriz está vazia */

         PAS_CondRetFaltouMemoria = 5 ,
               /* Faltou memória ao alocar dados */
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

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
