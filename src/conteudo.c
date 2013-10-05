/***************************************************************************
*
*  M�dulo de implementa��o: <abrevia��o>  <estrutura manipulada pelo m�dulo>
*
*  Arquivo gerado:              <nome-do-arquivo>.c
*  Letras identificadoras:      <abrevia��o>
*
*	Autores:
*     - <nick>: <nome>
*     - <nick>: <nome>
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1       <nick>   <data>      <observa��es>
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
	/* Valor do conte�do */
} tpConteudo;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


// assertiva de entrada, o ponteiro n�o aponta para um
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

/********** Fim do m�dulo de implementa��o: CON Conteudo **********/