/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              PARTIDA.C
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

#include <string.h>

#define PARTIDA_OWN
#include "partida.h"
#undef PARTIDA_OWN

#define NOME_REI "rei"

typedef struct stMovimento {
   LIS_tppLista passos;
   PAR_tpTipoMovimento tipo;
} tpMovimento;

typedef struct stModeloPeca {
   tpMovimento *pMovimento;
   char *nome;
} tpModeloPeca;

typedef struct stPeca {
   tpModeloPeca *pModelo;
   PAR_tpTimePeca time;
} tpPeca;

typedef struct stPegada {
   tpPeca *pPeca;
   struct stPegada *pAnterior;
} tpPegada;

typedef struct stCasa {
   char *nome;
   tpPeca *pPeca;
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

   typedef struct PAR_stPartida {
         TAB_tppTabuleiro pTabuleiro;
         LIS_tppLista pModelosPecas;
         tpCasa *pCasaRei;
   } tpPartida;

   typedef struct PAR_stPartida* PAR_tppPartida;

   typedef PAR_tpCondRet (*tpCallbackIterarCasasAlcancePeca)
      (tpPartida *pPartida, tpPeca *pPeca, tpPegada *pPegAnt);


/***** Protótipos das funções encapuladas no módulo *****/

   static char* NomeDaCasa(int x, int y);

   static tpCasa* CriarCasa();
   
   static void DestroiMovimento(void *pValor);
   
   static void DestruirModeloPeca(void *pValor);
   
   static void DestruirPeca(void *pValor);
   
   static void DestruirCasa(void *pValor);
   
   static void DestruirPegada(void *pValor);

   static int CompararPegadas(void *pPonteiro1, void *pPonteiro2);

   static int CompararNomeModeloPeca(void *pValor1, void *pValor2);

   static int CompararPassos(void *pValor1, void *pValor2);

   static PAR_tpCondRet CriarInstanciaDeRei(tpPartida *pPartida, tpPeca **pPeca);
   
   static PAR_tpCondRet CriarInstanciaDePeca(tpPartida *pPartida, char *nome,
      PAR_tpTimePeca time, tpPeca **ppPeca);


   // criar pegadas
   
   static PAR_tpCondRet InserirPegadaDaPecaNaCasaAtual(tpPartida *pPartida, tpPeca *pPeca,
      tpPegada *pPegAnt);

   static PAR_tpCondRet IterarPelasCasasDeAlcanceDaPeca(tpPartida *pPartida,
      tpCasa *pCasa, tpCallbackIterarCasasAlcancePeca operar);
   
   static PAR_tpCondRet SeguirPassosDaPeca(tpPartida *pPartida, LIS_tppLista pPassos,
      tpPeca *pPeca, DIR_tpDirecao orientacao, tpCallbackIterarCasasAlcancePeca operar);

   static PAR_tpCondRet SeguirPassoDaPeca(tpPartida *pPartida,
      PAR_tpPasso *pPasso, tpPeca *pPeca, DIR_tpDirecao orientacao,
      tpCallbackIterarCasasAlcancePeca operar);

   static PAR_tpCondRet SeguirDirecaoAteNaoPoderMais(tpPartida *pPartida,
      DIR_tpDirecao direcao, tpPeca *pPeca, tpCallbackIterarCasasAlcancePeca operar);
   
   static PAR_tpCondRet SeguirDirecaoEmUmaQuantidadeFixaDeVezes(tpPartida *pPartida,
      DIR_tpDirecao direcao, int quantidade, tpPeca *pPeca,
      tpCallbackIterarCasasAlcancePeca operar);
   
   // fim criar pegada

   static void ExtrairPosicao(char *nomeCasa, int *x, int *y);

   static void DestruirPasso(void *pValor);

   static PAR_tpCondRet InserirModelosPecas(LIS_tppLista pModelosPecas, tpPartida *pPartida);
   
   static LIS_tppLista CopiarPassos(LIS_tppLista pPassos);

/*****  Código das funções exportadas pelo módulo  *****/

   //PAR_tpCondRet PAR_AlgumaPegadaInimiga(PAR_tppPartida pPartida, int *pResposta)
   //{
   //   tpCasa *pCasa;
   //   int estaVazia;
   //   LIS_tpCondRet condRet = LIS_CondRetOK;
   //
   //   TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasa);
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
   //         return PAR_CondRetOK;
   //      }
   //      condRet =  LIS_AvancarElementoCorrente(pCasa->pegadas, 1);
   //   }
   //
   //   *pResposta = 0;
   //   return PAR_CondRetOK;
   //}


   
/***********************************************************************
*
*  $FC Função: TAB Criar partida
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     PAR_CondRetOK
*     PAR_CondRetFaltouMemoria
*
***********************************************************************/
   PAR_tpCondRet PAR_CriarPartida(PAR_tppPartida *ppPartida)
   {
	  tpPartida *pPartida;
     int x, y;

      if (ppPartida != NULL && *ppPartida != NULL)
      {
         PAR_DestruirPartida(ppPartida);
      }
	  
      MEM_Alloc(sizeof(tpPartida), (void **) &pPartida);
      if (pPartida == NULL)
      {
         return PAR_CondRetFaltouMemoria ;
      }

      pPartida->pTabuleiro = NULL;
      pPartida->pCasaRei = NULL;

      TAB_CriarTabuleiro(&pPartida->pTabuleiro, DestruirCasa);

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            tpCasa *pCasa = CriarCasa(NomeDaCasa(x, y));
            TAB_IrCasa(pPartida->pTabuleiro, x, y);
            TAB_AlterarValor(pPartida->pTabuleiro, pCasa);
         }
      }

      LIS_CriarLista(&pPartida->pModelosPecas, DestruirModeloPeca, CompararNomeModeloPeca);

	  *ppPartida = pPartida;

      return PAR_CondRetOK;
   }

