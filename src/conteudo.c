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

   typedef struct stConteudo {

         char Valor[255];
               /* Valor do conte�do */
   } CON_tpConteudo;

   /*****  C�digo das fun��es exportadas pelo m�dulo  *****/


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