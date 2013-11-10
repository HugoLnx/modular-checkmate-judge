/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              PASSO.C
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
#include "peca.h"

#include <string.h>

#define PASSO_OWN
#include "passo.h"
#undef PASSO_OWN


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

typedef struct PAR_stPasso
{
   DIR_tpDirecao direcao;
   int quantidade;
} tpPasso;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
   PAS_tpCondRet PAS_CriarPasso(PAS_tppPasso *ppPasso, DIR_tpDirecao direcao, int quantidade)
   {
      tpPasso *pPasso;
      MEM_Alloc(sizeof(tpPasso), (void**) &pPasso);
      pPasso->direcao = direcao;
      pPasso->quantidade = quantidade;

      *ppPasso = (PAS_tppPasso) pPasso;

      return PAS_CondRetOK;
   }

   PAS_tpCondRet PAS_DestruirPasso(PAS_tppPasso *ppPasso)
   {
      if (ppPasso == NULL || *ppPasso == NULL)
      {
         return PAS_CondRetMatrizNaoExiste;
      }

      MEM_Free(*ppPasso);

      return PAS_CondRetOK;
   }

   PAS_tpCondRet PAS_CompararPassos(PAS_tppPasso pPassoParm1, PAS_tppPasso pPassoParm2, int *pResposta)
   {
      tpPasso *pPasso1 = (tpPasso*) pPassoParm1;
      tpPasso *pPasso2 = (tpPasso*) pPassoParm2;
      *pResposta = pPasso1->direcao == pPasso2->direcao 
                && pPasso1->quantidade == pPasso2->quantidade;

      return PAS_CondRetOK;
   }

   PAS_tpCondRet PAS_Percorrer(PAS_tppPasso pPassoParm, int (*fazerNaDirecao)(DIR_tpDirecao direcao))
   {
      int continuar = 1;
      int i;
      tpPasso *pPasso = (tpPasso*) pPassoParm;

      i = 0;
      while (continuar && (pPasso->quantidade == 0 || i < pPasso->quantidade))
      {
         continuar = fazerNaDirecao(pPasso->direcao);
      }

      return PAS_CondRetOK;
   }

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/