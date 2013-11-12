#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              tabuleiro.h
*  Letras identificadoras:      TAB
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Matriz adaptada para ser tabuleiro.
*
*  Descrição do módulo
*     <descrição do módulo>
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


/* Tipo referência para uma <estrutura-manipulada> */
typedef struct TAB_stTabuleiro* TAB_tppTabuleiro;

/***********************************************************************
*
*  Tipo de dados: TAB <descricao-do-enum>
*
*
*  Descrição do tipo
*     <descricao do enum>
*
***********************************************************************/
   typedef enum {

         TAB_CondRetOK = 0,
               /* Executou correto */

         TAB_CondRetNaoEhCasa = 2,
               /* Não é nó na direção desejada */

         TAB_CondRetTabuleiroNaoExiste = 3,
               /* Tabuleiro não existe */

         TAB_CondRetFaltouMemoria = 5
               /* Faltou memória ao alocar dados */

   } TAB_tpCondRet;

   /***********************************************************************
*
*  Função: TAB <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Condições de retorno
*     <listar os possíveis tpCondRet>
*
*  Retorno por referência
*     <descrição do retorno>
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
*  Função: TAB <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Condições de retorno
*     <listar os possíveis tpCondRet>
*
*  Retorno por referência
*     <descrição do retorno>
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
*  Função: TAB <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Condições de retorno
*     <listar os possíveis tpCondRet>
*
*  Retorno por referência
*     <descrição do retorno>
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
*  Função: TAB <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Condições de retorno
*     <listar os possíveis tpCondRet>
*
*  Retorno por referência
*     <descrição do retorno>
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
*  Função: TAB <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Condições de retorno
*     <listar os possíveis tpCondRet>
*
*  Retorno por referência
*     <descrição do retorno>
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
*  Função: TAB <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Condições de retorno
*     <listar os possíveis tpCondRet>
*
*  Retorno por referência
*     <descrição do retorno>
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
*  Função: TAB <nome da funcao por extenso>
*
*  Descrição
*     <descricao da função>
*
*  Parâmetros
*     <param 1>      - <explicação sobre parametro 1>
*     <parametro 2>  - <explicação sobre parametro 2>
*
*  Condições de retorno
*     <listar os possíveis tpCondRet>
*
*  Retorno por referência
*     <descrição do retorno>
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
*  Função: TAB Ir para
*  
*  Descrição da função
*  Muda a casa corrente do tabuleiro para a casa na direção apontada
*  
*  Parâmetros
*     pTabuleiro - ponteiro para o tabuleiro que será manipulado.
*     direcao    - representa a direção que o nó corrente navegará.
*
*  Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetNaoEhCasa
*
*  Assertivas de entrada
*     - Valem as assertivas estruturais do tabuleiro.
*     - Existe casa com o nome passado por parâmetro.
*
*  Assertivas de saida
*     - Valem as assertivas estruturais do tabuleiro.
*     - Casa corrente é a casa com o nome passado por parâmetro.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrPara(TAB_tppTabuleiro pTabuleiro, DIR_tpDirecao);


#undef TABULEIRO_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
