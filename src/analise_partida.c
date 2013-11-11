
/***************************************************************************
*
*  Módulo de definição: APAR  Analise Partida
*
*  Arquivo gerado:              analise_partida.h
*  Letras identificadoras:      APAR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Marcação sobre as casas que as peças podem chegar
*
***************************************************************************/

#include <stdio.h>
#include <string.h>

#include "lista.h"
#include "tabuleiro.h"
#include "mem_manager.h"
#include "passo.h"

#define ANALISE_PARTIDA_OWN
#include "analise_partida.h"
#undef ANALISE_PARTIDA_OWN


/***********************************************************************
*  Tipo de dados: APAR Indica que peça pode chegar na casa
***********************************************************************/
typedef struct stPegada {
   PEC_tppPeca pPeca;
   struct stPegada *pAnterior;
} tpPegada;


/***********************************************************************
*  Tipo de dados: APAR Casa do tabuleiro
***********************************************************************/
typedef struct stCasa {
   char *nome;
   PEC_tppPeca pPeca;
   LIS_tppLista pegadas;
} tpCasa;


/***********************************************************************
*  Tipo de dados: APAR Estrutura da Analise da Partida
***********************************************************************/
   typedef struct APAR_stAnalise {
         TAB_tppTabuleiro pTabuleiro;
         tpCasa *pCasaRei;
   } tpAnalise;


/***** Protótipos das funções encapuladas no módulo *****/

   static APAR_tpCondRet CriarCasa(char *nome, PEC_tppPeca pPeca, tpCasa** ppCasa);

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

   
/***************************************************************************
*  Função: APAR Alguma pegada inimiga?
*  ****/
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


/***************************************************************************
*  Função: APAR Rei pode mover para corrente?
*  ****/
   APAR_tpCondRet APAR_ReiPodeMoverParaCorrente(APAR_tppAnalise pAnalise, int *pResposta)
   {
      tpCasa *pCasa;
      PEC_tpTimePeca time;
      PEC_tpCondRet condRet;

      TAB_ObterValor(pAnalise->pTabuleiro, (void**) &pCasa);
      
      condRet = PEC_ObterTime(pCasa->pPeca, &time);
      
      *pResposta = (condRet != PEC_CondRetOK || time == INIMIGA);

      return APAR_CondRetOK;
   }


   

/***************************************************************************
*  Função: APAR Criar análise
*  ****/
   APAR_tpCondRet APAR_CriarAnalise(APAR_tppAnalise *ppAnalise, PAR_tppPartida pPartida)
   {
      APAR_tpCondRet condRet;
      tpAnalise *pAnalise;
      int x, y;
      TAB_tpCondRet tabCondRet;

      MEM_Alloc(sizeof(tpAnalise), (void **) &pAnalise);
      if (pAnalise == NULL)
      {
         return APAR_CondRetFaltouMemoria;
      }

      pAnalise->pTabuleiro = NULL;
      pAnalise->pCasaRei = NULL;

      tabCondRet = TAB_CriarTabuleiro(&pAnalise->pTabuleiro, DestruirCasa);
      if (tabCondRet == TAB_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }

      for (x = 0; x < LARGURA; x++)
      {
         for (y = 0; y < ALTURA; y++)
         {
            tpCasa *pCasa;
            PEC_tppPeca pPeca;
            PAR_tpCondRet parCondRet;
            char *nomeCasa;
            int ehRei;

            tabCondRet = TAB_NomeDaCasa(x, y, &nomeCasa);
            if (tabCondRet == TAB_CondRetFaltouMemoria)
            {
               return APAR_CondRetFaltouMemoria;
            }

            parCondRet = PAR_IrCasa(pPartida, nomeCasa);
            if (parCondRet != PAR_CondRetOK)
            {
               return APAR_CondRetNaoEhCasa;
            }

            tabCondRet = TAB_IrCasa(pAnalise->pTabuleiro, nomeCasa);
            if (tabCondRet != TAB_CondRetOK)
            {
               return APAR_CondRetNaoEhCasa;
            }
            
            parCondRet = PAR_ObterPeca(pPartida, &pPeca);
            if (parCondRet != PAR_CondRetOK)
            {
               return APAR_CondRetNaoEhCasa;
            }

            condRet = CriarCasa(nomeCasa, pPeca, &pCasa);
            if (condRet == APAR_CondRetFaltouMemoria)
            {
               return APAR_CondRetFaltouMemoria;
            }

            PEC_EhORei(pPeca, &ehRei);

            if (ehRei)
            {
               pAnalise->pCasaRei = pCasa;
            }

            TAB_AlterarValor(pAnalise->pTabuleiro, pCasa);
         }
      }

      condRet = CriarPegadas(pAnalise);
      if (condRet == APAR_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }

	  *ppAnalise = pAnalise;

      return APAR_CondRetOK;
   }


