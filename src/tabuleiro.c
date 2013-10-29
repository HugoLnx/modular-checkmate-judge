/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
***************************************************************************/

#include <stdio.h>
#include "lista.h"
#include "grafo.h"
#include "mem_manager.h"

#define TABULEIRO_OWN
#include "tabuleiro.h"
#undef TABULEIRO_OWN

typedef enum {
   ANDA = 0,
   VOA = 1
} tpTipoMovimento;


typedef enum {
   ALIADA = 0,
   INIMIGA = 1
} tpTimePeca;

typedef struct stMovimento {
   LIS_tppLista passos;
   tpTipoMovimento tipo;
} tpMovimento;

typedef struct stModeloPeca {
   tpMovimento *pMovimento;
   char *nome;
} tpModeloPeca;

typedef struct stPeca {
   tpModeloPeca *pModelo;
   tpTimePeca time;
} tpPeca;

typedef struct stPegada {
   tpPeca *pPeca;
   struct stPegada *pAnterior;
} tpPegada;

typedef struct stCasa {
   tpPeca *pPeca;
   LIS_tppLista pegadas;
} tpCasa;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabe�a de uma matriz
*
*
*  $ED Descri��o do tipo
*     A cabe�a da matriz � o ponto de acesso para uma determinada matriz.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*
***********************************************************************/

   typedef struct stMatriz {
         GRA_tppGrafo pGrafo;
   } TAB_tpMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Dire��es que o n� pode ter ponteiros para outro n�.
*
*
***********************************************************************/
   typedef enum {
	    NORTE = 0,
		 
		 ESTE = 1,
       
		 SUL = 2,

		 OESTE = 3,

		 NORDESTE = 4,

		 SUDESTE = 5,

		 SUDOESTE = 6,

		 NOROESTE = 7
   } tpDirecao ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   TAB_tpCondRet CriarNoOrigem( TAB_tpMatriz * pMatriz ) ;

   void EsvaziarMatriz( TAB_tpMatriz * pMatriz ) ;

   TAB_tpCondRet AddColuna( TAB_tpMatriz * pMatriz ) ;
   
   TAB_tpCondRet IrPara( TAB_tpMatriz * pMatriz , tpDirecao direcao );

   TAB_tpCondRet InicializarMatriz(TAB_tpMatriz *pMatriz, int Linhas, int Colunas);

   TAB_tpCondRet CriarMatriz(TAB_tpMatriz **ppMatriz);

   char* NomeDaCasa(int x, int y);

   tpCasa* CriarCasa();
   
   void DestroiMovimento(void *pValor);
   
   void DestruirModeloPeca(void *pValor);
   
   void DestruirPeca(void *pValor);
   
   void DestruirCasa(void *pValor);
   
   void DestruirPegada(void *pValor);

   int CompararPegadas(void *pPonteiro1, void *pPonteiro2);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpMatriz ** ppMatriz)
   {
     CriarMatriz(ppMatriz);
     return InicializarMatriz(*ppMatriz, ALTURA, LARGURA);
   }

/***************************************************************************
*
*  Fun��o: MAT Destruir matriz
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
*  Fun��o: MAT Ir para n� ao norte.
*  ****/
   TAB_tpCondRet TAB_IrNoNorte(TAB_tpMatriz *pMatriz)
   {
	   return IrPara( pMatriz , NORTE );
   }



/***************************************************************************
*
*  Fun��o: MAT Ir para n� ao sul.
*  ****/
   TAB_tpCondRet TAB_IrNoSul( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUL );
   }



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � este.
*  ****/
   TAB_tpCondRet TAB_IrNoEste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , ESTE );
   }



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � oeste.
*  ****/
   TAB_tpCondRet TAB_IrNoOeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , OESTE );
   }




/***************************************************************************
*
*  Fun��o: MAT Ir para n� � nordeste.
*  ****/
   TAB_tpCondRet TAB_IrNoNordeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORDESTE );
   }




/***************************************************************************
*
*  Fun��o: MAT Ir para n� � sudeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDESTE );
   }




/***************************************************************************
*
*  Fun��o: MAT Ir para n� � sudoeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudoeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDOESTE );
   }




/***************************************************************************
*
*  Fun��o: MAT Ir para n� � noroeste.
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

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

   char* DirecaoComoString(tpDirecao direcao)
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


/***************************************************************************
*
*  $FC Fun��o: MAT Ir para n� gen�rico.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o apontada
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*     direcao - representa a dire��o que o n� corrente navegar�.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
*  ****/

   TAB_tpCondRet IrPara(TAB_tpMatriz *pMatriz , tpDirecao direcao)
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
*  $FC Fun��o: TAB Criar matriz
*
*  $ED Descri��o da fun��o
*     Cria uma nova matriz vazia.
*     Caso j� exista uma matriz, esta ser� destru�da.
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

	  *ppMatriz = pMatriz;

      return TAB_CondRetOK ;

   }


   


/***********************************************************************
*
*  $FC Fun��o: TAB Inicializar a matriz
*
*  $EP Par�metros
*     $P pMatriz - matriz que ser� inicializada.
*                    Este par�metro � passado por refer�ncia.
*     $P Linhas - quantidade de linhas que a matriz ter�.
*     $P Colunas - quantidade de colunas que a matriz ter�.
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
            if(x >= 7 && y >= 7) {
               int lol = 90;
            }
            GRA_InserirVertice(pMatriz->pGrafo, NomeDaCasa(x, y), CriarCasa());
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

   tpCasa* CriarCasa()
   {
      tpCasa *pCasa;
      MEM_Alloc(sizeof(tpCasa), (void **) &pCasa);
      LIS_CriarLista(&pCasa->pegadas, DestruirPegada, CompararPegadas);
      pCasa->pPeca = NULL;
   
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

      DestruirModeloPeca(pPeca->pModelo);
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

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/