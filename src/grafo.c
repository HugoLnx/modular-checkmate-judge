/***************************************************************************
*
*  M�dulo de implementa��o: <abrevia��o>  <estrutura manipulada pelo m�dulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.c
*  Letras identificadoras:      <abrevia��o>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1       <nick>   <data>      <observa��es>
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
               /* Nome do v�rtice */
      
         LIS_tppLista pSucessores;
               /* Ponteiros para as arestas originadas neste v�rtice */

         LIS_tppLista pAntecessores;
               /* Ponteiro para os v�rtices que t�m arestas 
                  direcionadas para este v�rtice */

         void * pValor;
               /* valor contido no v�rtice */

   } tpVertice;

/***********************************************************************
*  Tipo de dados: GRA Aresta do grafo
***********************************************************************/

   typedef struct stArestaGrafo {

         char *nome;
               /* Nome da aresta */
      
         tpVertice * pVertice;
               /* Ponteiro para o v�rtice destino da aresta */

   } tpAresta;


/***********************************************************************
*  Tipo de dados: GRA Grafo
***********************************************************************/

   typedef struct stGrafo {

         LIS_tppLista pOrigens;
               /* V�rtices que s�o origens do grafo */

         LIS_tppLista pVertices;
               /* Todos os v�rtices do grafo */
      
         tpVertice * pCorrente;
               /* V�rtice corrente */

		 void (*DestruirConteudo)(void *pConteudo);
			 /* L�gica respons�vel por destruir o valor do v�rtice do grafo */

   } GRA_tpGrafo;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirVertice(tpVertice *pVertice);
   static void DestruirAresta(tpVertice *pVertice);
   static int CompararValores (void *pValor1, void *pValor2);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
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

 
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  Fun��o: <abreviacao> <nome da funcao por extenso>
*
*  Descri��o:
*    <descri��o da fun��o>
*
***********************************************************************/

   /*void FuncaoEncapsulada( )
   {

   }*/

  int CompararValores( void * pValor1 , void * pValor2 )
  {
	return 0;
  }

/********** Fim do m�dulo de implementa��o: GRA Grafo direcionado **********/