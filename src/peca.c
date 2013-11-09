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
#include "input_string_parser.h"


typedef struct stMovimento {
   LIS_tppLista passos;
   PEC_tpTipoMovimento tipo;
} PEC_tpMovimento;

typedef struct stModeloPeca {
   PEC_tpMovimento *pMovimento;
   char *nome;
} PEC_tpModeloPeca;

typedef struct stPeca {
   PEC_tpModeloPeca *pModelo;
   PEC_tpTimePeca time;
} PEC_stPeca;

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, char* nome, char* passos, PEC_tpTipoMovimento tipoMovimento)
{
   PEC_stPeca *pPeca;
   PEC_tpModeloPeca *pModeloPeca;
   PEC_tpMovimento *pTipoMovimento;
   LIS_tppLista pPassos;
   MEM_Alloc(sizeof(PEC_stPeca),(void**)&pPeca);
   MEM_Alloc(sizeof(PEC_tpModeloPeca),(void**)&pModeloPeca);
   MEM_Alloc(sizeof(PEC_tpMovimento),(void**)&pTipoMovimento);

   ISP_LerPassos(passos,&pPassos);

   pTipoMovimento->passos = pPassos;
   pTipoMovimento->tipo = tipoMovimento;

   pModeloPeca->nome = nome;
   pModeloPeca->pMovimento = pTipoMovimento;

   pPeca->pModelo = pModeloPeca;

   *ppPeca = (PEC_tppPeca)pPeca;

   return PEC_CondRetOK;
}


PEC_tpCondRet PEC_DestruirPeca(PEC_tppPeca *ppPeca)
{
   PEC_stPeca* pPeca = (PEC_stPeca*)*ppPeca;
   if(pPeca == NULL)
      return PEC_CondRetOK;


   MEM_Free(pPeca->pModelo->nome);
   LIS_DestruirLista(pPeca->pModelo->pMovimento->passos);
   MEM_Free(pPeca->pModelo->pMovimento);
   MEM_Free(pPeca);

   *ppPeca = NULL;

   return PEC_CondRetOK;

}
// TODO [RCS] - PEC_CondRetNaoAlterou, espera que ISP_LerPassos retorne algo diferente de OK para quando não não receber argumentos válidos
PEC_tpCondRet PEC_AlterarPeca(PEC_tppPeca ppPeca, char *novoNome, char *pNovosPassos, PEC_tpTipoMovimento novoTipoMovimento)
{
   LIS_tppLista pPassos;
   LIS_tpCondRet lisCondRet;
   ISP_tpCondRet ispCondRet;

   PEC_stPeca *pPeca = (PEC_stPeca*) ppPeca;
   if(pPeca == NULL)
      return PEC_CondRetPecaNaoExiste;

   MEM_Free(pPeca->pModelo->nome);
   pPeca->pModelo->nome = novoNome;

   lisCondRet = LIS_DestruirLista(pPeca->pModelo->pMovimento->passos);
   if(lisCondRet != LIS_CondRetOK)
      return PEC_CondRetNaoAlterou;
   

   ispCondRet = ISP_LerPassos(pNovosPassos,&pPassos);
   if(ispCondRet != ISP_CondRetOK)
      return PEC_CondRetNaoAlterou;
   

   pPeca->pModelo->pMovimento->passos = pPassos;
   pPeca->pModelo->pMovimento->tipo = novoTipoMovimento;
   
   return PEC_CondRetOK;
}

PEC_tpCondRet PEC_AdicionarTime(PEC_tppPeca ppPeca, PEC_tpTimePeca time)
{
   PEC_stPeca *pPeca = (PEC_stPeca*) ppPeca;
   if(pPeca == NULL)
      return PEC_CondRetPecaNaoExiste;

   pPeca->time = time;

   return PEC_CondRetOK;

}

#define PECA_OWN
#include "peca.h"
#undef PECA_OWN

/********** Fim do módulo de implementação: Módulo matriz **********/