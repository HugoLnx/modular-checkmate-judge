/***************************************************************************
*
*  M�dulo de defini��o: DIR  Dire��o
*
*  Arquivo gerado:              direcao.c
*  Letras identificadoras:      DIR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Manipula��o b�sica de dire��o
*
***************************************************************************/

#include <stdio.h>
#include "mem_manager.h"
#include <string.h>

#define DIRECAO_OWN
#include "direcao.h"
#undef DIRECAO_OWN


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*  Fun��o: DIR Dire��o como string
*  ****/
   DIR_tpCondRet DIR_DirecaoComoString(DIR_tpDirecao direcao, char **pRetornoStr)
   {
      MEM_Alloc(sizeof(char)*10, (void **) pRetornoStr);
      if (pRetornoStr == NULL)
      {
         return DIR_CondRetFaltouMemoria;
      }

      switch(direcao)
      {
         case NORTE:     *pRetornoStr = "NORTE" ; break;
         case ESTE:      *pRetornoStr = "ESTE" ; break;
         case SUL:       *pRetornoStr = "SUL" ; break;
         case OESTE:     *pRetornoStr = "OEST" ; break;
         case NORDESTE:  *pRetornoStr = "NORDEST"; break;
         case SUDESTE:   *pRetornoStr = "SUDESTE"; break;
         case SUDOESTE:  *pRetornoStr = "SUSOESTE"; break;
         case NOROESTE:  *pRetornoStr = "NOROESTE"; break;
         default: return DIR_CondRetNaoPodeSeTornarString; break;
      }
      return DIR_CondRetOK;
   }



/***************************************************************************
*  Fun��o: DIR Dire��o orientada para
*  ****/
   DIR_tpCondRet DIR_DirecaoOrientadaPara(DIR_tpDirecao direcao,
      DIR_tpDirecao orientacao, DIR_tpDirecao *dirRetorno)
   {
      *dirRetorno = (DIR_tpDirecao) ((int) direcao + (int) orientacao) % TOTAL_DIRECOES;
      return DIR_CondRetOK;
   }

/********** Fim do m�dulo de implementa��o: M�dulo Dire��o **********/