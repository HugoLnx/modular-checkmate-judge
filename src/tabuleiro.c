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
   } TAB_tpMatriz;


/***** Protótipos das funções encapuladas no módulo *****/

   static TAB_tpCondRet CriarNoOrigem( TAB_tpMatriz * pMatriz ) ;

   static void EsvaziarMatriz( TAB_tpMatriz * pMatriz ) ;

   static TAB_tpCondRet AddColuna( TAB_tpMatriz * pMatriz ) ;
   
   static TAB_tpCondRet IrPara( TAB_tpMatriz * pMatriz , TAB_tpDirecao direcao );

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

   static int CompararNomeModeloPeca(void *pValor);
   
   static TAB_tpCondRet CriarInstanciaDePeca(TAB_tpMatriz *pTabuleiro, char *nome,
      TAB_tpTimePeca time, tpPeca **ppPeca);

   static TAB_tpCondRet InserirPegadaDaPecaNaCasaAtual(TAB_tpMatriz *pTabuleiro,
      tpPeca *pPeca, tpPegada *pPegAnt);
   
   static TAB_tpCondRet SeguirPassosDaPeca(TAB_tpMatriz *pTabuleiro, LIS_tppLista pPassos,
      tpPeca *pPeca, TAB_tpDirecao orientacao);

   static TAB_tpCondRet SeguirPassoDaPeca(TAB_tpMatriz *pTabuleiro,
      TAB_tpPasso *pPasso, tpPeca *pPeca, TAB_tpDirecao orientacao);

   static TAB_tpDirecao DirecaoOrientadaPara(TAB_tpDirecao direcao, TAB_tpDirecao orientacao);

/*****  Código das funções exportadas pelo módulo  *****/


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


/***************************************************************************
*
*  Função: MAT Ir para nó ao norte.
*  ****/
   TAB_tpCondRet TAB_IrNoNorte(TAB_tpMatriz *pMatriz)
   {
	   return IrPara( pMatriz , NORTE );
   }



/***************************************************************************
*
*  Função: MAT Ir para nó ao sul.
*  ****/
   TAB_tpCondRet TAB_IrNoSul( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUL );
   }



/***************************************************************************
*
*  Função: MAT Ir para nó à este.
*  ****/
   TAB_tpCondRet TAB_IrNoEste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , ESTE );
   }



/***************************************************************************
*
*  Função: MAT Ir para nó à oeste.
*  ****/
   TAB_tpCondRet TAB_IrNoOeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , OESTE );
   }




/***************************************************************************
*
*  Função: MAT Ir para nó à nordeste.
*  ****/
   TAB_tpCondRet TAB_IrNoNordeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORDESTE );
   }




