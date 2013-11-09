/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              DIRECAO.C
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
#include "mem_manager.h"
#include <string.h>

#define DIRECAO_OWN
#include "direcao.h"
#undef DIRECAO_OWN


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


   DIR_tpCondRet DIR_DirecaoComoString(DIR_tpDirecao direcao, char **pRetornoStr)
   {
      MEM_Alloc(sizeof(char)*2, (void **) pRetornoStr);
      switch(direcao)
      {
         case NORTE:     *pRetornoStr = "N" ; break;
         case ESTE:      *pRetornoStr = "E" ; break;
         case SUL:       *pRetornoStr = "S" ; break;
         case OESTE:     *pRetornoStr = "O" ; break;
         case NORDESTE:  *pRetornoStr = "NE"; break;
         case SUDESTE:   *pRetornoStr = "SE"; break;
         case SUDOESTE:  *pRetornoStr = "SO"; break;
         case NOROESTE:  *pRetornoStr = "NO"; break;
         default: return DIR_CondRetNaoPodeSeTornarString; break;
      }
      return DIR_CondRetOK;
   }


   DIR_tpCondRet DIR_DirecaoOrientadaPara(DIR_tpDirecao direcao,
      DIR_tpDirecao orientacao, DIR_tpDirecao *dirRetorno)
   {
      *dirRetorno = (DIR_tpDirecao) ((int) direcao + (int) orientacao) % TOTAL_DIRECOES;
      return DIR_CondRetOK;
   }

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/