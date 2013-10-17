/***************************************************************************
*
*  M�dulo de implementa��o: VER  Conte�do do m�dulo
*
*  Arquivo gerado:              vertice.h
*  Letras identificadoras:      VER
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

#define VERTICE_OWN
#include "vertice.h"
#undef VERTICE_OWN

/***********************************************************************
*  Tipo de dados: VER Conteudo
***********************************************************************/

typedef struct VER_stConteudo {

	char Valor[255];
		/* Valor do conte�do */

} tpConteudo;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*  Fun��o: VER Criar conte�do
*  ****/
VER_tpCondRet VER_CriarConteudo(VER_tppConteudo *ppConteudo, char *pValor)
{
	tpConteudo *pConteudo;

	pConteudo = (tpConteudo*)malloc(sizeof(tpConteudo));
	if(pConteudo == NULL)
   {
		return VER_CondRetFaltouMemoria;
   }

	strcpy(pConteudo->Valor, pValor);

	*ppConteudo = pConteudo;

	return VER_CondRetOK;
}

/***************************************************************************
*  Fun��o: VER Destruir conte�do
*  ****/
VER_tpCondRet VER_DestruirConteudo(VER_tppConteudo *ppConteudo)
{
	tpConteudo *pConteudo;
	pConteudo = *ppConteudo;

	if (*ppConteudo == NULL)
	{
		return VER_CondRetOK;
	}

	free(pConteudo);
	pConteudo = NULL;
	*ppConteudo = NULL;

	return VER_CondRetOK;
}

/***************************************************************************
*  Fun��o: VER Obter valor do conte�do
*  ****/
VER_tpCondRet VER_ObterValorDoConteudo(VER_tppConteudo pConteudoParm, char **ppValor)
{
	tpConteudo *pConteudo = pConteudoParm;

	if (pConteudo == NULL)
	{
		*ppValor = NULL;
		return VER_CondRetConteudoNaoExiste;
	}

	*ppValor = pConteudo->Valor;

	return VER_CondRetOK;
}

/***************************************************************************
*  Fun��o: VER Alterar valor do conte�do
*  ****/
VER_tpCondRet VER_AlterarValorDoConteudo(VER_tppConteudo pConteudoParm, char *pValor)
{
	tpConteudo *pConteudo = pConteudoParm;

	if (pConteudo == NULL)
	{
		return VER_CondRetConteudoNaoExiste;
	}

	strcpy(pConteudo->Valor, pValor);
	return VER_CondRetOK;
}

/********** Fim do m�dulo de implementa��o: VER Conteudo **********/