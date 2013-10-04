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

   typedef struct stConteudo {

         char Valor[255];
               /* Valor do conteúdo */
   } CON_tpConteudo;

   /*****  Código das funções exportadas pelo módulo  *****/


CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor)
   {
		CON_tpConteudo *pConteudo = (CON_tpConteudo *)malloc(sizeof(CON_tpConteudo));

		if(pConteudo == NULL)
			return CON_CondRetFaltouMemoria;

		strcpy(pConteudo->Valor,pValor);

		*ppConteudo = pConteudo;

		return CON_CondRetOK;


   }

CON_tpCondRet CON_DestruirConteudo(CON_tppConteudo *ppConteudo)
{
	CON_tpConteudo *pConteudo;
	pConteudo = *ppConteudo;

	free(pConteudo);
	pConteudo = NULL;
	*ppConteudo = NULL;

	return CON_CondRetOK;
}

CON_tpCondRet CON_ObterValorDoConteudo(CON_tppConteudo ppConteudo, char **ppValor)
{
	CON_tpConteudo *pConteudo;
	pConteudo = ppConteudo;

	*ppValor = pConteudo->Valor;

	return CON_CondRetOK;
}