/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              ANALISE_PARTIDA.C
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
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

#define NOME_REI "rei"

typedef struct stPegada {
   PEC_tppPeca *pPeca;
   struct stPegada *pAnterior;
} tpPegada;

typedef struct stCasa {
   char *nome;
   PEC_tppPeca pPeca;
   LIS_tppLista pegadas;
} tpCasa;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabe�a de uma matriz
*
*
*  $ED Descri��o do tipo
*     A cabe�a da matriz � o ponto de acesso para uma determinada matriz.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*
***********************************************************************/

   typedef struct APAR_stAnalise {
         TAB_tppTabuleiro pTabuleiro;
         tpCasa *pCasaRei;
   } tpAnalise;

   typedef struct APAR_stAnalise* APAR_tppAnalise;

   typedef APAR_tpCondRet (*tpCallbackIterarCasasAlcancePeca)
      (tpAnalise *pAnalise, PEC_tppPeca *pPeca, tpPegada *pPegAnt);


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static tpCasa* CriarCasa(char *nome, PEC_tppPeca pPeca);

   static void DestruirModeloPecaGenerico(void *pValor);
   
   //static void DestruirPeca(void *pValor);
   
   static void DestruirCasa(void *pValor);
   
   static void DestruirPegada(void *pValor);

   static int CompararPegadas(void *pPonteiro1, void *pPonteiro2);

   static int CompararPassos(void *pValor1, void *pValor2);

   // criar pegadas
   
   static APAR_tpCondRet InserirPegadaDaPecaNaCasaAtual(tpAnalise *pAnalise, PEC_tppPeca *pPeca,
      tpPegada *pPegAnt);

   static APAR_tpCondRet IterarPelasCasasDeAlcanceDaPeca(tpAnalise *pAnalise,
      tpCasa *pCasa, tpCallbackIterarCasasAlcancePeca operar);
   
   static APAR_tpCondRet SeguirPassosDaPeca(tpAnalise *pAnalise, LIS_tppLista pPassos,
      PEC_tppPeca *pPeca, DIR_tpDirecao orientacao, tpCallbackIterarCasasAlcancePeca operar);

   static APAR_tpCondRet SeguirPassoDaPeca(tpAnalise *pAnalise,
      PAS_tppPasso pPasso, PEC_tppPeca *pPeca, DIR_tpDirecao orientacao,
      tpCallbackIterarCasasAlcancePeca operar);

   static APAR_tpCondRet SeguirDirecaoAteNaoPoderMais(tpAnalise *pAnalise,
      DIR_tpDirecao direcao, PEC_tppPeca *pPeca, tpCallbackIterarCasasAlcancePeca operar);
   
   static APAR_tpCondRet SeguirDirecaoEmUmaQuantidadeFixaDeVezes(tpAnalise *pAnalise,
      DIR_tpDirecao direcao, int quantidade, PEC_tppPeca *pPeca,
      tpCallbackIterarCasasAlcancePeca operar);
   
   // fim criar pegada

   static void DestruirPasso(void *pValor);

   static APAR_tpCondRet InserirModelosPecas(LIS_tppLista pModelosPecas, tpAnalise *pAnalise);
   
   static LIS_tppLista CopiarPassos(LIS_tppLista pPassos);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

   //APAR_tpCondRet APAR_AlgumaPegadaInimiga(APAR_tppAnalise pAnalise, int *pResposta)
   //{
   //   tpCasa *pCasa;
   //   int estaVazia;
   //   LIS_tpCondRet condRet = LIS_CondRetOK;
   //
   //   TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
   //
   //   LIS_EstaVazia(pCasa->pegadas, &estaVazia);
   //   LIS_IrInicioLista(pCasa->pegadas);
   //   while (condRet == LIS_CondRetOK && !estaVazia)
   //   {
   //      tpPegada *pPegada;
   //      LIS_ObterValor(pCasa->pegadas, (void **) &pPegada);
   //      if (pPegada->pPeca->time == INIMIGA)
   //      {
   //         *pResposta = 1;
   //         return APAR_CondRetOK;
   //      }
   //      condRet =  LIS_AvancarElementoCorrente(pCasa->pegadas, 1);
   //   }
   //
   //   *pResposta = 0;
   //   return APAR_CondRetOK;
   //}


   
