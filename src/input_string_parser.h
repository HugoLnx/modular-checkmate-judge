#if ! defined( INPUT_STRING_PARSER_ )
#define INPUT_STRING_PARSER_
/***************************************************************************
*
*  M�dulo de defini��o: GRA  Grafo direcionado
*
*  Arquivo gerado:              grafo.c
*  Letras identificadoras:      GRA
*
*	Autores:
*     - rc: Robert Corr�a
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1.0     hg & rc  06/out/13   Prepara��o do m�dulo para trabalhar com grafos direcionados.
*
*  Descri��o do m�dulo
*     Implementa grafos direcionados com manipula��o, ou seja, � possivel criar, inserir
*     v�rtices no grafo, conect�-los atrav�s de arestas direcionais al�m de destruir o grafo,
*     um v�rtice ou uma aresta, navegar atrav�s das arestas usando o nome da aresta ou do
*     v�rtice de destino como refer�ncia. � poss�vel tamb�m marcar v�rtices como origem,
*     estes v�rtices poder�o ser acessados � qualquer momento utilizando a fun��o de navega��o
*     para origens.
*
*     Podem existir n grafos em opera��o simultaneamente.
*     Os grafos possuem uma cabe�a encapsulando o seu estado.
*
*     Cada grafo armazena dados gen�ricos.
*     Cada v�tice do grafo possui uma refer�ncia para o valor.
*
***************************************************************************/
 
#if defined( INPUT_STRING_PARSER_OWN )
   #define INPUT_STRING_PARSER_EXT
#else
   #define INPUT_STRING_PARSER_EXT extern
#endif

#include "partida.h"
#include "lista.h"
#include "peca.h"

/***** Declara��es exportadas pelo m�dulo *****/


/***********************************************************************
*
*  Tipo de dados: GRA Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es do grafo
*
***********************************************************************/

typedef enum {

   ISP_CondRetOK,
      /* Concluiu corretamente */

   ISP_CondRetNaoReconhecido,
      /* A entrada n�o foi reconhecida */

   ISP_CondRetFaltouMemoria,
      /* Faltou mem�ria ao tentar alocar algo */
 
} ISP_tpCondRet ;

ISP_tpCondRet ISP_LerTipoMovimento(char *tipoStr, PEC_tpTipoMovimento *pTipo);

ISP_tpCondRet ISP_LerPassos(char *passosStr, LIS_tppLista *ppPassos);

/***********************************************************************/
#undef INPUT_STRING_PARSER_EXT

/********** Fim do m�dulo de defini��o: GRA Grafo direcionado **********/

#else
#endif