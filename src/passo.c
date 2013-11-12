/***************************************************************************
*
*  Módulo de definição: PAS  Passo
*
*  Arquivo gerado:              passo.c
*  Letras identificadoras:      PAS
*
*	Autores:
*     - hg: Hugo Roque
      - rc: Robert Correa
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Manipulação básica de passo
*     2       rc       12/nov/2013      Serialização
***************************************************************************/

#include <stdio.h>
#include "mem_manager.h"

#include <string.h>

#define PASSO_OWN
#include "passo.h"
#undef PASSO_OWN


/***********************************************************************
*  Tipo de dados: PAS Passo
***********************************************************************/
typedef struct PAS_stPasso
{
   DIR_tpDirecao direcao;
   int quantidade;
} tpPasso;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*  Função: PAS Criar passo
*  ****/
   PAS_tpCondRet PAS_CriarPasso(PAS_tppPasso *ppPasso, DIR_tpDirecao direcao, int quantidade)
   {
      tpPasso *pPasso;
      MEM_Alloc(sizeof(tpPasso), (void**) &pPasso);
      if (pPasso == NULL)
      {
         return PAS_CondRetFaltouMemoria;
      }
      pPasso->direcao = direcao;
      pPasso->quantidade = quantidade;

      *ppPasso = (PAS_tppPasso) pPasso;

      return PAS_CondRetOK;
   }


/***************************************************************************
*  Função: PAS Destruir passo
*  ****/
   PAS_tpCondRet PAS_DestruirPasso(PAS_tppPasso *ppPasso)
   {
      if (ppPasso == NULL || *ppPasso == NULL)
      {
         return PAS_CondRetPassoNaoExiste;
      }

      MEM_Free(*ppPasso);

      return PAS_CondRetOK;
   }


/***************************************************************************
*  Função: PAS Comparar passos
*  ****/
   PAS_tpCondRet PAS_CompararPassos(PAS_tppPasso pPassoParm1, PAS_tppPasso pPassoParm2, int *pResposta)
   {
      tpPasso *pPasso1 = (tpPasso*) pPassoParm1;
      tpPasso *pPasso2 = (tpPasso*) pPassoParm2;
      *pResposta = pPasso1->direcao == pPasso2->direcao 
                && pPasso1->quantidade == pPasso2->quantidade;

      return PAS_CondRetOK;
   }


/***************************************************************************
*  Função: PAS Obter quantidade
*  ****/
   PAS_tpCondRet PAS_ObterQuantidade(PAS_tppPasso pPassoParm, int *pQuantidade)
   {
      tpPasso *pPasso = (tpPasso*) pPassoParm;

      if (pPasso == NULL)
      {
         *pQuantidade = NULL;
         return PAS_CondRetPassoNaoExiste;
      }
   
      *pQuantidade = pPasso->quantidade;

      return PAS_CondRetOK;
   }


/***************************************************************************
*  Função: PAS É infinito
*  ****/
   PAS_tpCondRet PAS_EhInfinito(PAS_tppPasso pPassoParm, int *pEhInfinito)
   {
      tpPasso *pPasso = (tpPasso*) pPassoParm;

      if (pPasso == NULL)
      {
         *pEhInfinito = 0;
         return PAS_CondRetPassoNaoExiste;
      }
   
      *pEhInfinito = pPasso->quantidade == 0;
      return PAS_CondRetOK;
   }


/***************************************************************************
*  Função: PAS Obter direção
*  ****/
   PAS_tpCondRet PAS_ObterDirecao(PAS_tppPasso pPassoParm, DIR_tpDirecao *pDirecao)
   {
      tpPasso *pPasso = (tpPasso*) pPassoParm;

      if (pPasso == NULL)
      {
         *pDirecao == NULL;
         return PAS_CondRetPassoNaoExiste;
      }
   
      *pDirecao = pPasso->direcao;

      return PAS_CondRetOK;
   }


/***************************************************************************
*  Função: PAS Salvar
*  ****/
   PAS_tpCondRet PAS_Salvar(LIS_tppLista ppPassos, FILE* pFile)
   {
      int numElementos;
      tpPasso *pPasso;
      char *linhaASerEscrita;
      char *direcao;

      LIS_IrInicioLista(ppPassos);
      LIS_NumELementos(ppPassos,&numElementos);

      MEM_Alloc(sizeof(char)*200,(void**)&linhaASerEscrita);
      MEM_Alloc(sizeof(char)*50,(void**)&direcao);

      
      while(numElementos > 0)
      {
         LIS_ObterValor(ppPassos, (void**)&pPasso);

         DIR_DirecaoComoString(pPasso->direcao,&direcao);

         if(numElementos == 1)
         {
            sprintf(linhaASerEscrita,"[%d]%s",pPasso->quantidade,direcao);
         }
         else
         {
            sprintf(linhaASerEscrita,"[%d]%s_",pPasso->quantidade,direcao);
         }

         fputs(linhaASerEscrita,pFile);
         LIS_AvancarElementoCorrente(ppPassos,1);
         numElementos--;
      }
      
      return PAS_CondRetOK;
   }

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Passo **********/
