/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              ANALISE_PARTIDA.C
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
#include "tabuleiro.h"
#include "mem_manager.h"
#include "direcao.h"
#include "passo.h"

#include <string.h>

#define ANALISE_PARTIDA_OWN
#include "analise_partida.h"
#undef ANALISE_PARTIDA_OWN

typedef struct stPegada {
   PEC_tppPeca pPeca;
   struct stPegada *pAnterior;
} tpPegada;

typedef struct stCasa {
   char *nome;
   PEC_tppPeca pPeca;
   LIS_tppLista pegadas;
} tpCasa;

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

   typedef struct APAR_stAnalise {
         TAB_tppTabuleiro pTabuleiro;
         tpCasa *pCasaRei;
   } tpAnalise;

   typedef struct APAR_stAnalise* APAR_tppAnalise;


/***** Protótipos das funções encapuladas no módulo *****/

   static tpCasa* CriarCasa(char *nome, PEC_tppPeca pPeca);

   static void DestruirModeloPecaGenerico(void *pValor);
   
   static void DestruirCasa(void *pValor);
   
   static void DestruirPegada(void *pValor);

   static int CompararPegadas(void *pPonteiro1, void *pPonteiro2);

   static int CompararPassos(void *pValor1, void *pValor2);

   static APAR_tpCondRet CriarPegadas(APAR_tppAnalise pAnalise);
   
   static APAR_tpCondRet InserirPegadaDaPecaNaCasaAtual(tpAnalise *pAnalise, PEC_tppPeca pPeca,
      tpPegada *pPegAnt);

   static APAR_tpCondRet IterarPelasCasasDeAlcanceDaPeca(tpAnalise *pAnalise,
      tpCasa *pCasa);
   
   static APAR_tpCondRet SeguirPassosDaPeca(tpAnalise *pAnalise, MPEC_tppModeloPeca pModelo,
      PEC_tppPeca pPeca, DIR_tpDirecao orientacao);

   static APAR_tpCondRet SeguirPassoDaPeca(tpAnalise *pAnalise,
      PAS_tppPasso pPasso, PEC_tppPeca pPeca, DIR_tpDirecao orientacao);

   static APAR_tpCondRet SeguirDirecaoAteNaoPoderMais(tpAnalise *pAnalise,
      DIR_tpDirecao direcao, PEC_tppPeca pPeca);
   
   static APAR_tpCondRet SeguirDirecaoEmUmaQuantidadeFixaDeVezes(tpAnalise *pAnalise,
      DIR_tpDirecao direcao, PAS_tppPasso pPasso, PEC_tppPeca pPeca);
   
   static APAR_tpCondRet InserirModelosPecas(LIS_tppLista pModelosPecas, tpAnalise *pAnalise);

   static void DestruirPasso(void *pValor);
   
/*****  Código das funções exportadas pelo módulo  *****/

   APAR_tpCondRet APAR_AlgumaPegadaInimiga(APAR_tppAnalise pAnalise, int *pResposta)
   {
      tpCasa *pCasa;
      int estaVazia;
      LIS_tpCondRet condRet = LIS_CondRetOK;
   
      TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
   
      LIS_EstaVazia(pCasa->pegadas, &estaVazia);
      LIS_IrInicioLista(pCasa->pegadas);
      while (condRet == LIS_CondRetOK && !estaVazia)
      {
         tpPegada *pPegada;
         PEC_tpTimePeca time;
         LIS_ObterValor(pCasa->pegadas, (void **) &pPegada);
         PEC_ObterTime(pPegada->pPeca, &time);
         if (time == INIMIGA)
         {
            *pResposta = 1;
            return APAR_CondRetOK;
         }
         condRet =  LIS_AvancarElementoCorrente(pCasa->pegadas, 1);
      }
   
      *pResposta = 0;
      return APAR_CondRetOK;
   }



   APAR_tpCondRet APAR_ReiPodeMoverParaCorrente(APAR_tppAnalise pAnalise, int *pResposta)
   {
      tpCasa *pCasa;
      PEC_tpTimePeca time;
      PEC_tpCondRet condRet;

      TAB_ObterValor(pAnalise->pTabuleiro, (void**) &pCasa);
      
      condRet = PEC_ObterTime(pCasa->pPeca, &time);
      
      *pResposta = condRet == PEC_CondRetOK && time == ALIADA;

      return APAR_CondRetOK;
   }


   
