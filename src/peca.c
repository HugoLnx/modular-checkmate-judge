/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              PECA.C
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
#include <string.h>
#include "lista.h"
#include "peca.h"
#include "mem_manager.h"


#define PECA_OWN
#include "peca.h"
#undef PECA_OWN

typedef struct PEC_stPeca {
   MPEC_tppModeloPeca pModelo;
   PEC_tpTimePeca time;
} tpPeca;

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, MPEC_tppModeloPeca pModelo, PEC_tpTimePeca time)
{
   tpPeca *pPeca;
   MEM_Alloc(sizeof(tpPeca), (void**)&pPeca);

   pPeca->pModelo = pModelo;
   pPeca->time = time;

   *ppPeca = (PEC_tppPeca)pPeca;

   return PEC_CondRetOK;
}


PEC_tpCondRet PEC_DestruirPeca(PEC_tppPeca *ppPeca)
{
   tpPeca* pPeca = (tpPeca*)*ppPeca;
   if (pPeca == NULL)
   {
      return PEC_CondRetOK;
   }

   MPEC_DestruirModeloPeca(&pPeca->pModelo);
   MEM_Free(pPeca);

   *ppPeca = NULL;

   return PEC_CondRetOK;

}


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

/********** Fim do módulo de implementação: Módulo matriz **********/