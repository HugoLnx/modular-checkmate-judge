#if ! defined( INPUT_STRING_PARSER_ )
#define INPUT_STRING_PARSER_
/***************************************************************************
*
*  Módulo de definição: GRA  Grafo direcionado
*
*  Arquivo gerado:              grafo.c
*  Letras identificadoras:      GRA
*
*	Autores:
*     - rc: Robert Corrêa
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1.0     hg & rc  06/out/13   Preparação do módulo para trabalhar com grafos direcionados.
*
*  Descrição do módulo
*     Implementa grafos direcionados com manipulação, ou seja, é possivel criar, inserir
*     vértices no grafo, conectá-los através de arestas direcionais além de destruir o grafo,
*     um vértice ou uma aresta, navegar através das arestas usando o nome da aresta ou do
*     vértice de destino como referência. É possível também marcar vértices como origem,
*     estes vértices poderão ser acessados à qualquer momento utilizando a função de navegação
*     para origens.
*
*     Podem existir n grafos em operação simultaneamente.
*     Os grafos possuem uma cabeça encapsulando o seu estado.
*
*     Cada grafo armazena dados genéricos.
*     Cada vétice do grafo possui uma referência para o valor.
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

/***** Declarações exportadas pelo módulo *****/


/***********************************************************************
*
*  Tipo de dados: GRA Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

typedef enum {

   ISP_CondRetOK,
      /* Concluiu corretamente */

   ISP_CondRetNaoReconhecido,
      /* A entrada não foi reconhecida */

   ISP_CondRetFaltouMemoria,
      /* Faltou memória ao tentar alocar algo */
 
} ISP_tpCondRet ;

ISP_tpCondRet ISP_LerTipoMovimento(char *tipoStr, PEC_tpTipoMovimento *pTipo);

ISP_tpCondRet ISP_LerPassos(char *passosStr, LIS_tppLista *ppPassos);

/***********************************************************************/
#undef INPUT_STRING_PARSER_EXT

/********** Fim do módulo de definição: GRA Grafo direcionado **********/

#else
#endif