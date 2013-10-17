/***************************************************************************
*
*  Módulo de implementação: VER  Conteúdo do módulo
*
*  Arquivo gerado:              vertice.h
*  Letras identificadoras:      VER
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

#define VERTICE_OWN
#include "vertice.h"
#undef VERTICE_OWN

/***********************************************************************
*  Tipo de dados: VER Conteudo
***********************************************************************/

typedef struct VER_stConteudo {

	char Valor[255];
		/* Valor do conteúdo */

} tpConteudo;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*  Função: VER Criar conteúdo
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
*  Função: VER Destruir conteúdo
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
*  Função: VER Obter valor do conteúdo
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
*  Função: VER Alterar valor do conteúdo
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

/********** Fim do módulo de implementação: VER Conteudo **********/