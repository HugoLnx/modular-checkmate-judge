#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"

#include    "conteudo.h"

static const char * CRIAR_CONTEUDO_CMD       = "=criarConteudo"        ;
static const char * DESTRUIR_CONTEUDO_CMD		= "=destruirConteudo"     ;
static const char * OBTER_VALOR_CMD				= "=obterValor"			  ;
static const char * ALTER_VALOR_CMD				= "=alterarValor"         ;

#define TRUE  1
#define FALSE 0

/* Tamanho do vetor de testes */
#define DIM_VT_CONTEUDO   10

/* Tamanho do buffer do valor do conteudo */
#define DIM_BUFFER_VALOR  255	

/* Constante string para representar null */
#define SIMBOLO_PARA_NULL "!N!"

#define VAZIO     0
#define NAO_VAZIO 1

CON_tppConteudo   vtConteudos[DIM_VT_CONTEUDO];

/***********************************************************************
*
*  Função: TCON Testar conteudo
*
*     Comandos disponíveis:
*
*     =criarConteudo				inxConteudo	string		CondRetEsp
*     =destruirConteudo			inxConteudo					CondRetEsp
*     =obterValor             inxConteudo string		CondRetEsp
*     =alterarValor           inxConteudo string		CondRetEsp
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

   }

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

   }

   /* Testar ObterValorDoConteudo */

   if (strcmp(ComandoTeste, OBTER_VALOR_CMD) == 0)
   {
      char *dado_esperado = (char*) malloc(sizeof(char) * DIM_BUFFER_VALOR);
      char *dado_obtido;

      numLidos = LER_LerParametros( "isi", &inxConteudo, dado_esperado, &CondRetEsp);

      if (numLidos != 3)
      {
         return TST_CondRetParm ;
      }

      if(strcmp(dado_esperado, SIMBOLO_PARA_NULL) == 0)
      {
         dado_esperado = NULL;
      }

      CondRet = (TST_tpCondRet) CON_ObterValorDoConteudo(vtConteudos[inxConteudo], &dado_obtido);

      if(CondRet ==  CON_CondRetOK)
      {
         CondRet = TST_CompararString(dado_esperado,dado_obtido,"Dado esperado não é igual ao obtido");
         return CondRet;	
      }
      else
      {
         if (dado_obtido != NULL)
         {
            return TST_NotificarFalha("Não foi obtido null como valor ao ocorrer um erro."); 
         }

         return TST_CompararInt(CondRetEsp, CondRet, "Não ocorreu o erro esperado na obtenção do valor.");
      }

      return TST_CondRetErro;

   }

   /* Testar AlterarValorDoConteudo */

   if (strcmp(ComandoTeste, ALTER_VALOR_CMD) == 0)
   {
      char dado_esperado[DIM_BUFFER_VALOR];
      char dado_para_alterar[DIM_BUFFER_VALOR];
      char* dado_obtido;
      numLidos = LER_LerParametros( "isi", &inxConteudo, dado_para_alterar, &CondRetEsp);

      if (numLidos != 3)
      {
         return TST_CondRetParm ;
      } 

      CondRet = (TST_tpCondRet) CON_AlterarValorDoConteudo(vtConteudos[inxConteudo], dado_para_alterar);

      if(CondRet == CON_CondRetOK)
      {
         CON_ObterValorDoConteudo(vtConteudos[inxConteudo],&dado_obtido);
         CondRet = TST_CompararString(dado_para_alterar,dado_obtido,"Dado não foi alterado");
         return CondRet;	
      }

       return TST_CompararInt(CondRetEsp, CondRet, "Não ocorreu o erro esperado na alteração do valor.");

   }

   return TST_CondRetNaoConhec ;

}