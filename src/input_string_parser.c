/***************************************************************************
*
*  Módulo de implementação: GRA  Grafo direcionado
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
*  Assertivas Estruturais
*     Antecessor aponta de volta para o vértice como sucessor
*        Para todo vértice pVerAnt em pVer->pAntecessores existirá uma aresta pAreSuc em pVerAnt->pSucessores tal que pAreSuc->pVertice = pVer
*     
*     Sucessor aponta de volta para o vértice como antecessor
*        Para toda aresta pAreSuc em pVer->pSucessores existirá um vértice pVerAnt em pAreSuc->pVertice->pAntecessores tal que pVerAnt = pVer
*     
*     Se está na origem tem que estar na lista de vértices
*        Para todo vértice pVerOri em pGrafo->pOrigens existirá um vértice pVer em pGrafo->pVertices tal que pVerOri = pVer
*     
*     Se tem corrente ele tem q estar na lista de vértices
*        Se pGrafo->pCorrente != NULL => Existirá um vértice pVer em pGrafo->pVertices tal que pVer = pGrafo->pCorrente
*     
*     Todos os antecessores dos vértices de um grafo têm q estar na lista de vértices desse grafo  
*        Para todo vértice pVer e pVerAnt tal que pVer pertence à pGrafo->pVertices e pVerAnt pertence à pVer->Antecessores existirá um pVer2 pertencente à pGrafo->pVertices tal que pVerAnt = pVer2
*     
*     Todas as arestas dos vértices de um grafo G têm que apontar para um vértice que está na lista desse grafo
*        Para todo vértice pVer e aresta pAre tal que pVer pertence à pGrafo->pVertices e pAre pertence à pVer->pSucessores, existirá um pVer2 pertencente à pGrafo->pVertices tal que pVer2 = pAre->pVertice.
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

#define SEPARADOR_PASSOS " "
#define FORMATO_PASSO_STR "[%d]%s"


/***** Protótipos das funções encapuladas no módulo *****/

static int CompararPassos(void *pValor1, void *pValor2);
static void DestruirPasso(void *pValor);
static TAB_tpPasso* LerPasso(char *passoInput);
TAB_tpDirecao LerDirecao(char *direcaoInput);

/*****  Código das funções exportadas pelo módulo  *****/

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

ISP_tpCondRet ISP_LerPassos(const char *passosStr, LIS_tppLista *ppPassos)
{
   LIS_tppLista passos;
   char *passoStr;
   char *str;
   MEM_Alloc(sizeof(char)*(strlen(passosStr)+1), (void **) &str);
   strcpy(str, passosStr);

   LIS_CriarLista(&passos, DestruirPasso, CompararPassos);

   passoStr = strtok(str, SEPARADOR_PASSOS);

   while (passoStr != NULL)
   {
      TAB_tpPasso *pPasso;
      pPasso = LerPasso(passoStr);
      LIS_InserirElementoApos(passos, pPasso);
      passoStr = strtok(NULL, SEPARADOR_PASSOS);
   }
   
   *ppPassos = passos;

   return ISP_CondRetOK;
}

TAB_tpPasso* LerPasso(char *passoInput)
{
   TAB_tpPasso *pPasso;
   int *pQnt;
   char *strDirecao;

   MEM_Alloc(sizeof(char)*10, (void **) &strDirecao);
   MEM_Alloc(sizeof(int), (void **) &pQnt);
   sscanf(passoInput, FORMATO_PASSO_STR, pQnt, strDirecao);

   MEM_Alloc(sizeof(TAB_tpPasso), (void **) &pPasso);
   pPasso->direcao = LerDirecao(strDirecao);
   pPasso->quantidade = *pQnt;

   return pPasso;
}

TAB_tpDirecao LerDirecao(char *direcaoInput)
{
   char *dirNormalizada = strlwr(direcaoInput);

   if (strcmp(dirNormalizada, "norte") == 0)
   {
      return NORTE;
   }
   else if (strcmp(dirNormalizada, "sul") == 0)
   {
      return SUL;
   }
   else if (strcmp(dirNormalizada, "este") == 0)
   {
      return ESTE;
   }
   else if (strcmp(dirNormalizada, "oeste") == 0)
   {
      return OESTE;
   }
   else if (strcmp(dirNormalizada, "nordeste") == 0)
   {
      return NORDESTE;
   }
   else if (strcmp(dirNormalizada, "sudeste") == 0)
   {
      return SUDESTE;
   }
   else if (strcmp(dirNormalizada, "sudoeste") == 0)
   {
      return SUDOESTE;
   }
   else if (strcmp(dirNormalizada, "noroeste") == 0)
   {
      return NOROESTE;
   }
   else
   {
      return (TAB_tpDirecao) -1;
   }
}


void DestruirPasso(void *pValor)
{
   MEM_Free(pValor);
}

int CompararPassos(void *pValor1, void *pValor2)
{
   return *(int*)pValor1 == *(int*)pValor2;
}

/********** Fim do módulo de implementação: GRA Grafo direcionado **********/