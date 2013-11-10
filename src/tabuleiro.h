#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              TABULEIRO.H
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
 
#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

#define LARGURA        8
#define ALTURA         8

#include "lista.h"
#include "direcao.h"

typedef struct TAB_stTabuleiro* TAB_tppTabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK = 0,
               /* Executou correto */

         TAB_CondRetNaoEhNo = 2,
               /* Não é nó na direção desejada */

         TAB_CondRetTabuleiroNaoExiste = 3,
               /* Tabuleiro não existe */

         TAB_CondRetFaltouMemoria = 5,
               /* Faltou memória ao alocar dados */

         TAB_CondRetPecaNaoEncontrada = 6

   } TAB_tpCondRet;

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro, void (*destruirValor)(void *pValor));

   TAB_tpCondRet TAB_ObterValor(TAB_tppTabuleiro pTabuleiro, void **ppValor);

   TAB_tpCondRet TAB_AlterarValor(TAB_tppTabuleiro pTabuleiro, void *pValor);

/***********************************************************************
*
*  $FC Função: TAB Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente não exista.
*
*  $EP Parâmetros
*     $P ppMatriz - é o ponteiro para a matriz que será destruida.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
***********************************************************************/
   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro *ppTabuleiro);

   TAB_tpCondRet TAB_IrCasa(TAB_tppTabuleiro pTabuleiro, char *nome);

   TAB_tpCondRet TAB_PercorrerCasas(TAB_tppTabuleiro pTabuleiro, int (*fazerNaCasa)(char *nome, void *pValor));

/***************************************************************************
*
*  $FC Função: MAT Ir para nó genérico.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção apontada
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*     direcao - representa a direção que o nó corrente navegará.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
*  ****/
   TAB_tpCondRet TAB_IrPara(TAB_tppTabuleiro pTabuleiro, DIR_tpDirecao);


#undef TABULEIRO_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
