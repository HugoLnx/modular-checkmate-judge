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
#include "direcao.h"

#include <string.h>

#define TABULEIRO_OWN
#include "tabuleiro.h"
#undef TABULEIRO_OWN

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

   typedef struct TAB_stTabuleiro {
         GRA_tppGrafo pGrafo;
         void (*destruirValor)(void *pValor);
   } tpTabuleiro;

   typedef struct TAB_stTabuleiro* TAB_tppTabuleiro;


/***** Protótipos das funções encapuladas no módulo *****/

   static TAB_tpCondRet InicializarTabuleiro(TAB_tppTabuleiro pTabuleiro);

   static TAB_tpCondRet CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro,
      void (*destruirValor)(void *pValor));

   static char* DirecaoComoString(DIR_tpDirecao direcao);

   static char* NomeDaCasa(int x, int y);

/*****  Código das funções exportadas pelo módulo  *****/

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro,
      void (*destruirValor)(void *pValor))
   {
     CriarTabuleiro(ppTabuleiro, destruirValor);
     return InicializarTabuleiro(*ppTabuleiro);
   }

/***************************************************************************
*
*  Função: MAT Destruir matriz
*  ****/
   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro *ppTabuleiro)
   {
		TAB_tppTabuleiro pTabuleiro;
      
		if (ppTabuleiro == NULL || *ppTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste ;
		}
      
		pTabuleiro = *ppTabuleiro;
         
		GRA_DestruirGrafo(&pTabuleiro->pGrafo);
		MEM_Free(pTabuleiro);
		*ppTabuleiro = NULL;

		return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_CopiarTabuleiro(TAB_tppTabuleiro pTabuleiro, TAB_tppTabuleiro *ppCopia)
   {
      TAB_tppTabuleiro pCopia = NULL;
      int x, y;

      TAB_CriarTabuleiro(&pCopia, pTabuleiro->destruirValor);

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            void *pValor;
            TAB_IrCasa(pTabuleiro, NomeDaCasa(x, y));
            TAB_IrCasa(pCopia, NomeDaCasa(x, y));
            GRA_ObterValorCorrente(pTabuleiro->pGrafo, (void **) &pValor);
            GRA_AlterarValorCorrente(pCopia->pGrafo, pValor);
         }
      }

      *ppCopia = pCopia;

      return TAB_CondRetOK;
   }


   TAB_tpCondRet TAB_IrCasa(TAB_tppTabuleiro pTabuleiro, char *nome)
   {
      GRA_tpCondRet condRet;

      if (pTabuleiro == NULL)
      {
         return TAB_CondRetTabuleiroNaoExiste;
      }
      
      condRet = GRA_IrParaAOrigem(pTabuleiro->pGrafo, nome);
      if (condRet != GRA_CondRetOK)
      {
         return TAB_CondRetNaoEhCasa;
      }

      return TAB_CondRetOK;
   }


   TAB_tpCondRet TAB_IrPara(TAB_tppTabuleiro pTabuleiro , DIR_tpDirecao direcao)
   {
      GRA_tpCondRet condRet;
      GRA_tppGrafo pGrafo;
      char *dirStr;

     if (pTabuleiro == NULL)
     {
        return TAB_CondRetTabuleiroNaoExiste;
     }

     pGrafo = pTabuleiro->pGrafo;
     DIR_DirecaoComoString(direcao, &dirStr);
     condRet = GRA_SeguirPelaAresta(pGrafo, dirStr);
     
     if (condRet != GRA_CondRetOK)
     {
        return TAB_CondRetNaoEhCasa;
     }

	  return TAB_CondRetOK ;
   }


   TAB_tpCondRet TAB_AlterarValor(TAB_tppTabuleiro pTabuleiro, void *pValor)
   {
      GRA_AlterarValorCorrente(pTabuleiro->pGrafo, pValor);
      return TAB_CondRetOK;
   }

   


   TAB_tpCondRet TAB_ObterValor(TAB_tppTabuleiro pTabuleiro, void **ppValor)
   {
      GRA_ObterValorCorrente(pTabuleiro->pGrafo, ppValor);
      return TAB_CondRetOK;
   }

