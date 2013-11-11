/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              CHECKMATE_JUDGE.C
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
#include "analise_partida.h"
#include <string.h>

#define CHECKMATE_JUDGE_OWN
#include "checkmate_judge.h"
#undef CHECKMATE_JUDGE_OWN

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

/***** Protótipos das funções encapuladas no módulo *****/


/*****  Código das funções exportadas pelo módulo  *****/

   JUD_tpCondRet JUD_EhCheckmate(PAR_tppPartida pPartida, int *pResposta)
   {
      JUD_tpCondRet condRet;
      APAR_tppAnalise pAnalise;
      
      pAnalise = NULL;
      APAR_CriarAnalise(&pAnalise, pPartida);

      condRet = VerificarCheckmate(pAnalise, pResposta);

      APAR_DestruirAnalise(&pAnalise);

      return condRet;
   }

   JUD_tpCondRet VerificarCheckmate(APAR_tppAnalise pAnalise, int *pResposta)
   {
      DIR_tpDirecao DIRECOES[TOTAL_DIRECOES] = {
         NORTE, NORDESTE, ESTE, SUDESTE,
         SUL, SUDOESTE, OESTE, NOROESTE
      };
      int i;
      int temPegadaInimiga;
      
      APAR_IrCasaRei(pAnalise);
   
      APAR_AlgumaPegadaInimiga(pAnalise, &temPegadaInimiga);
      if (!temPegadaInimiga)
      {
         *pResposta = 0;
         return JUD_CondRetOK;
      }
   
      for (i = 0; i < TOTAL_DIRECOES; i++)
      {
         DIR_tpDirecao direcao = DIRECOES[i];
         
         APAR_IrCasaRei(pAnalise);
         if (APAR_IrPara(pAnalise, direcao) == APAR_CondRetOK)
         {
            int reiPodeMover;
            APAR_ReiPodeMoverParaCorrente(pAnalise, &reiPodeMover);
            if (!reiPodeMover)
            {
               continue;
            }
   
            APAR_AlgumaPegadaInimiga(pAnalise, &temPegadaInimiga);
            if (!temPegadaInimiga) {
               *pResposta = 0;
               return JUD_CondRetOK;
            }
         }
      }
   
      *pResposta = 1;
      return JUD_CondRetOK;
   }

/*****  Código das funções encapsuladas no módulo  *****/


/********** Fim do módulo de implementação: Módulo matriz **********/