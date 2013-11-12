/***************************************************************************
*
*  Módulo de definição: MEM  Memory Manager
*
*  Arquivo gerado:              mem_manager.c
*  Letras identificadoras:      MEM
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Usando lista para armazenar os ponteiros para espaços alocados.
*
***************************************************************************/

#include <malloc.h>
#include <stdio.h>

#define MEM_OWN
#include "mem_manager.h"
#undef MEM_OWN

#include "lista.h"

static LIS_tppLista pLista;

/* Protótipos das funções encapsuladas no módulo */

static int CompararPonteiros (void *pointer1, void *pointer2);


/* Funções exportadas pelo módulo */

/***************************************************************************
*  Função: MEM Alloc
*  ****/
MEM_tpCondRet MEM_Alloc(int size, void ** ppResult)
{
   LIS_tpCondRet lisCondRet;

   if (size <= 0)
   {
      return MEM_CondRetTamanhoInvalido;
   }

   if (pLista == NULL)
   {
      lisCondRet = LIS_CriarLista(&pLista, free, CompararPonteiros);

      if (lisCondRet == LIS_CondRetFaltouMemoria)
      {
         return MEM_CondRetFaltouMemoria;
      }
   }
   *ppResult = malloc(size);
   if (ppResult == NULL)
   {
      return MEM_CondRetFaltouMemoria;
   }

   lisCondRet = LIS_InserirElementoApos(pLista, *ppResult);
   if (lisCondRet == LIS_CondRetFaltouMemoria)
   {
      return MEM_CondRetFaltouMemoria;
   }

   return MEM_CondRetOK;
}


/***************************************************************************
*  Função: MEM Free
*  ****/
MEM_tpCondRet MEM_Free(void *pointer)
{
   LIS_IrInicioLista(pLista);
   if (LIS_ProcurarValor(pLista, pointer) == LIS_CondRetOK)
   {
      LIS_ExcluirElemento(pLista);
   }
   return MEM_CondRetOK;
}


/***************************************************************************
*  Função: MEM Liberar toda memória alocada
*  ****/
MEM_tpCondRet MEM_LiberarTodaMemoriaAlocada()
{
   LIS_DestruirLista(pLista);
   pLista = NULL;
   return MEM_CondRetOK;
}

/**** Funções encapsuladas no módulo ****/


/***************************************************************************
*  Função: MEM Comparar ponteiros
*  ****/
int CompararPonteiros(void *pointer1, void *pointer2)
{
   if (pointer1 == pointer2)
   {
      return 0;
   }

   return -1;
}

/********** Fim do módulo de implementação: Módulo Memory Manager **********/