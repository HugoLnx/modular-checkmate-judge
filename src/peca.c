/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              PECA.C
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
#include <string.h>
#include "lista.h"
#include "peca.h"


typedef struct stMovimento {
   LIS_tppLista passos;
   PEC_tpTipoMovimento tipo;
} PEC_tpMovimento;

typedef struct stModeloPeca {
   PEC_tpMovimento *pMovimento;
   char *nome;
} PEC_tpModeloPeca;

typedef struct stPeca {
   PEC_tpModeloPeca *pModelo;
   PEC_tpTimePeca time;
} PEC_stPeca;


#define PECA_OWN
#include "peca.h"
#undef PECA_OWN

/********** Fim do módulo de implementação: Módulo matriz **********/