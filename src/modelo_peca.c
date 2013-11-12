/***************************************************************************
*
*  Módulo de definição: MPEC  Modelo de Peça
*
*  Arquivo gerado:              modelo_peca.c
*  Letras identificadoras:      MPEC
*
*	Autores:
*     - hg: Hugo Roque
      - rs: Robert Correa
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Manipulação básica de modelo de peça
*     2       rc       12/nov/2013      Serialização
*
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "modelo_peca.h"
#include "mem_manager.h"
#include "passo.h"


#define MODELO_PECA_OWN
#include "peca.h"
#undef MODELO_PECA_OWN

/***********************************************************************
*  Tipo de dados: MPEC Movimento do modelo
***********************************************************************/
typedef struct stMovimento {
   LIS_tppLista passos;
      /* Valem as assertivas estruturais da lista */

   MPEC_tpTipoMovimento tipo;
} tpMovimento;

/***********************************************************************
*  Tipo de dados: MPEC Modelo de peça
***********************************************************************/
typedef struct MPEC_stModeloPeca {
   tpMovimento *pMovimento;
      /* Valem as assertivas estruturais do movimento */

   char *nome;
      /* Não pode ser nulo */
} tpModeloPeca;

/* Funções exportadas pelo módulo */

/***************************************************************************
*  Função: MPEC Criar modelo de peça
*  ****/
MPEC_tpCondRet MPEC_CriarModeloPeca(MPEC_tppModeloPeca *ppModelo, char* nome, LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento)
{
   tpModeloPeca *pModeloPeca;
   tpMovimento *pTipoMovimento;
   MEM_Alloc(sizeof(tpModeloPeca),(void**)&pModeloPeca);
   MEM_Alloc(sizeof(tpMovimento),(void**)&pTipoMovimento);

   pTipoMovimento->passos = pPassos;
   pTipoMovimento->tipo = tipoMovimento;

   pModeloPeca->nome = nome;
   pModeloPeca->pMovimento = pTipoMovimento;


   *ppModelo = (MPEC_tppModeloPeca) pModeloPeca;

   return MPEC_CondRetOK;
}


/***************************************************************************
*  Função: MPEC Destruir modelo de peça
*  ****/
MPEC_tpCondRet MPEC_DestruirModeloPeca(MPEC_tppModeloPeca *ppModelo)
{
   tpModeloPeca* pModelo = (tpModeloPeca*)*ppModelo;
   if (pModelo == NULL)
   {
      return MPEC_CondRetOK;
   }

   MEM_Free(pModelo->nome);
   LIS_DestruirLista(pModelo->pMovimento->passos);
   MEM_Free(pModelo->pMovimento);

   *ppModelo = NULL;

   return MPEC_CondRetOK;

}


/***************************************************************************
*  Função: MPEC Alterar modelo de peça
*  ****/
MPEC_tpCondRet MPEC_AlterarModeloPeca(MPEC_tppModeloPeca pModeloParm, char *novoNome, LIS_tppLista pPassos, MPEC_tpTipoMovimento novoTipoMovimento)
{
   LIS_tpCondRet lisCondRet;

   tpModeloPeca *pModelo = (tpModeloPeca*) pModeloParm;
   if (pModelo == NULL)
   {
      return MPEC_CondRetModeloNaoExiste;
   }

   MEM_Free(pModelo->nome);
   pModelo->nome = novoNome;

   lisCondRet = LIS_DestruirLista(pModelo->pMovimento->passos);
   if(lisCondRet != LIS_CondRetOK)
   {
      return MPEC_CondRetNaoAlterou;
   }

   pModelo->pMovimento->passos = pPassos;
   pModelo->pMovimento->tipo = novoTipoMovimento;
   
   return MPEC_CondRetOK;
}


/***************************************************************************
*  Função: MPEC Obter nome
*  ****/
MPEC_tpCondRet MPEC_ObterNome(MPEC_tppModeloPeca pModeloParm, char **pNome)
{
   tpModeloPeca *pModelo = (tpModeloPeca*) pModeloParm;

   *pNome = pModelo->nome;

   return MPEC_CondRetOK;
}


/***************************************************************************
*  Função: MPEC Obter passos
*  ****/
MPEC_tpCondRet MPEC_ObterPassos(MPEC_tppModeloPeca pModeloParm, LIS_tppLista *ppPassos)
{
   tpModeloPeca *pModelo = (tpModeloPeca*) pModeloParm;

   if (pModelo == NULL)
   {
      *ppPassos = NULL;
      return MPEC_CondRetModeloNaoExiste;
   }

   *ppPassos = pModelo->pMovimento->passos;
   return MPEC_CondRetOK;
}


/***************************************************************************
*  Função: MPEC Obter tipo
*  ****/
MPEC_tpCondRet MPEC_ObterTipo(MPEC_tppModeloPeca pModeloParm, MPEC_tpTipoMovimento *pTipo)
{
   tpModeloPeca *pModelo = (tpModeloPeca*) pModeloParm;

   if (pModelo == NULL)
   {
      return MPEC_CondRetModeloNaoExiste;
   }
   
   *pTipo = pModelo->pMovimento->tipo;
   return MPEC_CondRetOK;
}


/***************************************************************************
*  Função: MPEC Salvar lista
*  ****/
MPEC_tpCondRet MPEC_SalvarLista(LIS_tppLista ppModelosPeca, FILE *pFile)
{
   int numElementos;
   tpModeloPeca *pModeloPeca;

   LIS_IrInicioLista(ppModelosPeca);
   LIS_NumELementos(ppModelosPeca,&numElementos);

   while(numElementos > 0)
   {
      LIS_ObterValor(ppModelosPeca,(void**)&pModeloPeca);

      MPEC_Salvar(pModeloPeca,pFile);

      if(numElementos != 1)
         fputs("\n",pFile);

      LIS_AvancarElementoCorrente(ppModelosPeca,1);
      numElementos--;
   }

   return MPEC_CondRetOK;
}


/***************************************************************************
*  Função: MPEC Salvar
*  ****/
MPEC_tpCondRet MPEC_Salvar(MPEC_tppModeloPeca pModeloPeca, FILE *pFile)
{
   char *linhaASerEscrita;
   tpModeloPeca *pModelo = (tpModeloPeca*) pModeloPeca;

   if(pModeloPeca != NULL)
   {
      MEM_Alloc(sizeof(char*)*200,(void**)&linhaASerEscrita);

      sprintf(linhaASerEscrita,"%s-%d-",pModelo->nome,pModelo->pMovimento->tipo);
      fputs(linhaASerEscrita,pFile);

      return (MPEC_tpCondRet )PAS_Salvar(pModelo->pMovimento->passos,pFile);
   }
   //rei

   return MPEC_CondRetOK;
   

   
}

/********** Fim do módulo de implementação: Módulo matriz **********/