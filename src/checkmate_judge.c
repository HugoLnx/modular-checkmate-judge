/***************************************************************************
*
*  M�dulo de defini��o: JUD - Checkmate Judge
*
*  Arquivo gerado:              checkmate_judge.c
*  Letras identificadoras:      JUD
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Verifica��es que envolvem locomo��o de pe�as
*
***************************************************************************/

#include <stdio.h>
#include "analise_partida.h"
#include <string.h>

#define CHECKMATE_JUDGE_OWN
#include "checkmate_judge.h"
#undef CHECKMATE_JUDGE_OWN


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   JUD_tpCondRet VerificarCheckmate(APAR_tppAnalise pAnalise, int *pResposta);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
   
/***************************************************************************
*  Fun��o: JUD Eh checkmate
*  ****/
   JUD_tpCondRet JUD_EhCheckmate(PAR_tppPartida pPartida, int *pResposta)
   {
      JUD_tpCondRet condRet;
      APAR_tppAnalise pAnalise;
      APAR_tpCondRet aparCondRet;

      pAnalise = NULL;
      aparCondRet = APAR_CriarAnalise(&pAnalise, pPartida);
      if (aparCondRet == APAR_CondRetFaltouMemoria)
      {
         return JUD_CondRetFaltouMemoria;
      }

      if (aparCondRet != APAR_CondRetOK)
      {
         return JUD_CondRetNaoFoiPossivelVerificar;
      }

      condRet = VerificarCheckmate(pAnalise, pResposta);

      APAR_DestruirAnalise(&pAnalise);

      return condRet;
   }

   
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

   
/***********************************************************************
*
*  Fun��o: JUD Verificar checkmate
*
*  Descri��o:
*    Fun��o com a l�gica de verifica��o de checkmate apartir de uma
*    analise de partida.
*
***********************************************************************/
   JUD_tpCondRet VerificarCheckmate(APAR_tppAnalise pAnalise, int *pResposta)
   {
      DIR_tpDirecao DIRECOES[TOTAL_DIRECOES] = {
         NORTE, NORDESTE, ESTE, SUDESTE,
         SUL, SUDOESTE, OESTE, NOROESTE
      };
      int i;
      int temPegadaInimiga;
      APAR_tpCondRet aparCondRet;
      
      aparCondRet = APAR_IrCasaRei(pAnalise);
      if (aparCondRet != JUD_CondRetOK)
      {
         return JUD_CondRetNaoFoiPossivelVerificar;
      }

      aparCondRet = APAR_AlgumaPegadaInimiga(pAnalise, &temPegadaInimiga);
      if (aparCondRet != JUD_CondRetOK)
      {
         return JUD_CondRetNaoFoiPossivelVerificar;
      }
      if (!temPegadaInimiga)
      {
         *pResposta = 0;
         return JUD_CondRetOK;
      }
   
      for (i = 0; i < TOTAL_DIRECOES; i++)
      {
         DIR_tpDirecao direcao = DIRECOES[i];
         
         aparCondRet = APAR_IrCasaRei(pAnalise);
         if (aparCondRet != JUD_CondRetOK)
         {
            return JUD_CondRetNaoFoiPossivelVerificar;
         }
         if (APAR_IrPara(pAnalise, direcao) == APAR_CondRetOK)
         {
            int reiPodeMover;
            aparCondRet = APAR_ReiPodeMoverParaCorrente(pAnalise, &reiPodeMover);
            if (aparCondRet != JUD_CondRetOK)
            {
               return JUD_CondRetNaoFoiPossivelVerificar;
            }
            if (!reiPodeMover)
            {
               continue;
            }
   
            aparCondRet = APAR_AlgumaPegadaInimiga(pAnalise, &temPegadaInimiga);
            if (aparCondRet != JUD_CondRetOK)
            {
               return JUD_CondRetNaoFoiPossivelVerificar;
            }
            if (!temPegadaInimiga) {
               *pResposta = 0;
               return JUD_CondRetOK;
            }
         }
      }
   
      *pResposta = 1;
      return JUD_CondRetOK;
   }


/********** Fim do m�dulo de implementa��o: M�dulo Checkmate Judge **********/