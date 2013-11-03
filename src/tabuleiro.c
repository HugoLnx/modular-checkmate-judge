/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*       1.00   hg e nf  15/09/2013 Adaptação do módulo para manipular matrizes
*
***************************************************************************/

#include <stdio.h>
#include "lista.h"
#include "grafo.h"
#include "mem_manager.h"

#include <string.h>

#define TABULEIRO_OWN
#include "tabuleiro.h"
#undef TABULEIRO_OWN

#define NOME_REI "rei"

typedef struct stMovimento {
   LIS_tppLista passos;
   TAB_tpTipoMovimento tipo;
} tpMovimento;

typedef struct stModeloPeca {
   tpMovimento *pMovimento;
   char *nome;
} tpModeloPeca;

typedef struct stPeca {
   tpModeloPeca *pModelo;
   TAB_tpTimePeca time;
} tpPeca;

typedef struct stPegada {
   tpPeca *pPeca;
   struct stPegada *pAnterior;
} tpPegada;

typedef struct stCasa {
   char *nome;
   tpPeca *pPeca;
   LIS_tppLista pegadas;
} tpCasa;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma matriz
*
*
*  $ED Descrição do tipo
*     A cabeça da matriz é o ponto de acesso para uma determinada matriz.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*
***********************************************************************/

   typedef struct stMatriz {
         GRA_tppGrafo pGrafo;
         LIS_tppLista pModelosPecas;
         tpCasa *pCasaRei;
   } TAB_tpMatriz;


   
   typedef TAB_tpCondRet (*tpCallbackIterarCasasAlcancePeca)(TAB_tpMatriz *pTabuleiro, tpPeca *pPeca,
      tpPegada *pPegAnt);


/***** Protótipos das funções encapuladas no módulo *****/

   static TAB_tpCondRet CriarNoOrigem( TAB_tpMatriz * pMatriz ) ;

   static void EsvaziarMatriz( TAB_tpMatriz * pMatriz ) ;

   static TAB_tpCondRet AddColuna( TAB_tpMatriz * pMatriz ) ;

   static TAB_tpCondRet InicializarMatriz(TAB_tpMatriz *pMatriz, int Linhas, int Colunas);

   static TAB_tpCondRet CriarMatriz(TAB_tpMatriz **ppMatriz);

   static char* NomeDaCasa(int x, int y);

   static tpCasa* CriarCasa();
   
   static void DestroiMovimento(void *pValor);
   
   static void DestruirModeloPeca(void *pValor);
   
   static void DestruirPeca(void *pValor);
   
   static void DestruirCasa(void *pValor);
   
   static void DestruirPegada(void *pValor);

   static int CompararPegadas(void *pPonteiro1, void *pPonteiro2);

   static int CompararNomeModeloPeca(void *pValor1, void *pValor2);

   static int CompararPassos(void *pValor1, void *pValor2);

   static TAB_tpCondRet CriarInstanciaDeRei(TAB_tpMatriz *pTabuleiro, tpPeca **pPeca);
   
   static TAB_tpCondRet CriarInstanciaDePeca(TAB_tpMatriz *pTabuleiro, char *nome,
      TAB_tpTimePeca time, tpPeca **ppPeca);

   static TAB_tpCondRet IterarPelasCasasDeAlcanceDaPeca(TAB_tpMatriz *pTabuleiro,
      tpCasa *pCasa, tpCallbackIterarCasasAlcancePeca operar);
   
   static TAB_tpCondRet SeguirPassosDaPeca(TAB_tpMatriz *pTabuleiro, LIS_tppLista pPassos,
      tpPeca *pPeca, TAB_tpDirecao orientacao, tpCallbackIterarCasasAlcancePeca operar);

   static TAB_tpCondRet SeguirPassoDaPeca(TAB_tpMatriz *pTabuleiro,
      TAB_tpPasso *pPasso, tpPeca *pPeca, TAB_tpDirecao orientacao,
      tpCallbackIterarCasasAlcancePeca operar);

   static TAB_tpCondRet RemoverPegadaDaPecaNaCasaAtual(TAB_tpMatriz *pTabuleiro, tpPeca *pPeca,
      tpPegada *pPegAnt);
   
   static TAB_tpCondRet InserirPegadaDaPecaNaCasaAtual(TAB_tpMatriz *pTabuleiro, tpPeca *pPeca,
      tpPegada *pPegAnt);

   static TAB_tpDirecao DirecaoOrientadaPara(TAB_tpDirecao direcao, TAB_tpDirecao orientacao);

   static char* DirecaoComoString(TAB_tpDirecao direcao);
   
   static void DestruirPasso(void *pValor);

   static TAB_tpCondRet InserirModelosPecas(LIS_tppLista pModelosPecas, TAB_tpMatriz *pTabuleiro);
   
   static LIS_tppLista CopiarPassos(LIS_tppLista pPassos);