/***********************************************************************
*
*  $FC Função: TAB Criar analise_partida
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     APAR_CondRetOK
*     APAR_CondRetFaltouMemoria
*
***********************************************************************/
   APAR_tpCondRet APAR_CriarAnalise(APAR_tppAnalise *ppAnalise, PAR_tppPartida pPartida)
   {
	  tpAnalise *pAnalise;
     int x, y;

      if (ppAnalise != NULL && *ppAnalise != NULL)
      {
         APAR_DestruirAnalise(ppAnalise);
      }
	  
      MEM_Alloc(sizeof(tpAnalise), (void **) &pAnalise);
      if (pAnalise == NULL)
      {
         return APAR_CondRetFaltouMemoria;
      }

      pAnalise->pTabuleiro = NULL;
      pAnalise->pCasaRei = NULL;

      TAB_CriarTabuleiro(&pAnalise->pTabuleiro, DestruirCasa);

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            tpCasa *pCasa;
            PEC_tppPeca pPeca;
            char *nomeCasa;
            int ehRei;
            TAB_NomeDaCasa(x, y, &nomeCasa);

            PAR_IrCasa(pPartida, nomeCasa);
            TAB_IrCasa(pAnalise->pTabuleiro, nomeCasa);
            PAR_ObterPeca(pPartida, &pPeca);

            pCasa = CriarCasa(nomeCasa, pPeca);

            PEC_EhORei(pPeca, &ehRei);

            if (ehRei)
            {
               pAnalise->pCasaRei = pCasa;
            }

            TAB_AlterarValor(pAnalise->pTabuleiro, pCasa);
         }
      }

      CriarPegadas(pAnalise);

	  *ppAnalise = pAnalise;

      return APAR_CondRetOK;
   }

/***************************************************************************
*
*  Função: MAT Destruir analise_partida
*  ****/
   APAR_tpCondRet APAR_DestruirAnalise(tpAnalise **ppAnalise)
   {
		tpAnalise *pAnalise;
      
		if (ppAnalise == NULL || *ppAnalise == NULL)
		{
			return APAR_CondRetMatrizNaoExiste ;
		}
      
		pAnalise = *ppAnalise;
         
      TAB_DestruirTabuleiro(&pAnalise->pTabuleiro);
		MEM_Free(pAnalise);
		*ppAnalise = NULL;

		return APAR_CondRetOK;
   }

   APAR_tpCondRet APAR_IrCasa(APAR_tppAnalise pAnalise, char *nomeCasa)
   {
      TAB_tpCondRet condRet;
   
      if (pAnalise == NULL)
      {
         return APAR_CondRetMatrizNaoExiste;
      }
      
      condRet = TAB_IrCasa(pAnalise->pTabuleiro, nomeCasa);
      if (condRet != TAB_CondRetOK)
      {
         return APAR_CondRetNaoEhNo;
      }
   
      return APAR_CondRetOK;
   }
   
   APAR_tpCondRet APAR_IrCasaRei(APAR_tppAnalise pAnalise)
   {
      APAR_IrCasa(pAnalise, pAnalise->pCasaRei->nome);
   
      return APAR_CondRetOK;
   }
   
   
   
   APAR_tpCondRet APAR_IrPara(APAR_tppAnalise pAnalise , DIR_tpDirecao direcao)
   {
      TAB_tpCondRet condRet;
   
     if (pAnalise == NULL)
     {
        return APAR_CondRetMatrizNaoExiste ;
     }
   
     condRet = TAB_IrPara(pAnalise->pTabuleiro, direcao);
     
     if (condRet != TAB_CondRetOK)
     {
        return APAR_CondRetNaoEhNo;
     }
   
	  return APAR_CondRetOK ;
   }
   

