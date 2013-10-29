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
   } TAB_tpMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Direções que o nó pode ter ponteiros para outro nó.
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

/***** Protótipos das funções encapuladas no módulo *****/

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

	  *ppMatriz = pMatriz;

      return TAB_CondRetOK ;

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

/********** Fim do módulo de implementação: Módulo matriz **********/