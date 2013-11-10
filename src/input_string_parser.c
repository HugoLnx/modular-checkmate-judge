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

#include "mem_manager.h"
#include "passo.h"
#include "direcao.h"

#define INPUT_STRING_PARSER_OWN
#include "input_string_parser.h"
#undef INPUT_STRING_PARSER_OWN

#define ANDA_STR "ANDA"
#define VOA_STR  "VOA"

#define SEPARADOR_PASSOS " _"
#define FORMATO_PASSO_STR "[%d]%s"


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static int CompararPassosGenerico(void *pValor1, void *pValor2);
static void DestruirPassoGenerico(void *pValor);
static PAS_tppPasso LerPasso(char *passoInput);
DIR_tpDirecao LerDirecao(char *direcaoInput);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

ISP_tpCondRet ISP_LerTipoMovimento(char *tipoStr, MPEC_tpTipoMovimento *pTipo)
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


//TODO [RCS] - condi��o de retorno para quando n�o conseguir criar os passos v�lidos.
ISP_tpCondRet ISP_LerPassos(const char *passosStr, LIS_tppLista *ppPassos)
{
   LIS_tppLista passos;
   char *passoStr;
   char *str;
   MEM_Alloc(sizeof(char)*(strlen(passosStr)+1), (void **) &str);
   strcpy(str, passosStr);

   LIS_CriarLista(&passos, DestruirPassoGenerico, CompararPassosGenerico);

   passoStr = strtok(str, SEPARADOR_PASSOS);

   while (passoStr != NULL)
   {
      PAS_tppPasso pPasso;
      pPasso = LerPasso(passoStr);
      LIS_InserirElementoApos(passos, pPasso);
      passoStr = strtok(NULL, SEPARADOR_PASSOS);
   }
   
   *ppPassos = passos;

   return ISP_CondRetOK;
}

PAS_tppPasso LerPasso(char *passoInput)
{
   PAS_tppPasso pPasso;
   int *pQnt;
   char *strDirecao;

   MEM_Alloc(sizeof(char)*10, (void **) &strDirecao);
   MEM_Alloc(sizeof(int), (void **) &pQnt);
   sscanf(passoInput, FORMATO_PASSO_STR, pQnt, strDirecao);

   PAS_CriarPasso(&pPasso, LerDirecao(strDirecao), *pQnt);

   return pPasso;
}

DIR_tpDirecao LerDirecao(char *direcaoInput)
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
      return (DIR_tpDirecao) -1;
   }
}


void DestruirPassoGenerico(void *pValor)
{
   PAS_DestruirPasso((PAS_tppPasso*) &pValor);
}

int CompararPassosGenerico(void *pValor1, void *pValor2)
{
   int resp;

   PAS_CompararPassos((PAS_tppPasso) pValor1, (PAS_tppPasso) pValor2, &resp);

   return resp;
}

/********** Fim do m�dulo de implementa��o: GRA Grafo direcionado **********/