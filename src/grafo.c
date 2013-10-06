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

	void (*destruirValor)(void *pValor);
	/* L�gica respons�vel por destruir o valor do v�rtice do grafo */

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

	void (*destruirValor)(void *pValor);
	/* L�gica respons�vel por destruir o valor do v�rtice do grafo */

} tpGrafo;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void NaoFazNada(void *pVazio);
static void DestruirVertice(void *pVazio);
static void DestruirAresta(void *pVazio);
static int CompararVerticeENome (void *pVazio1, void *pVazio2);
static int CompararArestaENome (void *pVazio1, void *pVazio2);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*  Tipo de dados: GRA Criar grafo
***********************************************************************/
GRA_tpCondRet GRA_CriarGrafo(GRA_tppGrafo *ppGrafo,
	void (*destruirValor)(void *pValor))
{
	tpGrafo *pGrafo = (tpGrafo *) malloc(sizeof(tpGrafo));

	pGrafo->pCorrente = NULL;
	pGrafo->destruirValor = destruirValor;

	LIS_CriarLista(&pGrafo->pOrigens, NaoFazNada, CompararVerticeENome);
	LIS_CriarLista(&pGrafo->pVertices, DestruirVertice, CompararVerticeENome);

	*ppGrafo = (GRA_tppGrafo) pGrafo;

	return GRA_CondRetOK;
}

/***********************************************************************
*  Tipo de dados: GRA Destruir grafo
***********************************************************************/
GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *ppGrafo)
{
	tpGrafo *pGrafo = (tpGrafo*) *ppGrafo;

	if (pGrafo == NULL)
	{
		return GRA_CondRetOK;
	}
	LIS_DestruirLista(pGrafo->pVertices);
	LIS_DestruirLista(pGrafo->pOrigens);

	free(pGrafo);
	pGrafo = NULL;
	*ppGrafo = NULL;
	
	return GRA_CondRetOK;
}

/***********************************************************************
*  Tipo de dados: GRA Inserir vertice
***********************************************************************/
GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafoParm, char *pNomeVertice, void *pValor)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	tpVertice *pVertice;

	if (pGrafo == NULL)
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
	pVertice->destruirValor = pGrafo->destruirValor;

	LIS_CriarLista(&pVertice->pAntecessores, NaoFazNada, CompararVerticeENome);
	LIS_CriarLista(&pVertice->pSucessores, DestruirAresta, CompararArestaENome);

	pGrafo->pCorrente = pVertice;
	LIS_InserirElementoApos(pGrafo->pVertices, pVertice);

	return GRA_CondRetOK;
}


/***********************************************************************
*  Tipo de dados: GRA Inserir aresta do corrente para outro v�rtice
***********************************************************************/
GRA_tpCondRet GRA_InserirArestaDoCorrentePara(GRA_tppGrafo pGrafoParm,
	char *nomeAresta, char *nomeVerticeDestino)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;
	tpAresta *pAresta;
	LIS_tpCondRet lisCondRet;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pAresta = (tpAresta*) malloc(sizeof(tpAresta));
	if (pAresta == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	}

	LIS_IrInicioLista(pGrafo->pVertices);
	lisCondRet = LIS_ProcurarValor(pGrafo->pVertices, nomeVerticeDestino);
	if (lisCondRet == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}
	else
	{
		void * pVazio;
		LIS_ObterValor(pGrafo->pVertices, &pVazio);
		pAresta->pVertice = (tpVertice*) pVazio;
		lisCondRet = LIS_InserirElementoApos(pAresta->pVertice->pAntecessores, pGrafo->pCorrente);
		if (lisCondRet == LIS_CondRetFaltouMemoria)
		{
			return GRA_CondRetFaltouMemoria;
		}
	}

	lisCondRet = LIS_InserirElementoApos(pGrafo->pCorrente->pSucessores, pAresta);
	if (lisCondRet == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}

	pAresta->nome = nomeAresta;

	return GRA_CondRetOK;
}


