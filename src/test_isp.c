#include    <string.h>
#include    <stdio.h>
#include    "mem_manager.h"

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "input_string_parser.h"

#define MAX_PASSOS     5
#define MAX_PASSOS_STR 50
#define MAX_TIPO_STR   5

#define TRUE  1
#define FALSE 0


static const char *LER_PASSOS_CMD                 = "=lerPassos"        ;
static const char *LER_BOOL_CMD                   = "=lerBooleano"      ;
static const char *LER_TIPO_MOVIMENTO_CMD         = "=lerTipoMovimento" ;
static const char *FIM_CMD                        = "=fim"              ;

static const TAB_tpPasso PASSOS[][MAX_PASSOS] = {
   {{NORTE, 2}},
   {{SUL, 2}, {ESTE, 5}},
   {{OESTE, 2}, {NOROESTE, 1}, {ESTE, 0}}
};

static const int PASSOS_SIZE[] = {1, 2, 3};

/*****Prot�tipos das fun��es encapuladas no m�dulo *****/
   static char* AlocarEspacoParaNome();
   static LIS_tppLista CriarListaPassos(const TAB_tpPasso *passos, const int tamanho);
   static void DestruirValor(void *pValor);

/***** C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
* Fun��o: TGRA Testar grafo
*
*    Comandos dispon�veis:
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

      /*Testar Ler tipo de movimento*/

         if (strcmp (ComandoTeste, LER_TIPO_MOVIMENTO_CMD) == 0)
         {
            char *tipoStr;
            int tipoEsperado;
            TAB_tpTipoMovimento tipoObtido;
            MEM_Alloc(sizeof(tipoStr)*MAX_TIPO_STR, (void **) &tipoStr);

            numLidos = LER_LerParametros("sii", tipoStr, &tipoEsperado, &CondRetEsp);

            if (numLidos != 3)
            {
               return TST_CondRetParm;
            }

            CondRet = ISP_LerTipoMovimento(tipoStr, &tipoObtido);

            if(CondRet ==  ISP_CondRetOK)
            {
               TST_CompararInt(tipoEsperado, (int) tipoObtido, "N�o foi obtido o tipo esperado.");
            }

            return CondRet;
         }

         
      /*Testar Ler passos*/

         if (strcmp(ComandoTeste, LER_PASSOS_CMD) == 0)
         {
            char *passosStr;
            int iPassosEsperado;
            LIS_tppLista pPassosEsperado;
            LIS_tppLista pPassosObtido;
            MEM_Alloc(sizeof(passosStr)*MAX_PASSOS_STR, (void **) &passosStr);

            numLidos = LER_LerParametros("sii", passosStr, &iPassosEsperado, &CondRetEsp);

            if (numLidos != 3)
            {
               return TST_CondRetParm;
            }

            pPassosEsperado = CriarListaPassos(PASSOS[iPassosEsperado], PASSOS_SIZE[iPassosEsperado]);
            
            CondRet = ISP_LerPassos(passosStr, &pPassosObtido);
            
            if (CondRet ==  ISP_CondRetOK)
            {
               if (!ListaDePassosSaoIguais(pPassosEsperado, pPassosObtido))
               {
                  TST_NotificarFalha("A lista de passos obtida n�o � igual � esperada");
                  return TST_CondRetErro;
               }
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


/***** C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
* Fun��o: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor(void *pValor)
   {
      MEM_Free(pValor);
   }

   LIS_tppLista CriarListaPassos(const TAB_tpPasso *passos, const int tamanho)
   {
      int i;
      LIS_tppLista pPassos;
      LIS_CriarLista(&pPassos, DestruirValor, NULL);

      for (i = 0; i < tamanho; i++)
      {
         TAB_tpPasso *pPasso;
         MEM_Alloc(sizeof(TAB_tpPasso), (void **) &pPasso);
         *pPasso = passos[i];
         LIS_InserirElementoApos(pPassos, pPasso);
      }

      return pPassos;
   }

   int ListaDePassosSaoIguais(LIS_tppLista pPassos1, LIS_tppLista pPassos2)
   {
      TAB_tpPasso *pPasso1;
      TAB_tpPasso *pPasso2;
      LIS_tpCondRet ret1 = LIS_CondRetOK;
      LIS_tpCondRet ret2 = LIS_CondRetOK;

      LIS_IrInicioLista(pPassos1);
      LIS_IrInicioLista(pPassos2);

      while (ret1 == LIS_CondRetOK && ret2 == LIS_CondRetOK)
      {
         LIS_ObterValor(pPassos1, (void **) &pPasso1);
         LIS_ObterValor(pPassos2, (void **) &pPasso2);

         if (pPasso1->direcao != pPasso2->direcao || pPasso1->quantidade != pPasso2->quantidade)
         {
            return FALSE;
         }
         
         ret1 = LIS_AvancarElementoCorrente(pPassos1, 1);
         ret2 = LIS_AvancarElementoCorrente(pPassos2, 1);
      }

      if (ret1 != ret2)
      {
         return FALSE;
      }

      return TRUE;
   }

/**********Fim do m�dulo de implementa��o: TGRA Teste Grafo direcionado **********/

