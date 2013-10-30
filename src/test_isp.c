#include    <string.h>
#include    <stdio.h>
#include    "mem_manager.h"

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "input_string_parser.h"


static const char *LER_PASSOS_CMD       = "=lerPassos"        ;
static const char *LER_BOOL_CMD   = "=lerBooleano"      ;
static const char *LER_TIPO_MOVIMENTO_CMD         = "=lerTipoMovimento" ;
static const char *FIM_CMD              = "=fim"              ;

/*****Protótipos das funções encapuladas no módulo *****/
   static char* AlocarEspacoParaNome();

/***** Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
* Função: TGRA Testar grafo
*
*    Comandos disponíveis:
*
*    =criarGrafo                   CondRetEsp
*    =destruirGrafo                CondRetEsp
*    =insVertice                   nome valor   CondRetEsp
*    =insAresta                    nome vertice CondRetEsp
*    =obterValor                   string CondRetEsp
*    =alterarValor                 string CondRetEsp
*    =excluirVertice               CondRetEsp
*    =irOrigem                     nome CondRetEsp
*    =irVertice                    nome CondRetEsp
*    =irPelaAresta                 nome CondRetEsp
*    =destruirCorr                 CondRetEsp
*    =destruirAresta               nome CondRetEsp
*    =tornarOrigem                 CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {
      int numLidos   = -1,
          CondRetEsp = -1;

      TST_tpCondRet CondRet;

      /*Testar CriarGrafo */

         if (strcmp (ComandoTeste, LER_TIPO_MOVIMENTO_CMD) == 0)
         {
            char *tipoStr;
            int tipoEsperado;
            TAB_tpTipoMovimento tipoObtido;
            MEM_Alloc(sizeof(tipoStr)*5, (void **) &tipoStr);

            numLidos = LER_LerParametros("sii", tipoStr, &tipoEsperado, &CondRetEsp);

            if (numLidos != 3)
            {
               return TST_CondRetParm;
            }

            CondRet = ISP_LerTipoMovimento(tipoStr, &tipoObtido);

            if(CondRet ==  ISP_CondRetOK)
            {
               TST_CompararInt(tipoEsperado, (int) tipoObtido, "Não foi obtido o tipo esperado.");
            }

            return CondRet;
         }


        /* Finalizar o teste */

       else if (strcmp(ComandoTeste, FIM_CMD) == 0)
         {
            MEM_LiberarTodaMemoriaAlocada();

            return TST_CondRetOK;
         }

      return TST_CondRetNaoConhec;

   }


/***** Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
* Função: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor(void *pValor)
   {
      MEM_Free(pValor);
   }

/**********Fim do módulo de implementação: TGRA Teste Grafo direcionado **********/

