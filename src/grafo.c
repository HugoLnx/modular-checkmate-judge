/***************************************************************************
*
*  Módulo de implementação: <abreviação>  <estrutura manipulada pelo módulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.c
*  Letras identificadoras:      <abreviação>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1       <nick>   <data>      <observações>
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"

#define GRAFO_OWN
#include "grafo.h"
#undef GRAFO_OWN

/***********************************************************************
*  Tipo de dados: GRA Vertice do grafo
***********************************************************************/

   typedef struct stVerticeGrafo {

         char *nome;
               /* Nome do vértice */
      
         LIS_tppLista pSucessores;
               /* Ponteiros para as arestas originadas neste vértice */

         LIS_tppLista pAntecessores;
               /* Ponteiro para os vértices que têm arestas 
                  direcionadas para este vértice */

         void * pValor;
               /* valor contido no vértice */

   } tpVertice;

/***********************************************************************
*  Tipo de dados: GRA Aresta do grafo
***********************************************************************/

   typedef struct stArestaGrafo {

         char *nome;
               /* Nome da aresta */
      
         tpVertice * pVertice;
               /* Ponteiro para o vértice destino da aresta */

   } tpAresta;


/***********************************************************************
*  Tipo de dados: GRA Grafo
***********************************************************************/

   typedef struct stGrafo {

         LIS_tppLista pOrigens;
               /* Vértices que são origens do grafo */

         LIS_tppLista pVertices;
               /* Todos os vértices do grafo */
      
         tpVertice * pCorrente;
               /* Vértice corrente */

		 void (*DestruirConteudo)(void *pConteudo);
			 /* Lógica responsável por destruir o valor do vértice do grafo */

   } GRA_tpGrafo;


/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirVertice(tpVertice *pVertice);
   static void DestruirAresta(tpVertice *pVertice);
   static int CompararValores (void *pValor1, void *pValor2);

/*****  Código das funções exportadas pelo módulo  *****/
//
GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo,
	void (*DestruirConteudo)(void *pConteudo))
{
	GRA_tpGrafo *pGrafo = (GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));

	pGrafo->pCorrente = NULL;
	pGrafo->DestruirConteudo = DestruirConteudo;

	LIS_CriarLista(&(pGrafo->pOrigens), pGrafo->DestruirConteudo, CompararValores);
	LIS_CriarLista(&(pGrafo->pVertices), pGrafo->DestruirConteudo, CompararValores);
	
	*ppGrafo = pGrafo;

    return GRA_CondRetOK;
}
//
//
//
//GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo);
//
//
//   GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, char *pNomeVertice, void *pValor)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafo,
//      char *nomeAresta, char *nomeVerticeDestino)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_DestruirVerticeCorrente(GRA_tppGrafo pGrafo)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_DestruirArestaAdjacente(GRA_tppGrafo pGrafo, char *pNomeAresta)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_TornarCorrenteUmaOrigem(GRA_tppGrafo pGrafo)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafo, char *nomeVertice)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafo, char *nomeAresta)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafo, char *nomeVertice)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_ObterConteudoCorrente(GRA_tppGrafo pGrafo, void **ppValor)
//   {
//      return GRA_CondRetGrafoVazia;
//   }
//
//
//
//   GRA_tpCondRet GRA_AlterarConteudoCorrente(GRA_tppGrafo pGrafo, void *pValor)
//   {
//      return GRA_CondRetGrafoVazia;
//   }

 
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  Função: <abreviacao> <nome da funcao por extenso>
*
*  Descrição:
*    <descrição da função>
*
***********************************************************************/

   /*void FuncaoEncapsulada( )
   {

   }*/

  int CompararValores( void * pValor1 , void * pValor2 )
  {
	return 0;
  }

/********** Fim do módulo de implementação: GRA Grafo direcionado **********/