/***************************************************************************
*  Função: APAR Destruir análise
*  ****/
   APAR_tpCondRet APAR_DestruirAnalise(tpAnalise **ppAnalise)
   {
		tpAnalise *pAnalise;
      
		if (ppAnalise == NULL || *ppAnalise == NULL)
		{
			return APAR_CondRetAnaliseNaoExiste ;
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
         return APAR_CondRetAnaliseNaoExiste;
      }
      
      condRet = TAB_IrCasa(pAnalise->pTabuleiro, nomeCasa);
      if (condRet != TAB_CondRetOK)
      {
         return APAR_CondRetNaoEhCasa;
      }
   
      return APAR_CondRetOK;
   }
 

/***************************************************************************
*  Função: APAR Ir casa para do rei
*  ****/
   APAR_tpCondRet APAR_IrCasaRei(APAR_tppAnalise pAnalise)
   {
      APAR_IrCasa(pAnalise, pAnalise->pCasaRei->nome);
   
      return APAR_CondRetOK;
   }
   
   

/***************************************************************************
*  Função: APAR Ir para
*  ****/
   APAR_tpCondRet APAR_IrPara(APAR_tppAnalise pAnalise , DIR_tpDirecao direcao)
   {
      TAB_tpCondRet condRet;
   
     if (pAnalise == NULL)
     {
        return APAR_CondRetAnaliseNaoExiste ;
     }
   
     condRet = TAB_IrPara(pAnalise->pTabuleiro, direcao);
     
     if (condRet != TAB_CondRetOK)
     {
        return APAR_CondRetNaoEhCasa;
     }
   
	  return APAR_CondRetOK ;
   }
   

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  Função: APAR Criar casa
*
*  Descrição:
*    Aloca espaço e atribui valores para uma instância de stCasa.
*
***********************************************************************/
   APAR_tpCondRet CriarCasa(char *nome, PEC_tppPeca pPeca, tpCasa **ppCasa)
   {
      tpCasa *pCasa;
      LIS_tpCondRet lisCondRet;
      MEM_Alloc(sizeof(tpCasa), (void **) &pCasa);
      if (pCasa == NULL)
      {
         return APAR_CondRetFaltouMemoria;
      }

      pCasa->pegadas = NULL;
      lisCondRet = LIS_CriarLista(&pCasa->pegadas, DestruirPegada, CompararPegadas);
      if (lisCondRet == LIS_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }
      pCasa->pPeca = pPeca;
      pCasa->nome = nome;
   
      *ppCasa = pCasa;
      return APAR_CondRetOK;
   }

/***********************************************************************
*
*  Função: APAR Destruir Casa
*
*  Descrição:
*    Libera o espaço da estrutura casa e das estruturas que a compõe.
*
***********************************************************************/
   void DestruirCasa(void *pValor)
   {
      tpCasa *pCasa = (tpCasa*) pValor;

      LIS_DestruirLista(pCasa->pegadas);

      PEC_DestruirPeca(&pCasa->pPeca);

      MEM_Free(pCasa);
   }

