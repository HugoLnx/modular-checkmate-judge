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
               /* Não criou nó origem */

         TAB_CondRetNaoEhNo = 2 ,
               /* Não é nó na direção desejada */

         TAB_CondRetMatrizNaoExiste = 3 ,
               /* Matriz não existe */

         TAB_CondRetNaoTemCorrente = 4 ,
               /* Matriz está vazia */

         TAB_CondRetFaltouMemoria = 5
               /* Faltou memória ao alocar dados */

   } TAB_tpCondRet ;


/***********************************************************************
*
*  $FC Função: TAB Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet TAB_CriarMatriz( TAB_tpMatriz ** ppMatriz ) ;



/***********************************************************************
*
*  $FC Função: TAB Inicializar a matriz
*
*  $EP Parâmetros
*     $P pMatriz - matriz que será inicializada.
*                    Este parâmetro é passado por referência.
*     $P Linhas - quantidade de linhas que a matriz terá.
*     $P Colunas - quantidade de colunas que a matriz terá.
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
*     TAB_CondRetMatrizNaoExiste
*
***********************************************************************/
   TAB_tpCondRet TAB_DestruirMatriz( TAB_tpMatriz ** ppMatriz ) ;


/***************************************************************************
*
*  $FC Função: TAB Ir para nó ao norte.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção norte
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Ir para nó ao sul.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção sul
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Ir para nó à este.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção este.
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Ir para nó à oeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção oeste
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Ir para nó à nordeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção nordeste
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Ir para nó à sudeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção sudeste
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Ir para nó à sudoeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção sudoeste
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Ir para nó à noroeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção noroeste
*  
*  $EP Parâmetros
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
*  $FC Função: TAB Obter valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
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
*  $FC Função: TAB Atribuir valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - o valor que será atribuido ao nó corrente.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*
***********************************************************************/
   
   TAB_tpCondRet TAB_AtribuirValorCorr( TAB_tpMatriz * pMatriz , LIS_tppLista ValorParm ) ;

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
