/***************************************************************************
*
*  M�dulo de implementa��o: CON  Conte�do do m�dulo
*
*  Arquivo gerado:              conteudo.h
*  Letras identificadoras:      CON
*
*	Autores:
*     - Hugo Roque: hg
*     - Robert Corr�a: rc
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data        Observa��es
*     1.0     rc       02/out/13   Cria��o do m�dulo e as opera��es b�sicas.
*     1.1     hg       05/out/13   Checagem de erros caso o conte�do n�o tenha sido criado.
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

/***************************************************************************
*  Fun��o: CON Criar conte�do
*  ****/
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

/***************************************************************************
*  Fun��o: CON Destruir conte�do
*  ****/
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

/***************************************************************************
*  Fun��o: CON Obter valor do conte�do
*  ****/
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

/***************************************************************************
*  Fun��o: CON Alterar valor do conte�do
*  ****/
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