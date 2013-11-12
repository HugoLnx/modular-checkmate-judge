/***************************************************************************
*
*  Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              tabuleiro.c
*  Letras identificadoras:      TAB
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Matriz adaptada para ser tabuleiro.
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
*  Tipo de dados: TAB estrutura principal do tabuleiro
***********************************************************************/
   typedef struct TAB_stTabuleiro {
         GRA_tppGrafo pGrafo;
         /* - Valem as assertivas estruturais do grafo
          * - Dado 2 casas c1 e c2, se c1 tem uma aresta representando a direção
          * d apontando para c2, então c2 tem uma aresta representando a direção
          * oposta à d apontando para c1.
          * - Grafo nunca estará vazio.
          */

         void (*destruirValor)(void *pValor);
   } tpTabuleiro;


/***** Protótipos das funções encapuladas no módulo *****/

   static TAB_tpCondRet InicializarTabuleiro(TAB_tppTabuleiro pTabuleiro);

   static TAB_tpCondRet CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro,
      void (*destruirValor)(void *pValor));

   static char* DirecaoComoString(DIR_tpDirecao direcao);

   static char* NomeDaCasa(int x, int y);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*  Função: TAB Criar tabuleiro
*  ****/
   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro,
      void (*destruirValor)(void *pValor))
   {
      TAB_tpCondRet condRet;

     condRet = CriarTabuleiro(ppTabuleiro, destruirValor);
     if (condRet != TAB_CondRetOK)
     {
        return condRet;
     }

     return InicializarTabuleiro(*ppTabuleiro);
   }


/***************************************************************************
*  Função: TAB Destruir tabuleiro
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


/***************************************************************************
*  Função: TAB Copiar tabuleiro
*  ****/
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


/***************************************************************************
*  Função: TAB Ir casa
*  ****/
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


/***************************************************************************
*  Função: TAB Ir para
*  ****/
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


/***************************************************************************
*  Função: TAB Alterar valor
*  ****/
   TAB_tpCondRet TAB_AlterarValor(TAB_tppTabuleiro pTabuleiro, void *pValor)
   {
      GRA_AlterarValorCorrente(pTabuleiro->pGrafo, pValor);
      return TAB_CondRetOK;
   }


/***************************************************************************
*  Função: TAB Obter valor
*  ****/
   TAB_tpCondRet TAB_ObterValor(TAB_tppTabuleiro pTabuleiro, void **ppValor)
   {
      if (pTabuleiro == NULL)
      {
         return TAB_CondRetTabuleiroNaoExiste;
      }
      GRA_ObterValorCorrente(pTabuleiro->pGrafo, ppValor);
      return TAB_CondRetOK;
   }



/***************************************************************************
*  Função: TAB Percorrer casas
*  ****/
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


/***************************************************************************
*  Função: TAB Nome da casa
*  ****/
   TAB_tpCondRet TAB_NomeDaCasa(int x, int y, char **pNome)
   {
      char *nome;

      if (x >= LARGURA || x < 0 || y >= ALTURA || y < 0)
      {
         *pNome = NULL;
         return TAB_CondRetOK;
      }

      MEM_Alloc(sizeof(char)*3, (void **) &nome);
      if (nome == NULL)
      {
         return TAB_CondRetFaltouMemoria;
      }
      nome[0] = x + 'A';
      nome[1] = y + '1';
      nome[2] = 0;

      *pNome = nome;
      return TAB_CondRetOK;
   }


/***************************************************************************
*  Função: TAB Inicializar tabuleiro
*  ****/
   TAB_tpCondRet InicializarTabuleiro(TAB_tppTabuleiro pTabuleiro)
   {
	   int x, y;

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

/*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
*  Função: TAB Direção como string
*  ****/
   char* DirecaoComoString(DIR_tpDirecao direcao)
   {
      char *dirStr;
      DIR_DirecaoComoString(direcao, &dirStr);
      return dirStr;
   }


   
/***************************************************************************
*  Função: TAB Criar tabuleiro
*  ****/
   TAB_tpCondRet CriarTabuleiro(TAB_tppTabuleiro *ppTabuleiro, void (*destruirValor)(void *pValor))
   {
	   TAB_tppTabuleiro pTabuleiro;
      GRA_tpCondRet graCondRet;
	  
      MEM_Alloc(sizeof(tpTabuleiro), (void **) &pTabuleiro);
      if (pTabuleiro == NULL)
      {
         return TAB_CondRetFaltouMemoria ;
      }

      graCondRet = GRA_CriarGrafo(&pTabuleiro->pGrafo, destruirValor);
      if (graCondRet == GRA_CondRetFaltouMemoria)
      {
         return TAB_CondRetFaltouMemoria;
      }
      pTabuleiro->destruirValor = destruirValor;

	  *ppTabuleiro = pTabuleiro;

      return TAB_CondRetOK;
   }


/***************************************************************************
*  Função: TAB Nome da casa
*  ****/
   char* NomeDaCasa(int x, int y)
   {
      char *nome;

      TAB_NomeDaCasa(x, y, &nome);
      
      return nome;
   }



/********** Fim do módulo de implementação: Módulo Tabuleiro **********/