/***************************************************************************
*
*  Função: MAT Destruir partida
*  ****/
   PAR_tpCondRet PAR_DestruirPartida(tpPartida **ppPartida)
   {
		tpPartida *pPartida;
      
		if (ppPartida == NULL || *ppPartida == NULL)
		{
			return PAR_CondRetMatrizNaoExiste ;
		}
      
		pPartida = *ppPartida;
         
      TAB_DestruirTabuleiro(&pPartida->pTabuleiro);
      LIS_DestruirLista(pPartida->pModelosPecas);
		MEM_Free(pPartida);
		*ppPartida = NULL;

		return PAR_CondRetOK;
   }

   //PAR_tpCondRet PAR_CriarPegadas(PAR_tppPartida pPartida)
   //{
   //   tpCasa *pCasaOriginal;
   //   int x, y;
   //
   //   TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasaOriginal);
   //
   //   for (x = 0; x < LARGURA; x++)
   //   {
   //      for (y = 0; y < ALTURA; y++)
   //      {
   //         tpCasa *pCasa;
   //         char *nome = NomeDaCasa(x, y);
   //         PAR_IrCasa(pPartida, nome);
   //
   //         TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasa);
   //
   //         if (pCasa->pPeca && pCasa->pPeca->pModelo)
   //         {
   //            IterarPelasCasasDeAlcanceDaPeca(pPartida, pCasa, InserirPegadaDaPecaNaCasaAtual);
   //         }
   //      }
   //   }
   //
   //   PAR_IrCasa(pPartida, pCasaOriginal->nome);
   //
   //   return PAR_CondRetOK;
   //}
   //
   //PAR_tpCondRet PAR_CriarPeca(PAR_tppPartida pPartida, char *nome,
   //   LIS_tppLista pPassos, PAR_tpTipoMovimento tipoMovimento)
   //{
   //   tpModeloPeca *pModelo;
   //   tpMovimento *pMovimento;
   //   MEM_Alloc(sizeof(tpModeloPeca), (void **) &pModelo);
   //   MEM_Alloc(sizeof(tpMovimento), (void **) &pMovimento);
   //
   //   pModelo->nome = nome;
   //   pMovimento->passos = pPassos;
   //   pMovimento->tipo = tipoMovimento;
   //   pModelo->pMovimento = pMovimento;
   //
   //   LIS_IrFinalLista(pPartida->pModelosPecas);
   //   LIS_InserirElementoApos(pPartida->pModelosPecas, pModelo);
   //
   //   return PAR_CondRetOK;
   //}
   //
   //PAR_tpCondRet PAR_AlterarPeca(PAR_tppPartida pPartida, char *nomeAtual, char* nomeNovo,
   //   LIS_tppLista pNovosPassos, PAR_tpTipoMovimento novoTipoMovimento)
   //{
   //   tpModeloPeca *pModelo;
   //   LIS_tpCondRet lisCondRet;
   //
   //   LIS_IrInicioLista(pPartida->pModelosPecas);
   //   
   //   lisCondRet = LIS_ProcurarValor(pPartida->pModelosPecas,nomeAtual);
   //
   //   if(lisCondRet != LIS_CondRetOK)
   //   {
   //      return PAR_CondRetPecaNaoEncontrada;
   //   }
   //
   //   LIS_ObterValor(pPartida->pModelosPecas, (void **) &pModelo);
   //
   //   MEM_Free(pModelo->nome);
   //
   //   pModelo->nome = nomeNovo;
   //   pModelo->pMovimento->passos= pNovosPassos;
   //   pModelo->pMovimento->tipo = novoTipoMovimento;
   //
   //   return PAR_CondRetOK;
   //}
   //
   //PAR_tpCondRet PAR_InserirRei(PAR_tppPartida pPartida)
   //{
   //   TAB_ObterValor(pPartida->pTabuleiro, (void **) &pPartida->pCasaRei);
   //
   //   CriarInstanciaDeRei(pPartida, &pPartida->pCasaRei->pPeca);
   //
   //   return PAR_CondRetOK;
   //}
   //
   //PAR_tpCondRet PAR_InserirPeca(PAR_tppPartida pPartida, char *nome, PAR_tpTimePeca time)
   //{
   //   tpCasa *pCasa;
   //   PAR_tpCondRet tabCondRet;
   //   TAB_ObterValor(pPartida->pTabuleiro, (void **)&pCasa);
   //
   //   tabCondRet = CriarInstanciaDePeca(pPartida, nome, time, &pCasa->pPeca);
   //
   //   if(tabCondRet != PAR_CondRetOK)
   //   {
   //      return tabCondRet;
   //   }
   //
   //   return PAR_CondRetOK;
   //}
   //
   //PAR_tpCondRet PAR_RemoverPeca(PAR_tppPartida pPartida)
   //{
   //   tpCasa *pCasa;
   //   
   //   TAB_ObterValor(pPartida->pTabuleiro, (void **)&pCasa);
   //
   //   if(pCasa->pPeca == NULL)
   //   {
   //      return PAR_CondRetPecaNaoEncontrada;
   //   }
   //
   //   DestruirPeca(pCasa->pPeca);
   //   pCasa->pPeca = NULL;
   //
   //   return PAR_CondRetOK;
   //}
   //
   //PAR_tpCondRet PAR_RemoverRei(PAR_tppPartida pPartida)
   //{
   //   MEM_Free(pPartida->pCasaRei->pPeca);
   //   pPartida->pCasaRei = NULL;
   //
   //   return PAR_CondRetOK;
   //}
   //
   //

   PAR_tpCondRet PAR_IrCasa(PAR_tppPartida pPartida, char *nomeCasa)
   {
      TAB_tpCondRet condRet;
      int x, y;
   
      if (pPartida == NULL)
      {
         return PAR_CondRetMatrizNaoExiste;
      }
      
      ExtrairPosicao(nomeCasa, &x, &y);
      condRet = TAB_IrCasa(pPartida->pTabuleiro, x, y);
      if (condRet != TAB_CondRetOK)
      {
         return PAR_CondRetNaoEhNo;
      }
   
      return PAR_CondRetOK;
   }
   
   //PAR_tpCondRet PAR_IrCasaRei(PAR_tppPartida pPartida)
   //{
   //   PAR_IrCasa(pPartida, pPartida->pCasaRei->nome);
   //
   //   return PAR_CondRetOK;
   //}
   //
   //
   //
   //PAR_tpCondRet PAR_IrPara(PAR_tppPartida pPartida , DIR_tpDirecao direcao)
   //{
   //   TAB_tpCondRet condRet;
   //
   //  if (pPartida == NULL)
   //  {
   //     return PAR_CondRetMatrizNaoExiste ;
   //  }
   //
   //  condRet = TAB_IrPara(pPartida->pTabuleiro, direcao);
   //  
   //  if (condRet != TAB_CondRetOK)
   //  {
   //     return PAR_CondRetNaoEhNo;
   //  }
   //
	//  return PAR_CondRetOK ;
   //}
   //
   //
   //PAR_tpCondRet PAR_EhCheckmate(PAR_tppPartida pPartida, int *pResposta)
   //{
   //   DIR_tpDirecao DIRECOES[TOTAL_DIRECOES] = {
   //      NORTE, NORDESTE, ESTE, SUDESTE,
   //      SUL, SUDOESTE, OESTE, NOROESTE
   //   };
   //   tpCasa *pCasa;
   //   int i;
   //   int temPegadaInimiga;
   //   PAR_IrCasaRei(pPartida);
   //
   //   PAR_AlgumaPegadaInimiga(pPartida, &temPegadaInimiga);
   //   if (!temPegadaInimiga)
   //   {
   //      *pResposta = 0;
   //      return PAR_CondRetOK;
   //   }
   //
   //   for (i = 0; i < TOTAL_DIRECOES; i++)
   //   {
   //      DIR_tpDirecao direcao = DIRECOES[i];
   //      
   //      PAR_IrCasaRei(pPartida);
   //      if (PAR_IrPara(pPartida, direcao) == PAR_CondRetOK)
   //      {
   //         TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasa);
   //         if (pCasa->pPeca && pCasa->pPeca->time == ALIADA)
   //         {
   //            continue;
   //         }
   //
   //         PAR_AlgumaPegadaInimiga(pPartida, &temPegadaInimiga);
   //         if (!temPegadaInimiga) {
   //            *pResposta = 0;
   //            return PAR_CondRetOK;
   //         }
   //      }
   //   }
   //
   //   *pResposta = 1;
   //   return PAR_CondRetOK;
   //}

