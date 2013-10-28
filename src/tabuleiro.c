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
   tpModeloPeca *pPeca;
   tpTimePeca time;
} tpPeca

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
*  $TC Tipo de dados: MAT Descritor do n� da matriz
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct stNoMatriz {
		 struct stNoMatriz * pNorte ;
               /* Ponteiro para n� adjacente ao norte
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNorte = NULL
			   *   se pNorte do n� X != NULL ent�o pSul de pNorte aponta para n� X */

         struct stNoMatriz * pSul ;
               /* Ponteiro para n� adjacente ao sul
               *
               *$EED Assertivas estruturais
			   *   se pSul do n� X != NULL ent�o pNorte de pSul aponta para n� X */

		 struct stNoMatriz * pEste ;
               /* Ponteiro para n� adjacente � este
               *
               *$EED Assertivas estruturais
			   *   se pEste do n� X != NULL ent�o pOeste de pEste aponta para n� X */

		 struct stNoMatriz * pOeste ;
               /* Ponteiro para n� adjacente � oeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pOeste = NULL
			   *   se pOeste do n� X != NULL ent�o pEste de pOeste aponta para n� X */

		 struct stNoMatriz * pNordeste ;
               /* Ponteiro para n� adjacente � nordeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNordeste = NULL
			   *   se pNordeste do n� X != NULL ent�o pSudoeste de pNordeste aponta para n� X */


		 struct stNoMatriz * pSudeste ;
               /* Ponteiro para n� adjacente � sudeste
               *
               *$EED Assertivas estruturais
			   *   se pSudeste do n� X != NULL ent�o pNoroeste de pSudeste aponta para n� X */


		 struct stNoMatriz * pNoroeste ;
               /* Ponteiro para n� adjacente � noroeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNoroeste = NULL
			   *   se pNoroeste do n� X != NULL ent�o pSudeste de pNoroeste aponta para n� X */


		 struct stNoMatriz * pSudoeste ;
               /* Ponteiro para n� adjacente � sudoeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pSudoeste = NULL
			   *   se pSudoeste do n� X != NULL ent�o pNordeste de pSudoeste aponta para n� X */


         LIS_tppLista Valor ;
               /* Valor do n� */

   } tpNoMatriz ;

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

   tpNoMatriz * CriarNo() ;

   TAB_tpCondRet CriarNoOrigem( TAB_tpMatriz * pMatriz ) ;

   void EsvaziarMatriz( TAB_tpMatriz * pMatriz ) ;

   tpNoMatriz * GetAdjacente( tpNoMatriz * pNo , tpDirecao dir ) ;

   TAB_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoOrigem , int QntLinhas ) ;

   TAB_tpCondRet AddColuna( TAB_tpMatriz * pMatriz ) ;

   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo ) ;
   
   TAB_tpCondRet IrPara( TAB_tpMatriz * pMatriz , tpDirecao direcao );

   TAB_tpCondRet InicializarMatriz(TAB_tpMatriz *pMatriz, int Linhas, int Colunas);

   TAB_tpCondRet CriarMatriz(TAB_tpMatriz **ppMatriz);

   char* NomeDaCasa(int x, int y);

   void DestruirValor(void *pValor);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpMatriz ** ppMatriz)
   {
     CriarMatriz(ppMatriz);
     InicializarMatriz(*ppMatriz, ALTURA, LARGURA);
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
*  Fun��o: MAT Obter valor corrente
*  ****/
   TAB_tpCondRet TAB_ObterValorCorr(TAB_tpMatriz *pMatriz, LIS_tppLista *ppValorParm)
   {

      if (pMatriz == NULL)
      {
         return TAB_CondRetMatrizNaoExiste;
      }

      GRA_ObterValorCorrente(pMatriz->pGrafo, (void **) ppValorParm);

      return TAB_CondRetOK ;

   }



/***************************************************************************
*
*  Fun��o: MAT Atribuir para valor corrente
*  ****/
   TAB_tpCondRet TAB_AtribuirValorCorr(TAB_tpMatriz *pMatriz, LIS_tppLista pValorParm)
   {
      if (pMatriz == NULL)
      {
         return TAB_CondRetMatrizNaoExiste;
      }
      GRA_AlterarValorCorrente(pMatriz->pGrafo, pValorParm);

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




   void DestruirValor(void *pValor)
   {
      LIS_DestruirLista((LIS_tppLista) pValor);
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

      GRA_CriarGrafo(&pMatriz->pGrafo, DestruirValor);

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
      
	   if( pMatriz == NULL )
	   {
		   return TAB_CondRetMatrizNaoExiste ;
	   }

      GRA_InserirVertice(pMatriz->pGrafo, NomeDaCasa(0, 0), NULL);
      GRA_TornarCorrenteUmaOrigem(pMatriz->pGrafo);

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            GRA_InserirVertice(pMatriz->pGrafo, NomeDaCasa(x, y), NULL);
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

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/