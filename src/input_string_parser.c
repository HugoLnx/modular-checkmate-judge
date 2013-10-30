/***************************************************************************
*
*  M�dulo de implementa��o: GRA  Grafo direcionado
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
*  Assertivas Estruturais
*     Antecessor aponta de volta para o v�rtice como sucessor
*        Para todo v�rtice pVerAnt em pVer->pAntecessores existir� uma aresta pAreSuc em pVerAnt->pSucessores tal que pAreSuc->pVertice = pVer
*     
*     Sucessor aponta de volta para o v�rtice como antecessor
*        Para toda aresta pAreSuc em pVer->pSucessores existir� um v�rtice pVerAnt em pAreSuc->pVertice->pAntecessores tal que pVerAnt = pVer
*     
*     Se est� na origem tem que estar na lista de v�rtices
*        Para todo v�rtice pVerOri em pGrafo->pOrigens existir� um v�rtice pVer em pGrafo->pVertices tal que pVerOri = pVer
*     
*     Se tem corrente ele tem q estar na lista de v�rtices
*        Se pGrafo->pCorrente != NULL => Existir� um v�rtice pVer em pGrafo->pVertices tal que pVer = pGrafo->pCorrente
*     
*     Todos os antecessores dos v�rtices de um grafo t�m q estar na lista de v�rtices desse grafo  
*        Para todo v�rtice pVer e pVerAnt tal que pVer pertence � pGrafo->pVertices e pVerAnt pertence � pVer->Antecessores existir� um pVer2 pertencente � pGrafo->pVertices tal que pVerAnt = pVer2
*     
*     Todas as arestas dos v�rtices de um grafo G t�m que apontar para um v�rtice que est� na lista desse grafo
*        Para todo v�rtice pVer e aresta pAre tal que pVer pertence � pGrafo->pVertices e pAre pertence � pVer->pSucessores, existir� um pVer2 pertencente � pGrafo->pVertices tal que pVer2 = pAre->pVertice.
*
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lista.h"
#include "mem_manager.h"
#include "tabuleiro.h"

#define INPUT_STRING_PARSER_OWN
#include "input_string_parser.h"
#undef INPUT_STRING_PARSER_OWN

#define ANDA_STR "ANDA"
#define VOA_STR  "VOA"



/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void DestruirVertice(void *pVazio);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

ISP_tpCondRet ISP_LerTipoMovimento(char *tipoStr, TAB_tpTipoMovimento *pTipo)
{
   if (strcmp(strupr(tipoStr), VOA_STR) == 0)
   {
      *pTipo = VOA;
   }
   else if (strcmp(strupr(tipoStr), ANDA_STR) == 0)
   {
      *pTipo = ANDA;
   }
   else
   {
      return ISP_CondRetNaoReconhecido;
   }

   return ISP_CondRetOK;
}

/********** Fim do m�dulo de implementa��o: GRA Grafo direcionado **********/