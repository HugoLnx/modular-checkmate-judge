#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"

#include    "conteudo.h"

static const char * CRIAR_CONTEUDO_CMD          = "=criarConteudo"        ;
static const char * DESTRUIR_CONTEUDO_CMD		= "=destruirConteudo"     ;
static const char * OBTER_VALOR_CMD				= "=obterValor"			  ;
static const char * ALTER_VALOR_CMD				= "=alterarValor"         ;

#define TRUE  1
#define FALSE 0

/* Tamanho do vetor de testes */
#define DIM_VT_CONTEUDO   10

/* Tamanho do buffer do valor do conteudo */
#define DIM_BUFFER_VALOR  255	


#define VAZIO     0
#define NAO_VAZIO 1

CON_tppConteudo   vtConteudos[DIM_VT_CONTEUDO];

/***********************************************************************
*
*  Função: TCON Testar conteudo
*
*     Comandos disponíveis:
*
*     =criarConteudo				inxConteudo	string			CondRetEsp
*     =destruirConteudo				inxConteudo					CondRetEsp
*     =obterValor                   inxConteudo string			CondRetEsp
*     =alterarValor                 inxConteudo string  string  CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
	int inxConteudo   = -1,
		numLidos      = -1,
		CondRetEsp    = -1;

	TST_tpCondRet CondRet;
	CON_tppConteudo ppConteudo = NULL;

	/* Testar CriarConteudo */

	if (strcmp(ComandoTeste, CRIAR_CONTEUDO_CMD) == 0)
	{
		char dado[DIM_BUFFER_VALOR];  
		numLidos = LER_LerParametros( "isi", &inxConteudo, dado, &CondRetEsp);

		if (numLidos != 3 )
		{
			return TST_CondRetParm ;
		}

		CondRet = (TST_tpCondRet)CON_CriarConteudo(&ppConteudo, dado);

		if( CondRet ==  CON_CondRetOK )
		{
			vtConteudos[ inxConteudo ] = ppConteudo;
			CondRet = TST_CompararPonteiroNulo(1, vtConteudos[inxConteudo], "Erro em ponteiro novo conteudo.");
			return CondRet;
		}

		return TST_CondRetErro;

	} /* fim ativa: Testar CriarConteudo */

	/* Testar DestruirConteudo */

	if (strcmp(ComandoTeste, DESTRUIR_CONTEUDO_CMD) == 0)
	{
		numLidos = LER_LerParametros( "ii", &inxConteudo, &CondRetEsp);

		if (numLidos != 2)
		{
			return TST_CondRetParm ;
		} 

		CondRet = (TST_tpCondRet) CON_DestruirConteudo(&(vtConteudos[inxConteudo]));

		if(CondRet ==  CON_CondRetOK)
		{
			CondRet = TST_CompararPonteiroNulo(0, vtConteudos[inxConteudo], "Erro em ponteiro ao destruir conteudo.");
			return CondRet;
		}

		return TST_CondRetErro;

	} /* fim ativa: Testar CriarConteudo */



	return TST_CondRetNaoConhec ;

} /* Fim função: TCON &Testar conteudo */