/***********************************************************************
*
*  $FC Fun��o: TAB Criar analise_partida
*
*  $ED Descri��o da fun��o
*     Cria uma nova matriz vazia.
*     Caso j� exista uma matriz, esta ser� destru�da.
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

	  *ppAnalise = pAnalise;

      return APAR_CondRetOK;
   }

/***************************************************************************
*
*  Fun��o: MAT Destruir analise_partida
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

   //APAR_tpCondRet APAR_CriarPegadas(APAR_tppAnalise pAnalise)
   //{
   //   tpCasa *pCasaOriginal;
   //   int x, y;
   //
   //   TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasaOriginal);
   //
   //   for (x = 0; x < LARGURA; x++)
   //   {
   //      for (y = 0; y < ALTURA; y++)
   //      {
   //         tpCasa *pCasa;
   //         char *nome = NomeDaCasa(x, y);
   //         APAR_IrCasa(pAnalise, nome);
   //
   //         TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
   //
   //         if (pCasa->pPeca && pCasa->pPeca->pModelo)
   //         {
   //            IterarPelasCasasDeAlcanceDaPeca(pAnalise, pCasa, InserirPegadaDaPecaNaCasaAtual);
   //         }
   //      }
   //   }
   //
   //   APAR_IrCasa(pAnalise, pCasaOriginal->nome);
   //
   //   return APAR_CondRetOK;
   //}
   

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
   
   
   
   //APAR_tpCondRet APAR_IrPara(APAR_tppAnalise pAnalise , DIR_tpDirecao direcao)
   //{
   //   TAB_tpCondRet condRet;
   //
   //  if (pAnalise == NULL)
   //  {
   //     return APAR_CondRetMatrizNaoExiste ;
   //  }
   //
   //  condRet = TAB_IrPara(pAnalise->pTabuleiro, direcao);
   //  
   //  if (condRet != TAB_CondRetOK)
   //  {
   //     return APAR_CondRetNaoEhNo;
   //  }
   //
	//  return APAR_CondRetOK ;
   //}
   //
   //
   //APAR_tpCondRet APAR_EhCheckmate(APAR_tppAnalise pAnalise, int *pResposta)
   //{
   //   DIR_tpDirecao DIRECOES[TOTAL_DIRECOES] = {
   //      NORTE, NORDESTE, ESTE, SUDESTE,
   //      SUL, SUDOESTE, OESTE, NOROESTE
   //   };
   //   tpCasa *pCasa;
   //   int i;
   //   int temPegadaInimiga;
   //   APAR_IrCasaRei(pAnalise);
   //
   //   APAR_AlgumaPegadaInimiga(pAnalise, &temPegadaInimiga);
   //   if (!temPegadaInimiga)
   //   {
   //      *pResposta = 0;
   //      return APAR_CondRetOK;
   //   }
   //
   //   for (i = 0; i < TOTAL_DIRECOES; i++)
   //   {
   //      DIR_tpDirecao direcao = DIRECOES[i];
   //      
   //      APAR_IrCasaRei(pAnalise);
   //      if (APAR_IrPara(pAnalise, direcao) == APAR_CondRetOK)
   //      {
   //         TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
   //         if (pCasa->pPeca && pCasa->pPeca->time == ALIADA)
   //         {
   //            continue;
   //         }
   //
   //         APAR_AlgumaPegadaInimiga(pAnalise, &temPegadaInimiga);
   //         if (!temPegadaInimiga) {
   //            *pResposta = 0;
   //            return APAR_CondRetOK;
   //         }
   //      }
   //   }
   //
   //   *pResposta = 1;
   //   return APAR_CondRetOK;
   //}

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

   tpCasa* CriarCasa(char *nome, PEC_tppPeca pPeca)
   {
      tpCasa *pCasa;
      MEM_Alloc(sizeof(tpCasa), (void **) &pCasa);
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

   
   int CompararPassos(void *pValor1, void *pValor2)
   {
      // TODO: fun��o para comparar passos
      return 0;
   }
   
   
   //APAR_tpCondRet IterarPelasCasasDeAlcanceDaPeca(tpAnalise *pAnalise,
   //   tpCasa *pCasa, tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   APAR_tpCondRet condRet;
   //   LIS_tppLista pPassos;
   //   int estaVazia;
   //   
   //   pPassos =pCasa->pPeca->pModelo->pMovimento->passos;
   //
   //   LIS_EstaVazia(pPassos, &estaVazia);
   //
   //   if (estaVazia)
   //   {
   //      return APAR_CondRetOK;
   //   }
   //
   //   SeguirPassosDaPeca(pAnalise, pPassos, pCasa->pPeca, NORTE, operar);
   //   APAR_IrCasa(pAnalise, pCasa->nome);
   //   SeguirPassosDaPeca(pAnalise, pPassos, pCasa->pPeca, ESTE , operar);
   //   APAR_IrCasa(pAnalise, pCasa->nome);
   //   SeguirPassosDaPeca(pAnalise, pPassos, pCasa->pPeca, SUL  , operar);
   //   APAR_IrCasa(pAnalise, pCasa->nome);
   //   SeguirPassosDaPeca(pAnalise, pPassos, pCasa->pPeca, OESTE, operar);
   //
   //   return APAR_CondRetOK;
   //}
   //
   //APAR_tpCondRet SeguirPassosDaPeca(tpAnalise *pAnalise, LIS_tppLista pPassos,
   //   tpPeca *pPeca, DIR_tpDirecao orientacao, tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   APAR_tpCondRet tabCondRet;
   //   LIS_tpCondRet lisCondRet = LIS_CondRetOK;
   // 
   //   LIS_IrInicioLista(pPassos);
   //   while (lisCondRet == LIS_CondRetOK)
   //   {
   //      APAR_tpPasso *pPasso;
   //      LIS_ObterValor(pPassos, (void **) &pPasso);
   //      
   //      tabCondRet = SeguirPassoDaPeca(pAnalise, pPasso, pPeca, orientacao, operar);
   //      
   //      if (tabCondRet != APAR_CondRetOK)
   //      {
   //         break;
   //      }
   //
   //      lisCondRet = LIS_AvancarElementoCorrente(pPassos, 1);
   //   }
   //
   //   if (pPeca->pModelo->pMovimento->tipo == VOA && tabCondRet == APAR_CondRetOK)
   //   {
   //      operar(pAnalise, pPeca, NULL);
   //   }
   //
   //   return APAR_CondRetOK;
   //
   //}
   //
   //APAR_tpCondRet SeguirPassoDaPeca(tpAnalise *pAnalise,
   //   APAR_tpPasso *pPasso, tpPeca *pPeca, DIR_tpDirecao orientacao,
   //   tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   APAR_tpCondRet condRet;
   //   DIR_tpDirecao direcao;
   //
   //   DIR_DirecaoOrientadaPara(pPasso->direcao, orientacao, &direcao);
   //
   //   if (pPasso->quantidade == 0)
   //   {
   //      condRet = SeguirDirecaoAteNaoPoderMais(pAnalise, direcao, pPeca, operar);
   //   }
   //   else
   //   {
   //      condRet = SeguirDirecaoEmUmaQuantidadeFixaDeVezes(pAnalise, direcao,
   //         pPasso->quantidade, pPeca, operar);
   //   }
   //
   //   return condRet;
   //}
   //
   //
   //
   //APAR_tpCondRet SeguirDirecaoEmUmaQuantidadeFixaDeVezes(tpAnalise *pAnalise,
   //   DIR_tpDirecao direcao, int quantidade, tpPeca *pPeca,
   //   tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   tpPeca *pPecaBarreirando = NULL;
   //   tpPegada *pPegAnt = NULL;
   //   int i;
   //   for (i = 0; i < quantidade && !pPecaBarreirando; i++)
   //   {
   //      APAR_tpCondRet condRet;
   //      condRet = APAR_IrPara(pAnalise, direcao);
   //      if (condRet != APAR_CondRetOK)
   //      {
   //         // chegou no final do tabuleiro
   //         return APAR_CondRetNaoEhNo;
   //      }
   //
   //      if (pPeca->pModelo->pMovimento->tipo == ANDA)
   //      {
   //         tpCasa *pCasa;
   //         TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
   //         pPecaBarreirando = pCasa->pPeca;
   //
   //         operar(pAnalise, pPeca, pPegAnt);
   //      }
   //
   //   }
   //   return APAR_CondRetOK;
   //}
   //
   //
   //APAR_tpCondRet SeguirDirecaoAteNaoPoderMais(tpAnalise *pAnalise,
   //   DIR_tpDirecao direcao, tpPeca *pPeca, tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   tpPegada *pPegAnt = NULL;
   //   tpPeca *pPecaBarreirando = NULL;
   //   int i;
   //   APAR_tpCondRet condRet;
   //   condRet = APAR_IrPara(pAnalise, direcao);
   //   while(condRet == APAR_CondRetOK && !pPecaBarreirando)
   //   {
   //      if (pPeca->pModelo->pMovimento->tipo == ANDA)
   //      {
   //         tpCasa *pCasa;
   //         TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
   //         pPecaBarreirando = pCasa->pPeca;
   //
   //         operar(pAnalise, pPeca, pPegAnt);
   //      }
   //
   //      condRet = APAR_IrPara(pAnalise, direcao);
   //   }
   //
   //   return APAR_CondRetOK;
   //}
   //
   //
   //APAR_tpCondRet InserirPegadaDaPecaNaCasaAtual(tpAnalise *pAnalise, tpPeca *pPeca,
   //   tpPegada *pPegAnt)
   //{
   //   tpCasa *pCasaAtual;
   //   tpPegada *pPegada;
   //   TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasaAtual);
   //   
   //   MEM_Alloc(sizeof(tpPegada), (void **) &pPegada);
   //   pPegada->pAnterior = pPegAnt;
   //   pPegada->pPeca = pPeca;
   //
   //   LIS_InserirElementoApos(pCasaAtual->pegadas, pPegada);
   //   pPegada->pAnterior = pPegAnt;
   //
   //   return APAR_CondRetOK;
   //}

   void ExtrairPosicao(char *nomeCasa, int *x, int *y)
   {
      *x = nomeCasa[0] - 'A';
      *y = nomeCasa[1] - '1';
   }


/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/