/***********************************************************************
*
*  Função: APAR Destruir pegada
*
*  Descrição:
*    Libera espaço da estrutura da pegada.
*
***********************************************************************/
   void DestruirPegada(void *pValor)
   {
      MEM_Free(pValor);
   }


/***********************************************************************
*
*  Função: APAR Destruir modelo peca generico
*
*  Descrição:
*    Função genérica que tem como objetivo ser utilizada em alguma
*    estrutura de dados como lista, grafo, etc.
*    Ela utiliza o módulo MPEC para destruir um modelo de peça.
*
***********************************************************************/
   void DestruirModeloPecaGenerico(void *pValor)
   {
      MPEC_DestruirModeloPeca((MPEC_tppModeloPeca*) &pValor);
   }

/***********************************************************************
*
*  Função: APAR Comparar pegadas
*
*  Descrição:
*    Função genérica que tem como objetivo ser utilizada em alguma
*    estrutura de dados como lista, grafo, etc.
*    Ela compara dois ponteiros de pegadas.
*
***********************************************************************/
   int CompararPegadas(void *pPonteiro1, void *pPonteiro2)
   {
      return pPonteiro1 == pPonteiro2;
   }


/***********************************************************************
*
*  Função: APAR Comparar nome do modelo de peça
*
*  Descrição:
*    Função genérica que tem como objetivo ser utilizada em alguma
*    estrutura de dados como lista, grafo, etc.
*    Ela compara o nome de um modelo de peça com uma string. É útil
*    na lista, para buscar um modelo de peça pelo seu nome.
*
***********************************************************************/
   int CompararNomeModeloPeca(void *pValor1, void *pValor2)
   {
      MPEC_tppModeloPeca pModelo1 = (MPEC_tppModeloPeca) pValor1;
      char *nome;
      char *nomeProcurado = (char*) pValor2;

      MPEC_RecuperarNome(pModelo1, &nome);

      return strcmp(nome, nomeProcurado);
   }


/***********************************************************************
*
*  Função: APAR Criar pegadas
*
*  Descrição:
*    Navega pelas casas adicionando pegadas nas casas que têm alguma
*    peça podendo se mover para ela.
*
***********************************************************************/
   APAR_tpCondRet CriarPegadas(APAR_tppAnalise pAnalise)
   {
      tpCasa *pCasaOriginal;
      APAR_tpCondRet condRet;
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
               condRet = IterarPelasCasasDeAlcanceDaPeca(pAnalise, pCasa);
               if (condRet == APAR_CondRetFaltouMemoria)
               {
                  APAR_IrCasa(pAnalise, pCasaOriginal->nome);
                  return APAR_CondRetFaltouMemoria;
               }
            }
         }
      }
   
      APAR_IrCasa(pAnalise, pCasaOriginal->nome);
   
      return APAR_CondRetOK;
   }
   
   
/***********************************************************************
*
*  Função: APAR Iterar pelas casas de alcance da peça
*
*  Descrição:
*    Itera por todas as casas que a peça pode se mover, inserindo
*    as pegadas.
*
***********************************************************************/
   APAR_tpCondRet IterarPelasCasasDeAlcanceDaPeca(tpAnalise *pAnalise,
      tpCasa *pCasa)
   {
      APAR_tpCondRet condRet;
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
   
      condRet = SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, NORTE);
      if (condRet == APAR_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }
      APAR_IrCasa(pAnalise, pCasa->nome);
      
      condRet = SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, ESTE);
      if (condRet == APAR_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }
      APAR_IrCasa(pAnalise, pCasa->nome);
      
      condRet = SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, SUL);
      if (condRet == APAR_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }
      APAR_IrCasa(pAnalise, pCasa->nome);
      
      condRet = SeguirPassosDaPeca(pAnalise, pModelo, pCasa->pPeca, OESTE);
      if (condRet == APAR_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }

      return APAR_CondRetOK;
   }

