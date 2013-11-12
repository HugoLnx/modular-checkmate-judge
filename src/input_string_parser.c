/***************************************************************************
*
*  Módulo de definição: ISP  Input String Parser
*
*  Arquivo gerado:              input_string_parser.c
*  Letras identificadoras:      ISP
*
*	Autores:
*     - hg: Hugo Roque
*     - rc: Robert Correa
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Parseia alguns tipos básicos
*
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mem_manager.h"
#include "passo.h"
#include "direcao.h"

#define INPUT_STRING_PARSER_OWN
#include "input_string_parser.h"
#undef INPUT_STRING_PARSER_OWN

#define ANDA_STR "ANDA"
#define VOA_STR  "VOA"

#define SEPARADOR_PASSOS " _"
#define FORMATO_PASSO_STR "[%d]%s"


/***** Protótipos das funções encapuladas no módulo *****/

static int CompararPassosGenerico(void *pValor1, void *pValor2);
static void DestruirPassoGenerico(void *pValor);
static PAS_tppPasso LerPasso(char *passoInput);
static DIR_tpDirecao LerDirecao(char *direcaoInput);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*  Função: ISP Ler tipo de movimento
*  ****/
ISP_tpCondRet ISP_LerTipoMovimento(char *tipoStr, MPEC_tpTipoMovimento *pTipo)
{
   if (strcmp(strupr(tipoStr), VOA_STR) == 0)
   {
      *pTipo = VOA;
   }
   else if (strcmp(strupr(tipoStr), ANDA_STR) == 0)
   {
      *pTipo = ANDA;
   }
   else
   {
      return ISP_CondRetNaoReconhecido;
   }

   return ISP_CondRetOK;
}


/***************************************************************************
*  Função: ISP Ler passos
*  ****/
ISP_tpCondRet ISP_LerPassos(const char *passosStr, LIS_tppLista *ppPassos)
{
   LIS_tppLista passos;
   char *passoStr;
   char *str;
   MEM_Alloc(sizeof(char)*(strlen(passosStr)+1), (void **) &str);
   strcpy(str, passosStr);

   LIS_CriarLista(&passos, DestruirPassoGenerico, CompararPassosGenerico);

   passoStr = strtok(str, SEPARADOR_PASSOS);

   while (passoStr != NULL)
   {
      PAS_tppPasso pPasso;
      pPasso = LerPasso(passoStr);
      LIS_InserirElementoApos(passos, pPasso);
      passoStr = strtok(NULL, SEPARADOR_PASSOS);
   }
   
   *ppPassos = passos;

   return ISP_CondRetOK;
}


/************* Código das funções encapsuladas *************/

/***************************************************************************
*  Função: ISP Ler passo
*  ****/
PAS_tppPasso LerPasso(char *passoInput)
{
   PAS_tppPasso pPasso;
   int *pQnt;
   char *strDirecao;

   MEM_Alloc(sizeof(char)*10, (void **) &strDirecao);
   MEM_Alloc(sizeof(int), (void **) &pQnt);
   sscanf(passoInput, FORMATO_PASSO_STR, pQnt, strDirecao);

   PAS_CriarPasso(&pPasso, LerDirecao(strDirecao), *pQnt);

   return pPasso;
}


/***************************************************************************
*  Função: ISP Ler direção
*  ****/
DIR_tpDirecao LerDirecao(char *direcaoInput)
{
   char *dirNormalizada = strlwr(direcaoInput);

   if (strcmp(dirNormalizada, "norte") == 0)
   {
      return NORTE;
   }
   else if (strcmp(dirNormalizada, "sul") == 0)
   {
      return SUL;
   }
   else if (strcmp(dirNormalizada, "este") == 0)
   {
      return ESTE;
   }
   else if (strcmp(dirNormalizada, "oeste") == 0)
   {
      return OESTE;
   }
   else if (strcmp(dirNormalizada, "nordeste") == 0)
   {
      return NORDESTE;
   }
   else if (strcmp(dirNormalizada, "sudeste") == 0)
   {
      return SUDESTE;
   }
   else if (strcmp(dirNormalizada, "sudoeste") == 0)
   {
      return SUDOESTE;
   }
   else if (strcmp(dirNormalizada, "noroeste") == 0)
   {
      return NOROESTE;
   }
   else
   {
      return (DIR_tpDirecao) -1;
   }
}


/***************************************************************************
*  Função: ISP Destruir passo genérico
*  ****/
void DestruirPassoGenerico(void *pValor)
{
   PAS_DestruirPasso((PAS_tppPasso*) &pValor);
}


/***************************************************************************
*  Função: Comparar passos genérico
*  ****/
int CompararPassosGenerico(void *pValor1, void *pValor2)
{
   int resp;

   PAS_CompararPassos((PAS_tppPasso) pValor1, (PAS_tppPasso) pValor2, &resp);

   return resp;
}

/********** Fim do módulo de implementação: Input String Parser **********/