/*****  Código das funções encapsuladas no módulo  *****/

   tpCasa* CriarCasa(char *nome, PEC_tppPeca pPeca)
   {
      tpCasa *pCasa;
      MEM_Alloc(sizeof(tpCasa), (void **) &pCasa);
      pCasa->pegadas = NULL;
      LIS_CriarLista(&pCasa->pegadas, DestruirPegada, CompararPegadas);
      pCasa->pPeca = pPeca;
      pCasa->nome = nome;
   
      return pCasa;
   }

   void DestruirCasa(void *pValor)
   {
      tpCasa *pCasa = (tpCasa*) pValor;

      LIS_DestruirLista(pCasa->pegadas);

      PEC_DestruirPeca(&pCasa->pPeca);

      MEM_Free(pCasa);
   }

   void DestruirPegada(void *pValor)
   {
      tpPegada *pPegada = (tpPegada*) pValor;
      
      if (pValor == NULL)
      {
         return;
      }

      DestruirPegada((void *) pPegada->pAnterior);
      MEM_Free(pValor);
   }


   void DestruirModeloPecaGenerico(void *pValor)
   {
      MPEC_DestruirModeloPeca((MPEC_tppModeloPeca*) &pValor);
   }

   int CompararPegadas(void *pPonteiro1, void *pPonteiro2)
   {
      tpPegada *pPegada = (tpPegada*) pPonteiro1;
      // TODO [RCS] PER_CriarPeca
      //tpPeca *pPeca = (tpPeca*) pPonteiro2;
   
      // TODO [RCS] pensar em como implementar linha abaixo
      //return strcmp(pPegada->pPeca->pModelo->nome, pPeca->pModelo->nome);
      return 0;
   }

   
   int CompararNomeModeloPeca(void *pValor1, void *pValor2)
   {
      MPEC_tppModeloPeca pModelo1 = (MPEC_tppModeloPeca) pValor1;
      char *nome;
      char *nomeProcurado = (char*) pValor2;

      MPEC_RecuperarNome(pModelo1, &nome);

      return strcmp(nome, nomeProcurado);
   }

   
   APAR_tpCondRet CriarPegadas(APAR_tppAnalise pAnalise)
   {
      tpCasa *pCasaOriginal;
      int x, y;
   
      TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasaOriginal);
   
      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            int ehRei;
            tpCasa *pCasa;
            char *nome;
            TAB_NomeDaCasa(x, y, &nome);
            APAR_IrCasa(pAnalise, nome);
   
            TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
            PEC_EhORei(pCasa->pPeca, &ehRei);
            if (!ehRei)
            {
               IterarPelasCasasDeAlcanceDaPeca(pAnalise, pCasa);
            }
         }
      }
   
      APAR_IrCasa(pAnalise, pCasaOriginal->nome);
   
      return APAR_CondRetOK;
   }
   
   
   
   APAR_tpCondRet IterarPelasCasasDeAlcanceDaPeca(tpAnalise *pAnalise,
      tpCasa *pCasa)
   {
      MPEC_tppModeloPeca pModelo;
      LIS_tppLista pPassos;
      int estaVazia;
      
      PEC_ObterModelo(pCasa->pPeca, &pModelo);
      MPEC_ObterPassos(pModelo, &pPassos);
   
      LIS_EstaVazia(pPassos, &estaVazia);
   
      if (estaVazia)
      {
         return APAR_CondRetOK;
      }
   
      SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, NORTE);
      APAR_IrCasa(pAnalise, pCasa->nome);
      SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, ESTE );
      APAR_IrCasa(pAnalise, pCasa->nome);
      SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, SUL  );
      APAR_IrCasa(pAnalise, pCasa->nome);
      SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, OESTE);
   
      return APAR_CondRetOK;
   }
   
   APAR_tpCondRet SeguirPassosDaPeca(tpAnalise *pAnalise, MPEC_tppModeloPeca pModelo,
      PEC_tppPeca pPeca, DIR_tpDirecao orientacao)
   {
      MPEC_tpTipoMovimento tipo;
      LIS_tppLista pPassos;
      APAR_tpCondRet tabCondRet;
      LIS_tpCondRet lisCondRet = LIS_CondRetOK;

      MPEC_ObterPassos(pModelo, &pPassos);
      MPEC_ObterTipo(pModelo, &tipo);
    
      LIS_IrInicioLista(pPassos);
      while (lisCondRet == LIS_CondRetOK)
      {
         PAS_tppPasso pPasso;
         LIS_ObterValor(pPassos, (void **) &pPasso);
         
         tabCondRet = SeguirPassoDaPeca(pAnalise, pPasso, pPeca, orientacao);
         
         if (tabCondRet != APAR_CondRetOK)
         {
            break;
         }
   
         lisCondRet = LIS_AvancarElementoCorrente(pPassos, 1);
      }
   
      if (tipo == VOA && tabCondRet == APAR_CondRetOK)
      {
         InserirPegadaDaPecaNaCasaAtual(pAnalise, pPeca, NULL);
      }
   
      return APAR_CondRetOK;
   
   }
   
   APAR_tpCondRet SeguirPassoDaPeca(tpAnalise *pAnalise,
      PAS_tppPasso pPasso, PEC_tppPeca pPeca, DIR_tpDirecao orientacao)
   {
      APAR_tpCondRet condRet;
      int ehInfinito;
      DIR_tpDirecao direcao;

      PAS_ObterDirecao(pPasso, &direcao);
      PAS_EhInfinito(pPasso, &ehInfinito);
   
      DIR_DirecaoOrientadaPara(direcao, orientacao, &direcao);
   
      if (ehInfinito)
      {
         condRet = SeguirDirecaoAteNaoPoderMais(pAnalise, direcao, pPeca);
      }
      else
      {
         condRet = SeguirDirecaoEmUmaQuantidadeFixaDeVezes(pAnalise, direcao,
            pPasso, pPeca);
      }
   
      return condRet;
   }
   
   
   
   APAR_tpCondRet SeguirDirecaoEmUmaQuantidadeFixaDeVezes(tpAnalise *pAnalise,
      DIR_tpDirecao direcao, PAS_tppPasso pPasso, PEC_tppPeca pPeca)
   {
      PEC_tppPeca pPecaBarreirando = NULL;
      tpPegada *pPegAnt = NULL;
      MPEC_tppModeloPeca pModelo;
      MPEC_tpTipoMovimento tipo;
      int i, quantidade;

      PAS_ObterQuantidade(pPasso, &quantidade);

      PEC_ObterModelo(pPeca, &pModelo);
      MPEC_ObterTipo(pModelo, &tipo);

      for (i = 0; i < quantidade && !pPecaBarreirando; i++)
      {
         APAR_tpCondRet condRet;
         condRet = APAR_IrPara(pAnalise, direcao);
         if (condRet != APAR_CondRetOK)
         {
            // chegou no final do tabuleiro
            return APAR_CondRetNaoEhNo;
         }
   
         if (tipo == ANDA)
         {
            tpCasa *pCasa;
            TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
            pPecaBarreirando = pCasa->pPeca;
   
            InserirPegadaDaPecaNaCasaAtual(pAnalise, pPeca, pPegAnt);
         }
   
      }
      return APAR_CondRetOK;
   }
   
   
   APAR_tpCondRet SeguirDirecaoAteNaoPoderMais(tpAnalise *pAnalise,
      DIR_tpDirecao direcao, PEC_tppPeca pPeca)
   {
      tpPegada *pPegAnt = NULL;
      PEC_tppPeca pPecaBarreirando = NULL;
      MPEC_tppModeloPeca pModelo;
      MPEC_tpTipoMovimento tipo;
      APAR_tpCondRet condRet;
      condRet = APAR_IrPara(pAnalise, direcao);
      
      PEC_ObterModelo(pPeca, &pModelo);
      MPEC_ObterTipo(pModelo, &tipo);

      while(condRet == APAR_CondRetOK && !pPecaBarreirando)
      {
         if (tipo == ANDA)
         {
            tpCasa *pCasa;
            TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
            pPecaBarreirando = pCasa->pPeca;
   
            InserirPegadaDaPecaNaCasaAtual(pAnalise, pPeca, pPegAnt);
         }
   
         condRet = APAR_IrPara(pAnalise, direcao);
      }
   
      return APAR_CondRetOK;
   }
   
   
   APAR_tpCondRet InserirPegadaDaPecaNaCasaAtual(tpAnalise *pAnalise, PEC_tppPeca pPeca,
      tpPegada *pPegAnt)
   {
      tpCasa *pCasaAtual;
      tpPegada *pPegada;
      TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasaAtual);
      
      MEM_Alloc(sizeof(tpPegada), (void **) &pPegada);
      pPegada->pAnterior = pPegAnt;
      pPegada->pPeca = pPeca;
      
      LIS_InserirElementoApos(pCasaAtual->pegadas, pPegada);
      pPegada->pAnterior = pPegAnt;
   
      return APAR_CondRetOK;
   }


/********** Fim do módulo de implementação: Módulo matriz **********/