/***********************************************************************
*
*  Função: APAR Seguir passos da peça
*
*  Descrição:
*    Navega pelas casas baseado na lista de passos de uma determinada peça
*    e em uma direção de orientação.
*
***********************************************************************/
   APAR_tpCondRet SeguirPassosDaPeca(tpAnalise *pAnalise, MPEC_tppModeloPeca pModelo,
      PEC_tppPeca pPeca, DIR_tpDirecao orientacao)
   {
      APAR_tpCondRet condRet;
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
         condRet = InserirPegadaDaPecaNaCasaAtual(pAnalise, pPeca, NULL);
         if (condRet == APAR_CondRetFaltouMemoria)
         {
            return APAR_CondRetFaltouMemoria;
         }
      }
   
      return APAR_CondRetOK;
   
   }

/***********************************************************************
*
*  Função: APAR Seguir passo da peça
*
*  Descrição:
*    Navega pelas casas baseado em um passo de uma determinada lista de
*    passos e em uma direção de orientação.
*
***********************************************************************/
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
   
   
/***********************************************************************
*
*  Função: APAR Seguir direção em uma quantidade fixa de vezes
*
*  Descrição:
*    Navega pelas casas seguindo uma direção em uma quantidade fixa
*    de vezes.
*
***********************************************************************/
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
            return APAR_CondRetNaoEhCasa;
         }
   
         if (tipo == ANDA)
         {
            tpCasa *pCasa;
            TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasa);
            pPecaBarreirando = pCasa->pPeca;
   
            condRet = InserirPegadaDaPecaNaCasaAtual(pAnalise, pPeca, pPegAnt);
            if (condRet == APAR_CondRetFaltouMemoria)
            {
               return APAR_CondRetFaltouMemoria;
            }
         }
   
      }
      return APAR_CondRetOK;
   }
   
/***********************************************************************
*
*  Função: APAR Seguir direção até não poder mais
*
*  Descrição:
*    Navega pelas casas seguindo uma direção até encontrar com uma peça
*    ou com a borda do tabuleiro.
*
***********************************************************************/
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
   
            condRet = InserirPegadaDaPecaNaCasaAtual(pAnalise, pPeca, pPegAnt);
            if (condRet == APAR_CondRetFaltouMemoria)
            {
               return APAR_CondRetFaltouMemoria;
            }
         }
   
         condRet = APAR_IrPara(pAnalise, direcao);
      }
   
      return APAR_CondRetOK;
   }
   

/***********************************************************************
*
*  Função: APAR Inserir pegada da peça na casa atual
*
*  Descrição:
*    Cria e insere uma pegada de uma determinada peça na casa corrente.
*
***********************************************************************/
   APAR_tpCondRet InserirPegadaDaPecaNaCasaAtual(tpAnalise *pAnalise, PEC_tppPeca pPeca,
      tpPegada *pPegAnt)
   {
      tpCasa *pCasaAtual;
      LIS_tpCondRet lisCondRet;
      tpPegada *pPegada;
      TAB_ObterValor(pAnalise->pTabuleiro, (void **) &pCasaAtual);
      
      MEM_Alloc(sizeof(tpPegada), (void **) &pPegada);
      if (pPegada == NULL)
      {
         return APAR_CondRetFaltouMemoria;
      }
      pPegada->pAnterior = pPegAnt;
      pPegada->pPeca = pPeca;
      
      lisCondRet = LIS_InserirElementoApos(pCasaAtual->pegadas, pPegada);
      if (lisCondRet == LIS_CondRetFaltouMemoria)
      {
         return APAR_CondRetFaltouMemoria;
      }
      pPegada->pAnterior = pPegAnt;
   
      return APAR_CondRetOK;
   }


/********** Fim do módulo de implementação: APAR Analise Partida **********/