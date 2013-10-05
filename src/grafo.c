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
         
         void (*destruirConteudo)(void *pConteudo);
          /* Lógica responsável por destruir o valor do vértice do grafo */

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

       void (*destruirConteudo)(void *pConteudo);
          /* Lógica responsável por destruir o valor do vértice do grafo */

   } tpGrafo;


/***** Protótipos das funções encapuladas no módulo *****/

   static void NaoFazNada(void *pVazio);
   static void DestruirVertice(void *pVazio);
   static void DestruirAresta(void *pVazio);
   static int CompararVerticeENome (void *pVazio1, void *pVazio2);
   static int CompararArestaENome (void *pVazio1, void *pVazio2);

/*****  Código das funções exportadas pelo módulo  *****/
//
GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo,
   void (*destruirConteudo)(void *pConteudo))
{
   tpGrafo *pGrafo = (tpGrafo *) malloc(sizeof(tpGrafo));

   pGrafo->pCorrente = NULL;
   pGrafo->destruirConteudo = destruirConteudo;

   LIS_CriarLista(&pGrafo->pOrigens, NaoFazNada, CompararVerticeENome);
   LIS_CriarLista(&pGrafo->pVertices, DestruirVertice, CompararVerticeENome);
   
   *ppGrafo = (GRA_tppGrafo) pGrafo;

    return GRA_CondRetOK;
}


GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo)
{
   tpGrafo *pGrafo = (tpGrafo*) *ppGrafo;
   
   LIS_DestruirLista(pGrafo->pVertices);
   LIS_DestruirLista(pGrafo->pOrigens);
   free(pGrafo);

   return GRA_CondRetOK;
}


   GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, char *pNomeVertice, void *pValor)
   {
      tpGrafo *pGraf = (tpGrafo*) pGrafo;
      tpVertice *pVertice;
      
      if (pGraf == NULL)
      {
         return GRA_CondRetGrafoNaoFoiCriado;
      }

      pVertice = (tpVertice*) malloc(sizeof(tpVertice));
      if (pVertice == NULL)
      {
         return GRA_CondRetFaltouMemoria;
      }

      pVertice->nome = pNomeVertice;
      pVertice->pValor = pValor;
      pVertice->destruirConteudo = pGraf->destruirConteudo;
      
      LIS_CriarLista(&pVertice->pAntecessores, NaoFazNada, CompararVerticeENome);
      LIS_CriarLista(&pVertice->pSucessores, DestruirAresta, CompararArestaENome);

      pGraf->pCorrente = pVertice;
      LIS_InserirElementoApos(pGraf->pVertices, pVertice);

      return GRA_CondRetOK;
   }



GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafo,
   char *nomeAresta, char *nomeVerticeDestino)
{
   tpGrafo *pGraf = (tpGrafo*) pGrafo;
   tpAresta *pAresta;
   LIS_tpCondRet lisCondRet;
      
   if (pGraf == NULL)
   {
      return GRA_CondRetGrafoNaoFoiCriado;
   }

   pAresta = (tpAresta*) malloc(sizeof(tpAresta));
   if (pAresta == NULL)
   {
      return GRA_CondRetFaltouMemoria;
   }

   LIS_IrInicioLista(pGraf->pVertices);
   lisCondRet = LIS_ProcurarValor(pGraf->pVertices, nomeVerticeDestino);
   if (lisCondRet == LIS_CondRetOK)
   {
      void * pVazio;
      LIS_ObterValor(pGraf->pVertices, &pVazio);
      pAresta->pVertice = (tpVertice*) pVazio;
      lisCondRet = LIS_InserirElementoApos(pAresta->pVertice->pAntecessores, pGraf->pCorrente);
      if (lisCondRet != LIS_CondRetOK)
      {
         return GRA_CondRetErroLIS;
      }
   }
   else
   {
      return GRA_CondRetErroLIS;
   }
   
   lisCondRet = LIS_InserirElementoApos(pGraf->pCorrente->pSucessores, pAresta);
   if (lisCondRet != LIS_CondRetOK)
   {
      return GRA_CondRetErroLIS;
   }

   pAresta->nome = nomeAresta;

   return GRA_CondRetOK;
}



   GRA_tpCondRet GRA_DestruirVerticeCorrente(GRA_tppGrafo pGrafo)
   {
      return GRA_CondRetGrafoVazio;
   }



   GRA_tpCondRet GRA_DestruirArestaAdjacente(GRA_tppGrafo pGrafo, char *pNomeAresta)
   {
      return GRA_CondRetGrafoVazio;
   }



   GRA_tpCondRet GRA_TornarCorrenteUmaOrigem(GRA_tppGrafo pGrafo)
   {
      return GRA_CondRetGrafoVazio;
   }



   GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafo, char *nomeVertice)
   {
      return GRA_CondRetGrafoVazio;
   }



   GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafo, char *nomeAresta)
   {
      return GRA_CondRetGrafoVazio;
   }



   GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafo, char *nomeVertice)
   {
      return GRA_CondRetGrafoVazio;
   }



   GRA_tpCondRet GRA_ObterConteudoCorrente(GRA_tppGrafo pGrafo, void **ppValor)
   {
      return GRA_CondRetGrafoVazio;
   }



   GRA_tpCondRet GRA_AlterarConteudoCorrente(GRA_tppGrafo pGrafo, void *pValor)
   {
      return GRA_CondRetGrafoVazio;
   }

 
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  Função: <abreviacao> <nome da funcao por extenso>
*
*  Descrição:
*    <descrição da função>
*
***********************************************************************/

   void DestruirVertice(void *pVazio)
   {
      tpVertice *pVertice = (tpVertice*) pVazio;
      
      LIS_DestruirLista(pVertice->pAntecessores);
      LIS_DestruirLista(pVertice->pSucessores);
      
      pVertice->destruirConteudo(pVertice->pValor);
      free(pVertice->nome);
      free(pVertice);
   }

   void DestruirAresta(void *pVazio)
   {
      tpAresta *pAresta = (tpAresta*) pVazio;

      free(pAresta->nome);
      free(pAresta);
   }

   // A lista de origens não deve destruir os vertices, pois
   // estes já serão destruidos na pela lista de vertices mesmo
   // Provavelmente será melhor preparar o módulo lista para receber NULL
   void NaoFazNada(void *pVazio) {}

  int CompararVerticeENome( void *pVazio1, void *pVazio2 )
  {
     tpVertice *pVertice1 = (tpVertice*) pVazio1;
     char *nomeBuscado = (char*) pVazio2;

     return strcmp(pVertice1->nome, nomeBuscado);
  }
  
  int CompararArestaENome( void *pVazio1, void *pVazio2 )
  {
     tpAresta *pAresta1 = (tpAresta*) pVazio1;
     char *nomeBuscado = (char*) pVazio2;

     return strcmp(pAresta1->nome, nomeBuscado);
  }

/********** Fim do módulo de implementação: GRA Grafo direcionado **********/