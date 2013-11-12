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
#include <stdlib.h>
#include "lista.h"
#include "tabuleiro.h"
#include "mem_manager.h"
#include "direcao.h"
#include "passo.h"
#include "input_string_parser.h"

#include <string.h>

#define PARTIDA_OWN
#include "partida.h"
#undef PARTIDA_OWN

typedef struct stCasa {
   char *nome;
   PEC_tppPeca pPeca;
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

   static FILE *pFile;
   static char *pCaminho;
/***** Protótipos das funções encapuladas no módulo *****/

   static int InserirCasaNoTabuleiro(TAB_tppTabuleiro pTabuleiro, char *nome);

   static tpCasa* CriarCasa();
   
   static void DestruirModeloPecaGenerico(void *pValor);
   
   static void DestruirCasa(void *pValor);

   static int CompararNomeModeloPeca(void *pValor1, void *pValor2);

   static PAR_tpCondRet CriarInstanciaDeRei(tpPartida *pPartida, PEC_tppPeca *ppPeca);
   
   static PAR_tpCondRet CriarInstanciaDePeca(tpPartida *pPartida, char *nome,
      PEC_tpTimePeca time, PEC_tppPeca *ppPeca);

   static int SalvaCasas(char *nome, void* pValor);

/*****  Código das funções exportadas pelo módulo  *****/
   
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
         return PAR_CondRetFaltouMemoria;
      }

      pPartida->pTabuleiro = NULL;
      pPartida->pCasaRei = NULL;

      TAB_CriarTabuleiro(&pPartida->pTabuleiro, DestruirCasa);

      TAB_PercorrerCasas(pPartida->pTabuleiro, InserirCasaNoTabuleiro);

      LIS_CriarLista(&pPartida->pModelosPecas, DestruirModeloPecaGenerico, CompararNomeModeloPeca);

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

   PAR_tpCondRet PAR_CriarPeca(PAR_tppPartida pPartida, char *nome,
      LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento)
   {
      MPEC_tppModeloPeca pModelo;

      MPEC_CriarModeloPeca(&pModelo, nome, pPassos, tipoMovimento);

      LIS_IrFinalLista(pPartida->pModelosPecas);
      LIS_InserirElementoApos(pPartida->pModelosPecas, pModelo);
   
      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet PAR_AlterarPeca(PAR_tppPartida pPartida, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, MPEC_tpTipoMovimento novoTipoMovimento)
   {
      MPEC_tppModeloPeca pModelo;
      LIS_tpCondRet lisCondRet;
   
      LIS_IrInicioLista(pPartida->pModelosPecas);
      
      lisCondRet = LIS_ProcurarValor(pPartida->pModelosPecas, nomeAtual);
   
      if(lisCondRet != LIS_CondRetOK)
      {
         return PAR_CondRetPecaNaoEncontrada;
      }
   
      LIS_ObterValor(pPartida->pModelosPecas, (void **) &pModelo);

      MPEC_AlterarModeloPeca(pModelo, nomeNovo, pNovosPassos, novoTipoMovimento);
   
      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet PAR_InserirRei(PAR_tppPartida pPartida)
   {
      TAB_ObterValor(pPartida->pTabuleiro, (void **) &pPartida->pCasaRei);
   
      CriarInstanciaDeRei(pPartida, &pPartida->pCasaRei->pPeca);
   
      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet PAR_InserirPeca(PAR_tppPartida pPartida, char *nome, PEC_tpTimePeca time)
   {
      tpCasa *pCasa;
      PAR_tpCondRet tabCondRet;
      TAB_ObterValor(pPartida->pTabuleiro, (void **)&pCasa);

      tabCondRet = CriarInstanciaDePeca(pPartida, nome, time, &pCasa->pPeca);
   
      if(tabCondRet != PAR_CondRetOK)
      {
         return tabCondRet;
      }
   
      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet PAR_RemoverPeca(PAR_tppPartida pPartida)
   {
      tpCasa *pCasa;
      
      TAB_ObterValor(pPartida->pTabuleiro, (void **)&pCasa);
   
      if(pCasa->pPeca == NULL)
      {
         return PAR_CondRetPecaNaoEncontrada;
      }
   
      PEC_DestruirPeca(&pCasa->pPeca);
      pCasa->pPeca = NULL;
   
      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet PAR_RemoverRei(PAR_tppPartida pPartida)
   {
      PEC_DestruirPeca(&pPartida->pCasaRei->pPeca);
      pPartida->pCasaRei = NULL;
   
      return PAR_CondRetOK;
   }

   PAR_tpCondRet PAR_IrCasa(PAR_tppPartida pPartida, char *nomeCasa)
   {
      TAB_tpCondRet condRet;
   
      if (pPartida == NULL)
      {
         return PAR_CondRetMatrizNaoExiste;
      }
      
      condRet = TAB_IrCasa(pPartida->pTabuleiro, nomeCasa);
      if (condRet != TAB_CondRetOK)
      {
         return PAR_CondRetNaoEhNo;
      }
   
      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet PAR_IrCasaRei(PAR_tppPartida pPartida)
   {
      PAR_IrCasa(pPartida, pPartida->pCasaRei->nome);
   
      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet CriarInstanciaDePeca(tpPartida *pPartida, char *nome,
      PEC_tpTimePeca time, PEC_tppPeca *ppPeca)
   {
      MPEC_tppModeloPeca pModelo;
      LIS_tpCondRet lisCondRet;

      LIS_IrInicioLista(pPartida->pModelosPecas);
      lisCondRet = LIS_ProcurarValor(pPartida->pModelosPecas, nome);
      if(lisCondRet != LIS_CondRetOK)
      {
         return PAR_CondRetPecaNaoEncontrada;
      }
      LIS_ObterValor(pPartida->pModelosPecas, (void**) &pModelo);

      PEC_CriarPeca(ppPeca, pModelo, time);

      return PAR_CondRetOK;
   }

   PAR_tpCondRet CriarInstanciaDeRei(tpPartida *pPartida, PEC_tppPeca *ppPeca)
   {
      PEC_CriarPeca(ppPeca, NULL, ALIADA);

      return PAR_CondRetOK;
   }

   PAR_tpCondRet PAR_ObterPeca(PAR_tppPartida pPartida, PEC_tppPeca *ppPeca)
   {
      tpCasa *pCasa;
      TAB_ObterValor(pPartida->pTabuleiro, (void **) &pCasa);
      *ppPeca = pCasa->pPeca;

      return PAR_CondRetOK;
   }

   PAR_tpCondRet PAR_Salvar(PAR_tppPartida ppPartida, char* caminho)
   {
      tpPartida *pPartida = (tpPartida *) ppPartida;
      tpCasa *pCasa;
      int numElementos;
      MPEC_tppModeloPeca *pModeloPeca;

      pCaminho = caminho;

      pFile = fopen(caminho,"w");

      if(pFile == NULL)
         return PAR_CondRetCaminhoErrado;

      fputs("ListaModeloPecas\n",pFile);

      MPEC_SalvarLista(pPartida->pModelosPecas,pFile);

      fputs("\nTabuleiro",pFile);

      fclose(pFile);

      TAB_PercorrerCasas(ppPartida->pTabuleiro, SalvaCasas);

      return PAR_CondRetOK;
   }
   
   PAR_tpCondRet PAR_Carregar(PAR_tppPartida *ppPartida, char* caminho)
   {
      char *line;
      int ehTabuleiro = -1;

      pCaminho = caminho;

      PAR_CriarPartida(ppPartida);

      pFile = fopen(pCaminho,"r");

      if(pFile == NULL)
         return PAR_CondRetCaminhoErrado;

      MEM_Alloc(sizeof(char)*200,(void**)&line);

      while(fgets(line,199,pFile) != NULL)
      {
         char *linhaASerLida;
         MEM_Alloc(sizeof(char)*200,(void**)&linhaASerLida);
         sscanf(line,"%s",linhaASerLida);

         if(strcmp(linhaASerLida,"ListaModeloPecas") == 0)
         {
            ehTabuleiro = 0;
            continue;
         }

         if(strcmp(linhaASerLida,"Tabuleiro") == 0)
         {
            ehTabuleiro = 1;
            continue;
         }

         if(ehTabuleiro == 0)
         {
            MPEC_tppModeloPeca ppModeloPeca;
            LIS_tppLista pPassos;
            char *nomeModelo, *passos;
            MPEC_tpTipoMovimento tipoMovimento;

            MEM_Alloc(sizeof(char)*200,(void**)&nomeModelo);
            MEM_Alloc(sizeof(char)*200,(void**)&passos);

            linhaASerLida = strtok(line, "-");
            strcpy(nomeModelo,linhaASerLida);

            linhaASerLida = strtok(NULL, "-");
            tipoMovimento = (MPEC_tpTipoMovimento) atoi(linhaASerLida);

            linhaASerLida = strtok(NULL, "-");
            strcpy(passos,linhaASerLida);

            ISP_LerPassos(passos,&pPassos);

            PAR_CriarPeca(*ppPartida,nomeModelo,pPassos,tipoMovimento);
         }
         else
         {
            MPEC_tppModeloPeca ppModeloPeca;
            LIS_tppLista pPassos;
            PEC_tpTimePeca time;
            char *nomeCasa, *nomeModelo;

            MEM_Alloc(sizeof(char)*200,(void**)&nomeCasa);
            MEM_Alloc(sizeof(char)*200,(void**)&nomeModelo);

            linhaASerLida = strtok(line, "-");
            strcpy(nomeCasa,linhaASerLida);

            linhaASerLida = strtok(NULL, "-");
            time = (PEC_tpTimePeca) atoi(linhaASerLida);

            linhaASerLida = strtok(NULL, "-");
            strcpy(nomeModelo,linhaASerLida);

            PAR_IrCasa(*ppPartida,nomeCasa);
            PAR_InserirPeca(*ppPartida,nomeModelo,time);
         }
      }

    
   }

/*****  Código das funções encapsuladas no módulo  *****/
   int InserirCasaNoTabuleiro(TAB_tppTabuleiro pTabuleiro, char *nome)
   {
      tpCasa *pCasa = CriarCasa(nome);
      TAB_AlterarValor(pTabuleiro, pCasa);
      return 1;
   }

   tpCasa* CriarCasa(char *nome)
   {
      tpCasa *pCasa;
      MEM_Alloc(sizeof(tpCasa), (void **) &pCasa);
      pCasa->pPeca = NULL;
      pCasa->nome = nome;
   
      return pCasa;
   }

   int SalvaCasas(TAB_tppTabuleiro pTabuleiro, char *pNome)
   {
      if(pTabuleiro != NULL)
      {
         FILE *fp;
         char *destino;
         tpCasa *pCasa;

         TAB_ObterValor(pTabuleiro,(void**)&pCasa);

         if(pCasa != NULL && pCasa->pPeca != NULL)
         {
            MEM_Alloc(sizeof(char)*200,(void**)&destino);

            fp = fopen(pCaminho,"a");

            sprintf(destino,"\n%s-",pCasa->nome);
            fputs(destino,fp);

            PEC_SalvarPeca(pCasa->pPeca,fp);

            fclose(fp);
         }
         return 1;
      }
   }

   void DestruirCasa(void *pValor)
   {
      tpCasa *pCasa = (tpCasa*) pValor;

      PEC_DestruirPeca(&pCasa->pPeca);

      MEM_Free(pCasa);
   }

   void DestruirModeloPecaGenerico(void *pValor)
   {
      MPEC_DestruirModeloPeca((MPEC_tppModeloPeca*) &pValor);
   }
   
   int CompararNomeModeloPeca(void *pValor1, void *pValor2)
   {
      MPEC_tppModeloPeca pModelo1 = (MPEC_tppModeloPeca) pValor1;
      char *nome;
      char *nomeProcurado = (char*) pValor2;

      MPEC_RecuperarNome(pModelo1, &nome);

      return strcmp(nome, nomeProcurado);
   }

/***** FIM do código das funções encapsuladas no módulo  *****/   

/********** Fim do módulo de implementação: Módulo partida **********/