/*****  Código das funções exportadas pelo módulo  *****/

   TAB_tpCondRet TAB_AlgumaPegadaInimiga(TAB_tpMatriz *pTabuleiro, int *pResposta)
   {
      tpCasa *pCasa;
      int estaVazia;
      LIS_tpCondRet condRet = LIS_CondRetOK;

      GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **) &pCasa);

      LIS_EstaVazia(pCasa->pegadas, &estaVazia);
      LIS_IrInicioLista(pCasa->pegadas);
      while (condRet == LIS_CondRetOK && !estaVazia)
      {
         tpPegada *pPegada;
         LIS_ObterValor(pCasa->pegadas, (void **) &pPegada);
         if (pPegada->pPeca->time == INIMIGA)
         {
            *pResposta = 1;
            return TAB_CondRetOK;
         }
         condRet =  LIS_AvancarElementoCorrente(pCasa->pegadas, 1);
      }

      *pResposta = 0;
      return TAB_CondRetOK;
   }


   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpMatriz ** ppMatriz)
   {
     CriarMatriz(ppMatriz);
     return InicializarMatriz(*ppMatriz, ALTURA, LARGURA);
   }

/***************************************************************************
*
*  Função: MAT Destruir matriz
*  ****/
   TAB_tpCondRet TAB_DestruirMatriz(TAB_tpMatriz **ppMatriz)
   {
		TAB_tpMatriz *pMatriz;
      
		if (ppMatriz == NULL || *ppMatriz == NULL)
		{
			return TAB_CondRetMatrizNaoExiste ;
		}
      
		pMatriz = *ppMatriz;
         
		GRA_DestruirGrafo(&pMatriz->pGrafo);
		MEM_Free(pMatriz);
		*ppMatriz = NULL;

		return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_CopiarTabuleiro(TAB_tpMatriz *pTabuleiro, TAB_tpMatriz **ppCopia)
   {
      TAB_tpMatriz *pCopia = NULL;
      int x, y;

      TAB_CriarTabuleiro(&pCopia);

      InserirModelosPecas(pTabuleiro->pModelosPecas, pCopia);

      if (pTabuleiro->pCasaRei)
      {
         TAB_IrCasa(pCopia, pTabuleiro->pCasaRei->nome);
         TAB_InserirRei(pCopia);
      }

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            char *nome = NomeDaCasa(x, y);
            tpCasa *pCasa;

            TAB_IrCasa(pTabuleiro, nome);
            GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **) &pCasa);

            if (pCasa->pPeca && pCasa->pPeca->pModelo)
            {
               char *nomeModelo;
               TAB_tpTimePeca time;

               TAB_IrCasa(pCopia, nome);
               nomeModelo = pCasa->pPeca->pModelo->nome;
               time = pCasa->pPeca->time;
               TAB_InserirPeca(pCopia, nomeModelo, time);
            }
         }
      }

      *ppCopia = pCopia;

      return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_CriarPeca(TAB_tpMatriz *pTabuleiro, char *nome,
      LIS_tppLista pPassos, TAB_tpTipoMovimento tipoMovimento)
   {
      tpModeloPeca *pModelo;
      tpMovimento *pMovimento;
      MEM_Alloc(sizeof(tpModeloPeca), (void **) &pModelo);
      MEM_Alloc(sizeof(tpMovimento), (void **) &pMovimento);

      pModelo->nome = nome;
      pMovimento->passos = pPassos;
      pMovimento->tipo = tipoMovimento;
      pModelo->pMovimento = pMovimento;

      LIS_IrFinalLista(pTabuleiro->pModelosPecas);
      LIS_InserirElementoApos(pTabuleiro->pModelosPecas, pModelo);

      return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_AlterarPeca(TAB_tpMatriz *pTabuleiro, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, TAB_tpTipoMovimento novoTipoMovimento)
   {
      tpModeloPeca *pModelo;
      LIS_tpCondRet lisCondRet;

      LIS_IrInicioLista(pTabuleiro->pModelosPecas);
      
      lisCondRet = LIS_ProcurarValor(pTabuleiro->pModelosPecas,nomeAtual);

      if(lisCondRet != LIS_CondRetOK)
      {
         return TAB_CondRetPecaNaoEncontrada;
      }

      LIS_ObterValor(pTabuleiro->pModelosPecas, &pModelo);

      MEM_Free(pModelo->nome);
      pModelo->nome = nomeNovo;
      pModelo->pMovimento->passos= pNovosPassos;
      pModelo->pMovimento->tipo = novoTipoMovimento;

      return TAB_CondRetOK;
   }
   
   TAB_tpCondRet TAB_InserirRei(TAB_tpMatriz *pTabuleiro)
   {
      GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **) &pTabuleiro->pCasaRei);

      CriarInstanciaDeRei(pTabuleiro, &pTabuleiro->pCasaRei->pPeca);

      return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_InserirPeca(TAB_tpMatriz *pTabuleiro, char *nome, TAB_tpTimePeca time)
   {
      tpCasa *pCasa;
      TAB_tpCondRet tabCondRet;
      GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **)&pCasa);

      tabCondRet = CriarInstanciaDePeca(pTabuleiro, nome, time, &pCasa->pPeca);

      if(tabCondRet != TAB_CondRetOK)
      {
         return tabCondRet;
      }

      IterarPelasCasasDeAlcanceDaPeca(pTabuleiro, pCasa, InserirPegadaDaPecaNaCasaAtual);

      TAB_IrCasa(pTabuleiro, pCasa->nome);

      return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_RemoverPeca(TAB_tpMatriz *pTabuleiro)
   {
      tpCasa *pCasa;
      
      GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **)&pCasa);

      IterarPelasCasasDeAlcanceDaPeca(pTabuleiro, pCasa, RemoverPegadaDaPecaNaCasaAtual);

      TAB_IrCasa(pTabuleiro, pCasa->nome);

      DestruirPeca(pCasa->pPeca);
      pCasa->pPeca = NULL;

      return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_RemoverRei(TAB_tpMatriz *pTabuleiro)
   {
      MEM_Free(pTabuleiro->pCasaRei->pPeca);
      pTabuleiro->pCasaRei = NULL;

      return TAB_CondRetOK;
   }


   TAB_tpCondRet TAB_IrCasa(TAB_tpMatriz *pTabuleiro, char *nomeCasa)
   {
      GRA_tpCondRet condRet;

      if (pTabuleiro == NULL)
      {
         return TAB_CondRetMatrizNaoExiste;
      }
      
      condRet = GRA_IrParaAOrigem(pTabuleiro->pGrafo, nomeCasa);
      if (condRet != GRA_CondRetOK)
      {
         return TAB_CondRetNaoEhNo;
      }

      return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_IrCasaRei(TAB_tpMatriz *pTabuleiro)
   {
      GRA_IrParaAOrigem(pTabuleiro->pGrafo, pTabuleiro->pCasaRei->nome);

      return TAB_CondRetOK;
   }



   TAB_tpCondRet TAB_IrPara(TAB_tpMatriz *pMatriz , TAB_tpDirecao direcao)
   {
      GRA_tpCondRet condRet;
      GRA_tppGrafo pGrafo;

     if (pMatriz == NULL)
     {
        return TAB_CondRetMatrizNaoExiste ;
     }

     pGrafo = pMatriz->pGrafo;
     condRet = GRA_SeguirPelaAresta(pGrafo, DirecaoComoString(direcao));
     
     if (condRet != GRA_CondRetOK)
     {
        return TAB_CondRetNaoEhNo;
     }

	  return TAB_CondRetOK ;

   }

/*****  Código das funções encapsuladas no módulo  *****/

   char* DirecaoComoString(TAB_tpDirecao direcao)
   {
      switch(direcao)
      {
         case NORTE:     return "N" ; break;
         case ESTE:      return "E" ; break;
         case SUL:       return "S" ; break;
         case OESTE:     return "O" ; break;
         case NORDESTE:  return "NE"; break;
         case SUDESTE:   return "SE"; break;
         case SUDOESTE:  return "SO"; break;
         case NOROESTE:  return "NO"; break;
         default: return NULL;
      }
   }


   
/***********************************************************************
*
*  $FC Função: TAB Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet CriarMatriz(TAB_tpMatriz **ppMatriz)
   {
	  TAB_tpMatriz *pMatriz;

      if (ppMatriz != NULL && *ppMatriz != NULL)
      {
         TAB_DestruirMatriz(ppMatriz);
      }
	  
      MEM_Alloc(sizeof(TAB_tpMatriz), (void **) &pMatriz);
      if (pMatriz == NULL)
      {
         return TAB_CondRetFaltouMemoria ;
      }

      GRA_CriarGrafo(&pMatriz->pGrafo, DestruirCasa);
      LIS_CriarLista(&pMatriz->pModelosPecas, DestruirModeloPeca, CompararNomeModeloPeca);

      pMatriz->pCasaRei = NULL;

	  *ppMatriz = pMatriz;

      return TAB_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: TAB Inicializar a matriz
*
*  $EP Parâmetros
*     $P pMatriz - matriz que será inicializada.
*                    Este parâmetro é passado por referência.
*     $P Linhas - quantidade de linhas que a matriz terá.
*     $P Colunas - quantidade de colunas que a matriz terá.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet InicializarMatriz(TAB_tpMatriz *pMatriz)
   {
	   int x, y;

	   if( pMatriz == NULL )
	   {
		   return TAB_CondRetMatrizNaoExiste ;
	   }

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            char *nome = NomeDaCasa(x, y);
            GRA_InserirVertice(pMatriz->pGrafo, nome, CriarCasa(nome));
            GRA_TornarCorrenteUmaOrigem(pMatriz->pGrafo);
         }
      }

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            char *nome = NomeDaCasa(x, y);
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(NORTE)   , nome, NomeDaCasa(x, y-1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(ESTE)    , nome, NomeDaCasa(x+1, y));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(SUL)     , nome, NomeDaCasa(x, y+1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(OESTE)   , nome, NomeDaCasa(x-1, y));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(NORDESTE), nome, NomeDaCasa(x+1, y-1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(SUDESTE) , nome, NomeDaCasa(x+1, y+1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(SUDOESTE), nome, NomeDaCasa(x-1, y+1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(NOROESTE), nome, NomeDaCasa(x-1, y-1));
         }
      }

      GRA_IrParaAOrigem(pMatriz->pGrafo, NomeDaCasa(0,0));

	   return TAB_CondRetOK ;
   }

   char* NomeDaCasa(int x, int y)
   {
      char *nome;

      if (x >= LARGURA || x < 0 || y >= ALTURA || y < 0)
      {
         return NULL;
      }

      MEM_Alloc(sizeof(char)*3, (void **) &nome);
      nome[0] = x + 'A';
      nome[1] = y + '1';
      nome[2] = 0;

      return nome;
   }

   tpCasa* CriarCasa(char *nome)
   {
      tpCasa *pCasa;
      MEM_Alloc(sizeof(tpCasa), (void **) &pCasa);
      LIS_CriarLista(&pCasa->pegadas, DestruirPegada, CompararPegadas);
      pCasa->pPeca = NULL;
      pCasa->nome = nome;
   
      return pCasa;
   }



   void DestruirCasa(void *pValor)
   {
      tpCasa *pCasa = (tpCasa*) pValor;

      LIS_DestruirLista(pCasa->pegadas);
      DestruirPeca((void*) pCasa->pPeca);

      MEM_Free(pCasa);
   }
   
   

   void DestruirPegada(void *pValor)
   {
      tpPegada *pPegada = (tpPegada*) pValor;
      
      if (pValor == NULL)
      {
         return;
      }

      DestruirPegada((void *) pPegada->pAnterior);
      MEM_Free(pValor);
   }



   void DestruirPeca(void *pValor)
   {
      tpPeca *pPeca = (tpPeca*) pValor;
      if (pValor == NULL)
      {
         return;
      }

      MEM_Free(pPeca);
   }


   void DestruirModeloPeca(void *pValor)
   {
      tpModeloPeca *pModelo = (tpModeloPeca*) pValor;

      if (pModelo == NULL)
      {
         return;
      }
      MEM_Free(pModelo->nome);
      DestroiMovimento(pModelo->pMovimento);
      MEM_Free(pModelo);
   }


   void DestroiMovimento(void *pValor)
   {
      tpMovimento *pMovimento = (tpMovimento*) pValor;
      LIS_DestruirLista(pMovimento->passos);
      MEM_Free(pMovimento);
   }

   
   void DestruirPasso(void *pValor)
   {
      MEM_Free(pValor);
   }
   
   int CompararPegadas(void *pPonteiro1, void *pPonteiro2)
   {
      tpPegada *pPegada = (tpPegada*) pPonteiro1;
      tpPeca *pPeca = (tpPeca*) pPonteiro2;
   
      return strcmp(pPegada->pPeca->pModelo->nome, pPeca->pModelo->nome);
   }

   int CompararNomeModeloPeca(void *pValor1, void *pValor2)
   {
      tpModeloPeca *pModelo1 = (tpModeloPeca*) pValor1;
      char *nomeProcurado = (char*) pValor2;

      return strcmp(pModelo1->nome, nomeProcurado);
   }

   
   int CompararPassos(void *pValor1, void *pValor2)
   {
      // TODO: função para comparar passos
      return 0;
   }

   TAB_tpDirecao DirecaoOrientadaPara(TAB_tpDirecao direcao, TAB_tpDirecao orientacao)
   {
      return (TAB_tpDirecao) (((int) direcao + (int) orientacao) % TOTAL_DIRECOES);
   }

   LIS_tppLista CopiarPassos(LIS_tppLista pPassos)
   {
      LIS_tpCondRet condRet = LIS_CondRetOK;
      LIS_tppLista pCopiaPassos;

      LIS_CriarLista(&pCopiaPassos, DestruirPasso, CompararPassos);
      LIS_IrInicioLista(pPassos);

      while (condRet == LIS_CondRetOK)
      {
         TAB_tpPasso *pPasso, *pCopiaPasso;
         LIS_ObterValor(pPassos, (void **) &pPasso);
         MEM_Alloc(sizeof(TAB_tpPasso), (void **) &pCopiaPasso);
         pCopiaPasso->direcao = pPasso->direcao;
         pCopiaPasso->quantidade = pPasso->quantidade;

         LIS_InserirElementoApos(pCopiaPassos, pCopiaPasso);

         condRet = LIS_AvancarElementoCorrente(pPassos, 1);
      }

      return pCopiaPassos;
   }

   TAB_tpCondRet InserirModelosPecas(LIS_tppLista pModelosPecas, TAB_tpMatriz *pTabuleiro)
   {
      LIS_tpCondRet condRet = LIS_CondRetOK;
      int estaVazia;

      LIS_IrInicioLista(pModelosPecas);
      LIS_IrInicioLista(pTabuleiro->pModelosPecas);

      LIS_EstaVazia(pModelosPecas, &estaVazia);

      while (condRet == LIS_CondRetOK && !estaVazia)
      {
         tpModeloPeca *pModelo;
         LIS_tppLista pPassos;
         char *nome;
         TAB_tpTipoMovimento tipo;
         
         LIS_ObterValor(pModelosPecas, (void **) &pModelo);

         MEM_Alloc(sizeof(char)*strlen(pModelo->nome)+1, (void **) &nome);
         strcpy(nome, pModelo->nome);
         
         pPassos = CopiarPassos(pModelo->pMovimento->passos);
         tipo = pModelo->pMovimento->tipo;

         TAB_CriarPeca(pTabuleiro, nome, pPassos, tipo);

         condRet = LIS_AvancarElementoCorrente(pModelosPecas, 1);
      }

      return TAB_CondRetOK;
   }
   
   TAB_tpCondRet CriarInstanciaDePeca(TAB_tpMatriz *pTabuleiro, char *nome,
      TAB_tpTimePeca time, tpPeca **ppPeca)
   {
      tpPeca *pPeca;
      tpModeloPeca *pModelo;
      LIS_tpCondRet lisCondRet;
      MEM_Alloc(sizeof(tpPeca), (void **) &pPeca);
      
      LIS_IrInicioLista(pTabuleiro->pModelosPecas);
      lisCondRet = LIS_ProcurarValor(pTabuleiro->pModelosPecas, nome);
      if(lisCondRet != LIS_CondRetOK)
      {
         return TAB_CondRetPecaNaoEncontrada;
      }
      LIS_ObterValor(pTabuleiro->pModelosPecas, (void**) &pModelo);
      
      pPeca->pModelo = pModelo;
      pPeca->time = time;

      *ppPeca = pPeca;

      return TAB_CondRetOK;
   }

   
   TAB_tpCondRet CriarInstanciaDeRei(TAB_tpMatriz *pTabuleiro, tpPeca **pPeca)
   {
      tpPeca *pRei;
      MEM_Alloc(sizeof(tpPeca), (void **) &pRei);

      pRei->pModelo = NULL;
      pRei->time = ALIADA;

      *pPeca = pRei;

      return TAB_CondRetOK;
   }


   TAB_tpCondRet IterarPelasCasasDeAlcanceDaPeca(TAB_tpMatriz *pTabuleiro,
      tpCasa *pCasa, tpCallbackIterarCasasAlcancePeca operar)
   {
      TAB_tpCondRet condRet;
      LIS_tppLista pPassos;
      int estaVazia;
      
      pPassos =pCasa->pPeca->pModelo->pMovimento->passos;

      LIS_EstaVazia(pPassos, &estaVazia);

      if (estaVazia)
      {
         return TAB_CondRetOK;
      }

      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, NORTE, operar);
      TAB_IrCasa(pTabuleiro, pCasa->nome);
      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, ESTE , operar);
      TAB_IrCasa(pTabuleiro, pCasa->nome);
      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, SUL  , operar);
      TAB_IrCasa(pTabuleiro, pCasa->nome);
      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, OESTE, operar);

      return TAB_CondRetOK;
   }

   TAB_tpCondRet SeguirPassosDaPeca(TAB_tpMatriz *pTabuleiro, LIS_tppLista pPassos,
      tpPeca *pPeca, TAB_tpDirecao orientacao, tpCallbackIterarCasasAlcancePeca operar)
   {
      TAB_tpCondRet tabCondRet;
      LIS_tpCondRet lisCondRet = LIS_CondRetOK;
    
      LIS_IrInicioLista(pPassos);
      while (lisCondRet == LIS_CondRetOK)
      {
         TAB_tpPasso *pPasso;
         LIS_ObterValor(pPassos, (void **) &pPasso);
         
         tabCondRet = SeguirPassoDaPeca(pTabuleiro, pPasso, pPeca, orientacao, operar);
         
         if (tabCondRet != TAB_CondRetOK)
         {
            break;
         }

         lisCondRet = LIS_AvancarElementoCorrente(pPassos, 1);
      }

      if (pPeca->pModelo->pMovimento->tipo == VOA && tabCondRet == TAB_CondRetOK)
      {
         operar(pTabuleiro, pPeca, NULL);
      }

      return TAB_CondRetOK;

   }


   TAB_tpCondRet SeguirPassoDaPeca(TAB_tpMatriz *pTabuleiro,
      TAB_tpPasso *pPasso, tpPeca *pPeca, TAB_tpDirecao orientacao,
      tpCallbackIterarCasasAlcancePeca operar)
   {
      TAB_tpDirecao direcao;
      tpPegada *pPegAnt = NULL;
      int i;

      direcao = DirecaoOrientadaPara(pPasso->direcao, orientacao);
      for (i = 0; i < pPasso->quantidade; i++)
      {
         TAB_tpCondRet condRet;
         condRet = TAB_IrPara(pTabuleiro, direcao);
         if (condRet != TAB_CondRetOK)
         {
            // chegou no final do tabuleiro
            return TAB_CondRetNaoEhNo;
         }

         if (pPeca->pModelo->pMovimento->tipo == ANDA)
         {
            operar(pTabuleiro, pPeca, pPegAnt);
         }
      }

      return TAB_CondRetOK;
   }


   TAB_tpCondRet RemoverPegadaDaPecaNaCasaAtual(TAB_tpMatriz *pTabuleiro, tpPeca *pPeca,
      tpPegada *pPegAnt)
   {
      tpCasa *pCasaAtual;
      tpPegada *pPegada;

      GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **) &pCasaAtual);
      
      LIS_IrInicioLista(pCasaAtual->pegadas);
      LIS_ProcurarValor(pCasaAtual->pegadas, pPeca);
      LIS_ExcluirElemento(pCasaAtual->pegadas);

      return TAB_CondRetOK;
   }

   
   TAB_tpCondRet InserirPegadaDaPecaNaCasaAtual(TAB_tpMatriz *pTabuleiro, tpPeca *pPeca,
      tpPegada *pPegAnt)
   {
      tpCasa *pCasaAtual;
      tpPegada *pPegada;
      
      GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **) &pCasaAtual);
      
      MEM_Alloc(sizeof(tpPegada), (void **) &pPegada);
      pPegada->pAnterior = pPegAnt;
      pPegada->pPeca = pPeca;

      LIS_InserirElementoApos(pCasaAtual->pegadas, pPegada);
      pPegada->pAnterior = pPegAnt;

      return TAB_CondRetOK;
   }



/********** Fim do módulo de implementação: Módulo matriz **********/