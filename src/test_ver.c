#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"

#include    "vertice.h"

static const char * CRIAR_VERTICE_CMD       = "=criarConteudo"    ;
static const char * DESTRUIR_VERTICE_CMD		= "=destruirConteudo" ;
static const char * OBTER_VALOR_CMD				= "=obterValor"		 ;
static const char * ALTER_VALOR_CMD				= "=alterarValor"     ;

/* Tamanho do vetor de testes */
#define DIM_VT_VERTICE   10

/* Tamanho do buffer do valor do conteudo */
#define DIM_BUFFER_VALOR  255	

/* Constante string para representar null */
#define SIMBOLO_PARA_NULL "!N!"

VER_tppConteudo vtConteudos[DIM_VT_VERTICE];

/***********************************************************************
*
*  Função: TVER Testar conteudo
*
*     Comandos disponíveis:
*
*     =criarConteudo          inxConteudo	string      CondRetEsp
*     =destruirConteudo       inxConteudo               CondRetEsp
*     =obterValor             inxConteudo   string      CondRetEsp
*     =alterarValor           inxConteudo   string      CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
	int inxConteudo   = -1,
		numLidos      = -1,
		CondRetEsp    = -1;

	TST_tpCondRet CondRet;
	VER_tppConteudo ppConteudo = NULL;

	/* Testar CriarConteudo */

	if (strcmp(ComandoTeste, CRIAR_VERTICE_CMD) == 0)
	{
		char dado[DIM_BUFFER_VALOR];  
		numLidos = LER_LerParametros("isi", &inxConteudo, dado, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		}

		CondRet = (TST_tpCondRet) VER_CriarConteudo(&vtConteudos[inxConteudo], dado);

		if(CondRet == VER_CondRetOK)
		{
			CondRet = TST_CompararPonteiroNulo(1, vtConteudos[inxConteudo], "Erro em ponteiro novo conteudo.");
			return CondRet;
		}

		return TST_CompararInt(CondRetEsp, CondRet, "Condição de retorno inesperada ao criar um novo conteúdo");
	}

	/* Testar DestruirConteudo */

	if (strcmp(ComandoTeste, DESTRUIR_VERTICE_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii", &inxConteudo, &CondRetEsp);

		if (numLidos != 2)
		{
			return TST_CondRetParm;
		} 

		CondRet = (TST_tpCondRet) VER_DestruirConteudo(&vtConteudos[inxConteudo]);

		if(CondRet ==  VER_CondRetOK)
		{
			CondRet = TST_CompararPonteiroNulo(0, vtConteudos[inxConteudo], "Erro em ponteiro ao destruir conteudo.");
			return CondRet;
		}

		return TST_CompararInt(CondRetEsp, CondRet, "Condição de retorno inesperada ao destruir o conteúdo.");

	}

	/* Testar ObterValorDoConteudo */

	if (strcmp(ComandoTeste, OBTER_VALOR_CMD) == 0)
	{
		char *pDadoEsperado = (char*) malloc(sizeof(char) * DIM_BUFFER_VALOR);
		char *pDadoObtido;

		numLidos = LER_LerParametros("isi", &inxConteudo, pDadoEsperado, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		}

		if(strcmp(pDadoEsperado, SIMBOLO_PARA_NULL) == 0)
		{
			pDadoEsperado = NULL;
		}

		CondRet = (TST_tpCondRet) VER_ObterValorDoConteudo(vtConteudos[inxConteudo], &pDadoObtido);

		if(CondRet ==  VER_CondRetOK)
		{
			CondRet = TST_CompararString(pDadoEsperado,pDadoObtido,"Dado esperado não é igual ao obtido");
			return CondRet;	
		}
		else
		{
			if (pDadoObtido != NULL)
			{
				return TST_NotificarFalha("Não foi obtido null como valor ao ocorrer um erro."); 
			}

			return TST_CompararInt(CondRetEsp, CondRet, "Condição de retorno inesperada na obtenção do valor.");
		}
	}

	/* Testar AlterarValorDoConteudo */

	if (strcmp(ComandoTeste, ALTER_VALOR_CMD) == 0)
	{
		char pDadoParaAlterar[DIM_BUFFER_VALOR];
		char* pDadoObtido;

		numLidos = LER_LerParametros("isi", &inxConteudo, pDadoParaAlterar, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		} 

		CondRet = (TST_tpCondRet) VER_AlterarValorDoConteudo(vtConteudos[inxConteudo], pDadoParaAlterar);

		if(CondRet == VER_CondRetOK)
		{
			VER_ObterValorDoConteudo(vtConteudos[inxConteudo], &pDadoObtido);
			CondRet = TST_CompararString(pDadoParaAlterar, pDadoObtido, "Dado não foi alterado");
			return CondRet;	
		}

		return TST_CompararInt(CondRetEsp, CondRet, "Condição de retorno inesperada na alteração do valor.");
	}

	return TST_CondRetNaoConhec ;

}