/***********************************************************************
*  Tipo de dados: GRA Obter conte�do do v�rtice corrente
***********************************************************************/
GRA_tpCondRet GRA_ObterValorCorrente(GRA_tppGrafo pGrafoParm, void **ppValor)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;

	if (pGrafo == NULL)
	{
		*ppValor = NULL;
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	if (pGrafo->pCorrente == NULL)
	{
		*ppValor = NULL;
		return GRA_CondRetGrafoVazio; 
	}

	*ppValor = pGrafo->pCorrente->pValor;
	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_AlterarValorCorrente(GRA_tppGrafo pGrafoParm, void *pValor)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	if (pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	pGrafo->pCorrente->pValor = pValor;
	return GRA_CondRetOK;
}


/***********************************************************************
*  Tipo de dados: GRA Tornar v�rtice corrente uma origem
***********************************************************************/
GRA_tpCondRet GRA_TornarCorrenteUmaOrigem(GRA_tppGrafo pGrafoParm)
{
	tpGrafo *pGrafo = (tpGrafo*) pGrafoParm;

	if (pGrafo == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	if (pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	LIS_InserirElementoApos(pGrafo->pOrigens, pGrafo->pCorrente);
	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_DestruirVerticeCorrente(GRA_tppGrafo pGrafoParm)
{
	tpGrafo *pGrafo = NULL;
	tpVertice  *pVertice = NULL;
	int estaVazia = -1;

	LIS_tpCondRet lisCondRet;

	if(pGrafoParm == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pGrafo = (tpGrafo*) pGrafoParm;

	if(pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	LIS_EstaVazia(pGrafo->pOrigens,&estaVazia);

	if(estaVazia)
	{
		return GRA_CondRetNaoAchou;
	}

	// remove corrente vai para origem

	LIS_ObterValor(pGrafo->pOrigens,(void**)&pVertice);

	LIS_IrInicioLista(pGrafo->pVertices);
	LIS_ProcurarValor(pGrafo->pVertices,pGrafo->pCorrente->nome);
	LIS_ExcluirElemento(pGrafo->pVertices);

	pGrafo->pCorrente = pVertice;
	

	return GRA_CondRetOK;
}



GRA_tpCondRet GRA_DestruirArestaAdjacente(GRA_tppGrafo pGrafoParm, char *pNomeAresta)
{
	tpGrafo *pGrafo = NULL;
	tpAresta *pAresta = NULL;
	
	LIS_tpCondRet lisCondRet;

	if(pGrafoParm == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pGrafo = (tpGrafo*) pGrafoParm;

	if(pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	// Busca Aresta � remover
	LIS_IrInicioLista(pGrafo->pCorrente->pSucessores);
	lisCondRet = LIS_ProcurarValor(pGrafo->pCorrente->pSucessores, pNomeAresta);
	if(lisCondRet != LIS_CondRetOK)
	{
		return GRA_CondRetNaoAchou;
	}
	LIS_ObterValor(pGrafo->pCorrente->pSucessores, (void**)&pAresta);

	// Remove refer�ncia do v�rtice corrente
	LIS_IrInicioLista(pAresta->pVertice->pAntecessores);
	LIS_ProcurarValor(pAresta->pVertice->pAntecessores,pGrafo->pCorrente->nome);

	LIS_ExcluirElemento(pAresta->pVertice->pAntecessores);
	LIS_ExcluirElemento(pGrafo->pCorrente->pSucessores);

	return GRA_CondRetOK;
}

GRA_tpCondRet GRA_IrParaVerticeAdjacente(GRA_tppGrafo pGrafoParm, char *nomeVertice)
{
	tpGrafo *pGrafo = NULL;
	tpAresta *pAresta = NULL;
	tpVertice *pVertice = NULL;
	int numElemLista = 0;

	if(pGrafoParm == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pGrafo = (tpGrafo*) pGrafoParm;

	if(pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	LIS_NumELementos(pGrafo->pCorrente->pSucessores, &numElemLista);
	LIS_IrInicioLista(pGrafo->pCorrente->pSucessores);

	while(numElemLista > 0)
	{
		LIS_ObterValor(pGrafo->pCorrente->pSucessores, (void**)&pAresta);

		if(!strcmp(nomeVertice, pAresta->pVertice->nome))
		{
			pGrafo->pCorrente = pAresta->pVertice;
			return GRA_CondRetOK;
		}

		LIS_AvancarElementoCorrente(pGrafo->pCorrente->pSucessores,1);

		numElemLista--;
	}

	return GRA_CondRetNaoAchou;
}

GRA_tpCondRet GRA_SeguirPelaAresta(GRA_tppGrafo pGrafoParm, char *nomeAresta)
{
	tpGrafo *pGrafo = NULL;
	tpAresta *pAresta = NULL;
	LIS_tpCondRet lisCondRet;

	if(pGrafoParm == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pGrafo = (tpGrafo*) pGrafoParm;

	if(pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	LIS_IrInicioLista(pGrafo->pCorrente->pSucessores);

	lisCondRet = LIS_ProcurarValor(pGrafo->pCorrente->pSucessores, nomeAresta);

	if(lisCondRet != LIS_CondRetOK)
	{
		return GRA_CondRetNaoAchou;
	}

	LIS_ObterValor(pGrafo->pCorrente->pSucessores, (void**)&pAresta);

	pGrafo->pCorrente = pAresta->pVertice;

	return GRA_CondRetOK;
}

GRA_tpCondRet GRA_IrParaAOrigem(GRA_tppGrafo pGrafoParm, char *nomeVertice)
{
	tpGrafo *pGrafo = NULL;
	LIS_tpCondRet lisCondRet;
	tpVertice *pVertice;
	if(pGrafoParm == NULL)
	{
		return GRA_CondRetGrafoNaoFoiCriado;
	}

	pGrafo = (tpGrafo*) pGrafoParm;

	if(pGrafo->pCorrente == NULL)
	{
		return GRA_CondRetGrafoVazio;
	}

	LIS_IrInicioLista(pGrafo->pOrigens);
	lisCondRet = LIS_ProcurarValor(pGrafo->pOrigens, nomeVertice);

	if(lisCondRet != LIS_CondRetOK)
	{
		return GRA_CondRetNaoAchou;
	}

	LIS_ObterValor(pGrafo->pOrigens, (void**)&pVertice);

	pGrafo->pCorrente = pVertice;

	return GRA_CondRetOK;
}


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  Fun��o: <abreviacao> <nome da funcao por extenso>
*
*  Descri��o:
*    <descri��o da fun��o>
*
***********************************************************************/

void DestruirVertice(void *pVazio)
{
	tpVertice *pVertice = (tpVertice*) pVazio;

	LIS_DestruirLista(pVertice->pAntecessores);
	LIS_DestruirLista(pVertice->pSucessores);

	pVertice->destruirValor(pVertice->pValor);

	free(pVertice->nome);

	free(pVertice);

	
}

void DestruirAresta(void *pVazio)
{
	tpAresta *pAresta = (tpAresta*) pVazio;

	free(pAresta->nome);
	free(pAresta);
}

// A lista de origens n�o deve destruir os vertices, pois
// estes j� ser�o destruidos na pela lista de vertices mesmo
// Provavelmente ser� melhor preparar o m�dulo lista para receber NULL
void NaoFazNada(void *pVazio) {}

// usado para fazer a busca na lista de vertices
int CompararVerticeENome( void *pVazio1, void *pVazio2 )
{
	tpVertice *pVertice1 = (tpVertice*) pVazio1;
	char *nomeBuscado = (char*) pVazio2;

	return strcmp(pVertice1->nome, nomeBuscado);
}

// usado para fazer a busca na lista de arestas
int CompararArestaENome( void *pVazio1, void *pVazio2 )
{
	tpAresta *pAresta1 = (tpAresta*) pVazio1;
	char *nomeBuscado = (char*) pVazio2;

	return strcmp(pAresta1->nome, nomeBuscado);
}

/********** Fim do m�dulo de implementa��o: GRA Grafo direcionado **********/