/*****  Código das funções encapsuladas no módulo  *****/

   char* DirecaoComoString(DIR_tpDirecao direcao)
   {
      char *dirStr;
      DIR_DirecaoComoString(direcao, &dirStr);
      return dirStr;
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
   TAB_tpCondRet CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro, void (*destruirValor)(void *pValor))
   {
	   TAB_tppTabuleiro pTabuleiro;

      if (ppTabuleiro != NULL && *ppTabuleiro != NULL)
      {
         TAB_DestruirTabuleiro(ppTabuleiro);
      }
	  
      MEM_Alloc(sizeof(tpTabuleiro), (void **) &pTabuleiro);
      if (pTabuleiro == NULL)
      {
         return TAB_CondRetFaltouMemoria ;
      }

      GRA_CriarGrafo(&pTabuleiro->pGrafo, destruirValor);
      pTabuleiro->destruirValor = destruirValor;

	  *ppTabuleiro = pTabuleiro;

      return TAB_CondRetOK;
   }
   

   TAB_tpCondRet TAB_PercorrerCasas(TAB_tppTabuleiro pTabuleiro, int (*fazerNaCasa)(TAB_tppTabuleiro pTabuleiro, char *nome))
   {
      int x, y, continuar = 1;

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            void *pValor;
            char *nome = NomeDaCasa(x, y);
            TAB_IrCasa(pTabuleiro, nome);
            TAB_ObterValor(pTabuleiro, &pValor);
            continuar = fazerNaCasa(pTabuleiro, nome);

            if (!continuar)
            {
               return TAB_CondRetOK;
            }
         }
      }

      return TAB_CondRetOK;
   }

   TAB_tpCondRet TAB_NomeDaCasa(int x, int y, char **pNome)
   {
      char *nome;

      if (x >= LARGURA || x < 0 || y >= ALTURA || y < 0)
      {
         *pNome = NULL;
         return TAB_CondRetOK;
      }

      MEM_Alloc(sizeof(char)*3, (void **) &nome);
      nome[0] = x + 'A';
      nome[1] = y + '1';
      nome[2] = 0;

      *pNome = nome;
      return TAB_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: TAB Inicializar a matriz
*
*  $EP Parâmetros
*     $P pTabuleiro - matriz que será inicializada.
*                    Este parâmetro é passado por referência.
*     $P Linhas - quantidade de linhas que a matriz terá.
*     $P Colunas - quantidade de colunas que a matriz terá.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet InicializarTabuleiro(TAB_tppTabuleiro pTabuleiro)
   {
	   int x, y;

	   if( pTabuleiro == NULL )
	   {
		   return TAB_CondRetTabuleiroNaoExiste ;
	   }

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            char *nome = NomeDaCasa(x, y);
            GRA_InserirVertice(pTabuleiro->pGrafo, nome, NULL);
            GRA_TornarCorrenteUmaOrigem(pTabuleiro->pGrafo);
         }
      }

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            char *nome;
            nome = NomeDaCasa(x, y);
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(NORTE)   , nome, NomeDaCasa(x, y-1));
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(ESTE)    , nome, NomeDaCasa(x+1, y));
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(SUL)     , nome, NomeDaCasa(x, y+1));
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(OESTE)   , nome, NomeDaCasa(x-1, y));
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(NORDESTE), nome, NomeDaCasa(x+1, y-1));
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(SUDESTE) , nome, NomeDaCasa(x+1, y+1));
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(SUDOESTE), nome, NomeDaCasa(x-1, y+1));
            GRA_InserirAresta(pTabuleiro->pGrafo, DirecaoComoString(NOROESTE), nome, NomeDaCasa(x-1, y-1));
         }
      }

      GRA_IrParaAOrigem(pTabuleiro->pGrafo, NomeDaCasa(0,0));

	   return TAB_CondRetOK ;
   }

   char* NomeDaCasa(int x, int y)
   {
      char *nome;

      TAB_NomeDaCasa(x, y, &nome);
      
      return nome;
   }



/********** Fim do módulo de implementação: Módulo matriz **********/