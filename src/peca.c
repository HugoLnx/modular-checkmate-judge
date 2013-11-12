/***************************************************************************
*
*  M�dulo de defini��o: PEC  Pe�a
*
*  Arquivo gerado:              peca.c
*  Letras identificadoras:      PEC
*
*	Autores:
*     - hg: Hugo Roque
        rc: Robert Correa
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Fun��es para manipula��o da pe�a.
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "peca.h"
#include "mem_manager.h"


#define PECA_OWN
#include "peca.h"
#undef PECA_OWN


/***********************************************************************
*  Tipo de dados: PEC Pe�a
***********************************************************************/
typedef struct PEC_stPeca {
   MPEC_tppModeloPeca pModelo;
   /* Valem as assertivas estruturais do modelo */

   PEC_tpTimePeca time;
} tpPeca;


/***************************************************************************
*  Fun��o: PEC Criar pe�a
*  ****/
PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, MPEC_tppModeloPeca pModelo, PEC_tpTimePeca time)
{
   tpPeca *pPeca;
   MEM_Alloc(sizeof(tpPeca), (void**)&pPeca);

   pPeca->pModelo = pModelo;
   pPeca->time = time;

   *ppPeca = (PEC_tppPeca)pPeca;

   return PEC_CondRetOK;
}


/***************************************************************************
*  Fun��o: PEC Destruir pe�a
*  ****/
PEC_tpCondRet PEC_DestruirPeca(PEC_tppPeca *ppPeca)
{
   tpPeca* pPeca = (tpPeca*)*ppPeca;
   if (pPeca == NULL)
   {
      return PEC_CondRetOK;
   }

   MEM_Free(pPeca);

   *ppPeca = NULL;

   return PEC_CondRetOK;
}


/***************************************************************************
*  Fun��o: PEC Criar rei
*  ****/
PEC_tpCondRet PEC_CriarRei(PEC_tppPeca *ppPeca)
{
   return PEC_CriarPeca(ppPeca, NULL, ALIADA);
}


/***************************************************************************
*  Fun��o: PEC Destruir rei
*  ****/
PEC_tpCondRet PEC_DestruirRei(PEC_tppPeca *ppPeca)
{
   return PEC_DestruirPeca(ppPeca);
}


/***************************************************************************
*  Fun��o: PEC Alterar modelo pe�a
*  ****/
PEC_tpCondRet PEC_AlterarModeloPeca(PEC_tppPeca ppPeca, MPEC_tppModeloPeca pNovoModelo)
{
   LIS_tpCondRet lisCondRet;

   tpPeca *pPeca = (tpPeca*) ppPeca;
   if (pPeca == NULL)
   {
      return PEC_CondRetPecaNaoExiste;
   }

   pPeca->pModelo = pNovoModelo;
   
   return PEC_CondRetOK;
}


/***************************************************************************
*  Fun��o: PEC � o rei
*  ****/
PEC_tpCondRet PEC_EhORei(PEC_tppPeca pPecaParm, int *ehRei)
{
   tpPeca *pPeca = (tpPeca*) pPecaParm;

   if (pPeca == NULL)
   {
      *ehRei = 0;
   }
   else
   {
      *ehRei = pPeca->pModelo == NULL;
   }

   return PEC_CondRetOK;

}


/***************************************************************************
*  Fun��o: PEC Obter modelo
*  ****/
PEC_tpCondRet PEC_ObterModelo(PEC_tppPeca pPecaParm, MPEC_tppModeloPeca *ppModelo)
{
   tpPeca *pPeca = (tpPeca*) pPecaParm;

   if (pPecaParm == NULL)
   {
      *ppModelo = NULL;
      return PEC_CondRetPecaNaoExiste;
   }

   *ppModelo = pPeca->pModelo;
   return PEC_CondRetOK;
}


/***************************************************************************
*  Fun��o: PEC Obter time
*  ****/
PEC_tpCondRet PEC_ObterTime(PEC_tppPeca pPecaParm, PEC_tpTimePeca *pTime)
{
   tpPeca *pPeca = (tpPeca*) pPecaParm;

   if (pPecaParm == NULL)
   {
      return PEC_CondRetPecaNaoExiste;
   }

   *pTime = pPeca->time;
   return PEC_CondRetOK;
}


/***************************************************************************
*  Fun��o: PEC Salvar pe�a
*  ****/
PEC_tpCondRet PEC_SalvarPeca(PEC_tppPeca ppPeca, FILE* pFile)
{
   char *linhaASerEscrita;
   
   tpPeca *pPeca = (tpPeca*) ppPeca;
   if (pPeca == NULL)
   {
      return PEC_CondRetPecaNaoExiste;
   }

   MEM_Alloc(sizeof(char*)*200,(void**)&linhaASerEscrita);
   
   sprintf(linhaASerEscrita,"%d-",(int)pPeca->time);
   fputs(linhaASerEscrita,pFile);

   return (PEC_tpCondRet)MPEC_Salvar(pPeca->pModelo,pFile);
}

/********** Fim do m�dulo de implementa��o: M�dulo Pe�a **********/