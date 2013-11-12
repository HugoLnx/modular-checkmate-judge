#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  M�dulo de defini��o: TAB  Tabuleiro
*
*  Arquivo gerado:              tabuleiro.h
*  Letras identificadoras:      TAB
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Matriz adaptada para ser tabuleiro.
*
*  Descri��o do m�dulo
*     <descri��o do m�dulo>
*     TODO: (incluir assertivas estruturais)
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


/* Tipo refer�ncia para uma <estrutura-manipulada> */
typedef struct TAB_stTabuleiro* TAB_tppTabuleiro;

/***********************************************************************
*
*  Tipo de dados: TAB <descricao-do-enum>
*
*
*  Descri��o do tipo
*     <descricao do enum>
*
***********************************************************************/
   typedef enum {

         TAB_CondRetOK = 0,
               /* Executou correto */

         TAB_CondRetNaoEhCasa = 2,
               /* N�o � n� na dire��o desejada */

         TAB_CondRetTabuleiroNaoExiste = 3,
               /* Tabuleiro n�o existe */

         TAB_CondRetFaltouMemoria = 5
               /* Faltou mem�ria ao alocar dados */

   } TAB_tpCondRet;

   /***********************************************************************
*
*  Fun��o: TAB <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro, void (*destruirValor)(void *pValor));

/***********************************************************************
*
*  Fun��o: TAB <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterValor(TAB_tppTabuleiro pTabuleiro, void **ppValor);

/***********************************************************************
*
*  Fun��o: TAB <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
   TAB_tpCondRet TAB_AlterarValor(TAB_tppTabuleiro pTabuleiro, void *pValor);

/***********************************************************************
*
*  Fun��o: TAB <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro *ppTabuleiro);

/***********************************************************************
*
*  Fun��o: TAB <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
   TAB_tpCondRet TAB_IrCasa(TAB_tppTabuleiro pTabuleiro, char *nome);

/***********************************************************************
*
*  Fun��o: TAB <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
   TAB_tpCondRet TAB_PercorrerCasas(TAB_tppTabuleiro pTabuleiro, int (*fazerNaCasa)(TAB_tppTabuleiro pTabuleiro, char *nome));

/***********************************************************************
*
*  Fun��o: TAB <nome da funcao por extenso>
*
*  Descri��o
*     <descricao da fun��o>
*
*  Par�metros
*     <param 1>      - <explica��o sobre parametro 1>
*     <parametro 2>  - <explica��o sobre parametro 2>
*
*  Condi��es de retorno
*     <listar os poss�veis tpCondRet>
*
*  Retorno por refer�ncia
*     <descri��o do retorno>
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saida
*     <assertivas de saida>
*
***********************************************************************/
   TAB_tpCondRet TAB_NomeDaCasa(int x, int y, char **pNome);

/***************************************************************************
*
*  Fun��o: TAB Ir para
*  
*  Descri��o da fun��o
*  Muda a casa corrente do tabuleiro para a casa na dire��o apontada
*  
*  Par�metros
*     pTabuleiro - ponteiro para o tabuleiro que ser� manipulado.
*     direcao    - representa a dire��o que o n� corrente navegar�.
*
*  Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetNaoEhCasa
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do tabuleiro.
*     - Existe casa com o nome passado por par�metro.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do tabuleiro.
*     - Casa corrente � a casa com o nome passado por par�metro.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrPara(TAB_tppTabuleiro pTabuleiro, DIR_tpDirecao);


#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
