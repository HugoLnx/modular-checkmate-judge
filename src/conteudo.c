/***************************************************************************
*
*  Módulo de implementação: <abreviação>  <estrutura manipulada pelo módulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.c
*  Letras identificadoras:      <abreviação>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1       <nick>   <data>      <observações>
*
***************************************************************************/

#include <stdlib.h>
#include <string.h>

#define CONTEUDO_OWN
#include "conteudo.h"
#undef CONTEUDO_OWN

/***********************************************************************
*  Tipo de dados: CON Conteudo
***********************************************************************/

typedef struct CON_stConteudo {

	char Valor[255];
	/* Valor do conteúdo */
} tpConteudo;

/*****  Código das funções exportadas pelo módulo  *****/


// assertiva de entrada, o ponteiro não aponta para um
// conteudo q foi criado anteriormente
CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor)
{
	tpConteudo *pConteudo;

   pConteudo = (tpConteudo *)malloc(sizeof(tpConteudo));
	if(pConteudo == NULL)
		return CON_CondRetFaltouMemoria;

	strcpy(pConteudo->Valor,pValor);

	*ppConteudo = pConteudo;

	return CON_CondRetOK;
}

CON_tpCondRet CON_DestruirConteudo(CON_tppConteudo *ppConteudo)
{
	tpConteudo *pConteudo;
	pConteudo = *ppConteudo;

   if (*ppConteudo == NULL)
   {
      return CON_CondRetOK;
   }

	free(pConteudo);
	pConteudo = NULL;
	*ppConteudo = NULL;

	return CON_CondRetOK;
}

CON_tpCondRet CON_ObterValorDoConteudo(CON_tppConteudo pConteudoParm, char **ppValor)
{
	tpConteudo *pConteudo = pConteudoParm;

   if (pConteudo == NULL)
   {
      *ppValor = NULL;
      return CON_CondRetConteudoNaoExiste;
   }

	*ppValor = pConteudo->Valor;

	return CON_CondRetOK;
}

CON_tpCondRet CON_AlterarValorDoConteudo(CON_tppConteudo pConteudoParm, char *pValor)
{
	tpConteudo *pConteudo = pConteudoParm;
   
   if (pConteudo == NULL)
   {
      return CON_CondRetConteudoNaoExiste;
   }

	strcpy(pConteudo->Valor,pValor);
	return CON_CondRetOK;
}

/********** Fim do módulo de implementação: CON Conteudo **********/