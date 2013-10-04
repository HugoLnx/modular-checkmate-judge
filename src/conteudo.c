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

#define CONTEUDO_OWN
#include "conteudo.h"
#undef CONTEUDO_OWN

/***********************************************************************
*  Tipo de dados: CON Conteudo
***********************************************************************/

   typedef struct stConteudo {

         char * pValor;
               /* Valor do conteúdo */
   } CON_tpConteudo;

   /*****  Código das funções exportadas pelo módulo  *****/


   CON_tpCondRet CON_CriarConteudo(CON_tppConteudo *ppConteudo, char *pValor)
   {
		CON_tpConteudo *pConteudo = (CON_tpConteudo *)malloc(sizeof(CON_tpConteudo));

		if(pConteudo == NULL)
			return CON_CondRetFaltouMemoria;

		pConteudo->pValor = pValor;

		*ppConteudo = pConteudo;

		return CON_CondRetOK;


   }