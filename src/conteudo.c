/***************************************************************************
*
*  Módulo de implementação: CON  Conteúdo do módulo
*
*  Arquivo gerado:              conteudo.h
*  Letras identificadoras:      CON
*
*	Autores:
*     - Hugo Roque: hg
*     - Robert Corrêa: rc
*
*  Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1.0     rc       02/out/13   Criação do módulo e as operações básicas.
*     1.1     hg       05/out/13   Checagem de erros caso o conteúdo não tenha sido criado.
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

/***************************************************************************
*  Função: CON Criar conteúdo
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
*  Função: CON Destruir conteúdo
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
*  Função: CON Obter valor do conteúdo
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
*  Função: CON Alterar valor do conteúdo
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

/********** Fim do módulo de implementação: CON Conteudo **********/