/***************************************************************************
*
*  Função: MAT Ir para nó à sudeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDESTE );
   }




/***************************************************************************
*
*  Função: MAT Ir para nó à sudoeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudoeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDOESTE );
   }




/***************************************************************************
*
*  Função: MAT Ir para nó à noroeste.
*  ****/
   TAB_tpCondRet TAB_IrNoNoroeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NOROESTE );
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

   TAB_tpCondRet TAB_InserirPeca(TAB_tpMatriz *pTabuleiro, char *nome, TAB_tpTimePeca time)
   {
      tpCasa *pCasa;
      
      GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **)&pCasa);

      CriarInstanciaDePeca(pTabuleiro, nome, time, &pCasa->pPeca);

      CriarPegadasDaPecaNaCasa(pTabuleiro, pCasa);

      return TAB_CondRetOK;
   }

   TAB_tpCondRet CriarInstanciaDePeca(TAB_tpMatriz *pTabuleiro, char *nome,
      TAB_tpTimePeca time, tpPeca **ppPeca)
   {
      tpPeca *pPeca;
      tpModeloPeca *pModelo;

      MEM_Alloc(sizeof(tpPeca), (void **) &pPeca);
      
      LIS_IrInicioLista(pTabuleiro->pModelosPecas);
      LIS_ProcurarValor(pTabuleiro->pModelosPecas, nome);
      LIS_ObterValor(pTabuleiro->pModelosPecas, (void**) &pModelo);
      
      pPeca->pModelo = pModelo;
      pPeca->time = time;

      *ppPeca = pPeca;
   }

   TAB_tpCondRet CriarPegadasDaPecaNaCasa(TAB_tpMatriz *pTabuleiro, tpCasa *pCasa)
   {
      TAB_tpCondRet condRet;
      LIS_tppLista pPassos;
      int estaVazia;
      
      pPassos = pCasa->pPeca->pModelo->pMovimento->passos;

      LIS_EstaVazia(pPassos, &estaVazia);

      if (estaVazia)
      {
         return TAB_CondRetOK;
      }

      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, NORTE);
      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, ESTE);
      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, SUL);
      SeguirPassosDaPeca(pTabuleiro, pPassos, pCasa->pPeca, OESTE);

      return TAB_CondRetOK;
   }

   TAB_tpCondRet SeguirPassosDaPeca(TAB_tpMatriz *pTabuleiro, LIS_tppLista pPassos,
      tpPeca *pPeca, TAB_tpDirecao orientacao)
   {
      TAB_tpCondRet tabCondRet;
      LIS_tpCondRet lisCondRet = LIS_CondRetOK;
    
      LIS_IrInicioLista(pPassos);
      while (lisCondRet == LIS_CondRetOK)
      {
         TAB_tpPasso *pPasso;
         LIS_ObterValor(pPassos, (void **) &pPasso);
         
         tabCondRet = SeguirPassoDaPeca(pTabuleiro, pPasso, pPeca, orientacao);
         
         if (tabCondRet != TAB_CondRetOK)
         {
            break;
         }

         lisCondRet = LIS_AvancarElementoCorrente(pPassos, 1);
      }

      if (pPeca->pModelo->pMovimento->tipo == VOA && tabCondRet == TAB_CondRetOK)
      {
         InserirPegadaDaPecaNaCasaAtual(pTabuleiro, pPeca, NULL);
      }

      return TAB_CondRetOK;

   }


   TAB_tpCondRet SeguirPassoDaPeca(TAB_tpMatriz *pTabuleiro,
      TAB_tpPasso *pPasso, tpPeca *pPeca, TAB_tpDirecao orientacao)
   {
      TAB_tpDirecao direcao;
      tpPegada *pPegAnt = NULL;
      int i;

      direcao = DirecaoOrientadaPara(pPasso->direcao, orientacao);
      for (i = 0; i < pPasso->quantidade; i++)
      {
         TAB_tpCondRet condRet;
         condRet = IrPara(pTabuleiro, direcao);
         if (condRet != TAB_CondRetOK)
         {
            // chegou no final do tabuleiro
            return TAB_CondRetNaoEhNo;
         }

         if (pPeca->pModelo->pMovimento->tipo == ANDA)
         {
            InserirPegadaDaPecaNaCasaAtual(pTabuleiro, pPeca, pPegAnt);
         }
      }
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
      pPegAnt = pPegada;
   }


/***************************************************************************
*
*  $FC Função: MAT Ir para nó genérico.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção apontada
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*     direcao - representa a direção que o nó corrente navegará.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
*  ****/

   TAB_tpCondRet IrPara(TAB_tpMatriz *pMatriz , TAB_tpDirecao direcao)
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
   TAB_tpCondRet InicializarMatriz(TAB_tpMatriz * pMatriz , int Linhas , int Colunas )
   {
	   int x, y;
	   TAB_tpCondRet Cond;
      tpCasa *pCasa;
      
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
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(NORTE)   , NomeDaCasa(x, y), NomeDaCasa(x, y-1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(ESTE)    , NomeDaCasa(x, y), NomeDaCasa(x+1, y));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(SUL)     , NomeDaCasa(x, y), NomeDaCasa(x, y+1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(OESTE)   , NomeDaCasa(x, y), NomeDaCasa(x-1, y));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(NORDESTE), NomeDaCasa(x, y), NomeDaCasa(x+1, y-1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(SUDESTE) , NomeDaCasa(x, y), NomeDaCasa(x+1, y+1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(SUDOESTE), NomeDaCasa(x, y), NomeDaCasa(x-1, y+1));
            GRA_InserirAresta(pMatriz->pGrafo, DirecaoComoString(NOROESTE), NomeDaCasa(x, y), NomeDaCasa(x-1, y-1));
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
      nome[0] = y + 'A';
      nome[1] = x + '1';
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


   
   int CompararPegadas(void *pPonteiro1, void *pPonteiro2)
   {
      tpPegada *pPegada1 = (tpPegada*) pPonteiro1;
      tpPegada *pPegada2 = (tpPegada*) pPonteiro2;
   
      // TODO: implementar corretamente
      return 1;
   }

   int CompararNomeModeloPeca(void *pValor1, void *pValor2)
   {
      tpModeloPeca *pModelo1 = (tpModeloPeca*) pValor1;
      char *nomeProcurado = (char*) pValor2;

      return strcmp(pModelo1->nome, nomeProcurado);
   }

   TAB_tpDirecao DirecaoOrientadaPara(TAB_tpDirecao direcao, TAB_tpDirecao orientacao)
   {
      return (TAB_tpDirecao) (((int) direcao + (int) orientacao) % TOTAL_DIRECOES);
   }

/********** Fim do módulo de implementação: Módulo matriz **********/