/*****  Código das funções encapsuladas no módulo  *****/

   char* NomeDaCasa(int x, int y)
   {
      char *nome;

      if (x >= LARGURA || x < 0 || y >= ALTURA || y < 0)
      {
         return NULL;
      }

      MEM_Alloc(sizeof(char)*3, (void **) &nome);
      nome[0] = x + 'A';
      nome[1] = y + '1';
      nome[2] = 0;

      return nome;
   }

   tpCasa* CriarCasa(char *nome)
   {
      tpCasa *pCasa;
      MEM_Alloc(sizeof(tpCasa), (void **) &pCasa);
      LIS_CriarLista(&pCasa->pegadas, DestruirPegada, CompararPegadas);
      pCasa->pPeca = NULL;
      pCasa->nome = nome;
   
      return pCasa;
   }



   void DestruirCasa(void *pValor)
   {
      tpCasa *pCasa = (tpCasa*) pValor;

      LIS_DestruirLista(pCasa->pegadas);
      DestruirPeca((void*) pCasa->pPeca);

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



   void DestruirPeca(void *pValor)
   {
      tpPeca *pPeca = (tpPeca*) pValor;
      if (pValor == NULL)
      {
         return;
      }

      MEM_Free(pPeca);
   }


   void DestruirModeloPeca(void *pValor)
   {
      tpModeloPeca *pModelo = (tpModeloPeca*) pValor;

      if (pModelo == NULL)
      {
         return;
      }
      MEM_Free(pModelo->nome);
      DestroiMovimento(pModelo->pMovimento);
      MEM_Free(pModelo);
   }


   void DestroiMovimento(void *pValor)
   {
      tpMovimento *pMovimento = (tpMovimento*) pValor;
      LIS_DestruirLista(pMovimento->passos);
      MEM_Free(pMovimento);
   }

   
   void DestruirPasso(void *pValor)
   {
      MEM_Free(pValor);
   }
   
   int CompararPegadas(void *pPonteiro1, void *pPonteiro2)
   {
      tpPegada *pPegada = (tpPegada*) pPonteiro1;
      tpPeca *pPeca = (tpPeca*) pPonteiro2;
   
      return strcmp(pPegada->pPeca->pModelo->nome, pPeca->pModelo->nome);
   }

   int CompararNomeModeloPeca(void *pValor1, void *pValor2)
   {
      tpModeloPeca *pModelo1 = (tpModeloPeca*) pValor1;
      char *nomeProcurado = (char*) pValor2;

      return strcmp(pModelo1->nome, nomeProcurado);
   }

   
   int CompararPassos(void *pValor1, void *pValor2)
   {
      // TODO: função para comparar passos
      return 0;
   }
   
   //PAR_tpCondRet CriarInstanciaDePeca(tpPartida *pPartida, char *nome,
   //   PAR_tpTimePeca time, tpPeca **ppPeca)
   //{
   //   tpPeca *pPeca;
   //   tpModeloPeca *pModelo;
   //   LIS_tpCondRet lisCondRet;
   //   MEM_Alloc(sizeof(tpPeca), (void **) &pPeca);
   //   
   //   LIS_IrInicioLista(pPartida->pModelosPecas);
   //   lisCondRet = LIS_ProcurarValor(pPartida->pModelosPecas, nome);
   //   if(lisCondRet != LIS_CondRetOK)
   //   {
   //      return PAR_CondRetPecaNaoEncontrada;
   //   }
   //   LIS_ObterValor(pPartida->pModelosPecas, (void**) &pModelo);
   //   
   //   pPeca->pModelo = pModelo;
   //   pPeca->time = time;
   //
   //   *ppPeca = pPeca;
   //
   //   return PAR_CondRetOK;
   //}
   //
   //
   //PAR_tpCondRet CriarInstanciaDeRei(tpPartida *pPartida, tpPeca **pPeca)
   //{
   //   tpPeca *pRei;
   //   MEM_Alloc(sizeof(tpPeca), (void **) &pRei);
   //
   //   pRei->pModelo = NULL;
   //   pRei->time = ALIADA;
   //
   //   *pPeca = pRei;
   //
   //   return PAR_CondRetOK;
   //}
   //
   //
   //PAR_tpCondRet IterarPelasCasasDeAlcanceDaPeca(tpPartida *pPartida,
   //   tpCasa *pCasa, tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   PAR_tpCondRet condRet;
   //   LIS_tppLista pPassos;
   //   int estaVazia;
   //   
   //   pPassos =pCasa->pPeca->pModelo->pMovimento->passos;
   //
   //   LIS_EstaVazia(pPassos, &estaVazia);
   //
   //   if (estaVazia)
   //   {
   //      return PAR_CondRetOK;
   //   }
   //
   //   SeguirPassosDaPeca(pPartida, pPassos, pCasa->pPeca, NORTE, operar);
   //   PAR_IrCasa(pPartida, pCasa->nome);
   //   SeguirPassosDaPeca(pPartida, pPassos, pCasa->pPeca, ESTE , operar);
   //   PAR_IrCasa(pPartida, pCasa->nome);
   //   SeguirPassosDaPeca(pPartida, pPassos, pCasa->pPeca, SUL  , operar);
   //   PAR_IrCasa(pPartida, pCasa->nome);
   //   SeguirPassosDaPeca(pPartida, pPassos, pCasa->pPeca, OESTE, operar);
   //
   //   return PAR_CondRetOK;
   //}
   //
   //PAR_tpCondRet SeguirPassosDaPeca(tpPartida *pPartida, LIS_tppLista pPassos,
   //   tpPeca *pPeca, DIR_tpDirecao orientacao, tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   PAR_tpCondRet tabCondRet;
   //   LIS_tpCondRet lisCondRet = LIS_CondRetOK;
   // 
   //   LIS_IrInicioLista(pPassos);
   //   while (lisCondRet == LIS_CondRetOK)
   //   {
   //      PAR_tpPasso *pPasso;
   //      LIS_ObterValor(pPassos, (void **) &pPasso);
   //      
   //      tabCondRet = SeguirPassoDaPeca(pPartida, pPasso, pPeca, orientacao, operar);
   //      
   //      if (tabCondRet != PAR_CondRetOK)
   //      {
   //         break;
   //      }
   //
   //      lisCondRet = LIS_AvancarElementoCorrente(pPassos, 1);
   //   }
   //
   //   if (pPeca->pModelo->pMovimento->tipo == VOA && tabCondRet == PAR_CondRetOK)
   //   {
   //      operar(pPartida, pPeca, NULL);
   //   }
   //
   //   return PAR_CondRetOK;
   //
   //}
   //
   //PAR_tpCondRet SeguirPassoDaPeca(tpPartida *pPartida,
   //   PAR_tpPasso *pPasso, tpPeca *pPeca, DIR_tpDirecao orientacao,
   //   tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   PAR_tpCondRet condRet;
   //   DIR_tpDirecao direcao;
   //
   //   DIR_DirecaoOrientadaPara(pPasso->direcao, orientacao, &direcao);
   //
   //   if (pPasso->quantidade == 0)
   //   {
   //      condRet = SeguirDirecaoAteNaoPoderMais(pPartida, direcao, pPeca, operar);
   //   }
   //   else
   //   {
   //      condRet = SeguirDirecaoEmUmaQuantidadeFixaDeVezes(pPartida, direcao,
   //         pPasso->quantidade, pPeca, operar);
   //   }
   //
   //   return condRet;
   //}
   //
   //
   //
   //PAR_tpCondRet SeguirDirecaoEmUmaQuantidadeFixaDeVezes(tpPartida *pPartida,
   //   DIR_tpDirecao direcao, int quantidade, tpPeca *pPeca,
   //   tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   tpPeca *pPecaBarreirando = NULL;
   //   tpPegada *pPegAnt = NULL;
   //   int i;
   //   for (i = 0; i < quantidade && !pPecaBarreirando; i++)
   //   {
   //      PAR_tpCondRet condRet;
   //      condRet = PAR_IrPara(pPartida, direcao);
   //      if (condRet != PAR_CondRetOK)
   //      {
   //         // chegou no final do tabuleiro
   //         return PAR_CondRetNaoEhNo;
   //      }
   //
   //      if (pPeca->pModelo->pMovimento->tipo == ANDA)
   //      {
   //         tpCasa *pCasa;
   //         TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasa);
   //         pPecaBarreirando = pCasa->pPeca;
   //
   //         operar(pPartida, pPeca, pPegAnt);
   //      }
   //
   //   }
   //   return PAR_CondRetOK;
   //}
   //
   //
   //PAR_tpCondRet SeguirDirecaoAteNaoPoderMais(tpPartida *pPartida,
   //   DIR_tpDirecao direcao, tpPeca *pPeca, tpCallbackIterarCasasAlcancePeca operar)
   //{
   //   tpPegada *pPegAnt = NULL;
   //   tpPeca *pPecaBarreirando = NULL;
   //   int i;
   //   PAR_tpCondRet condRet;
   //   condRet = PAR_IrPara(pPartida, direcao);
   //   while(condRet == PAR_CondRetOK && !pPecaBarreirando)
   //   {
   //      if (pPeca->pModelo->pMovimento->tipo == ANDA)
   //      {
   //         tpCasa *pCasa;
   //         TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasa);
   //         pPecaBarreirando = pCasa->pPeca;
   //
   //         operar(pPartida, pPeca, pPegAnt);
   //      }
   //
   //      condRet = PAR_IrPara(pPartida, direcao);
   //   }
   //
   //   return PAR_CondRetOK;
   //}
   //
   //
   //PAR_tpCondRet InserirPegadaDaPecaNaCasaAtual(tpPartida *pPartida, tpPeca *pPeca,
   //   tpPegada *pPegAnt)
   //{
   //   tpCasa *pCasaAtual;
   //   tpPegada *pPegada;
   //   TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasaAtual);
   //   
   //   MEM_Alloc(sizeof(tpPegada), (void **) &pPegada);
   //   pPegada->pAnterior = pPegAnt;
   //   pPegada->pPeca = pPeca;
   //
   //   LIS_InserirElementoApos(pCasaAtual->pegadas, pPegada);
   //   pPegada->pAnterior = pPegAnt;
   //
   //   return PAR_CondRetOK;
   //}

   void ExtrairPosicao(char *nomeCasa, int *x, int *y)
   {
      *x = nomeCasa[0] - 'A';
      *y = nomeCasa[1] - '1';
   }


/********** Fim do módulo de implementação: Módulo matriz **********/