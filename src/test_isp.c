#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "input_string_parser.h"
#include    "passo.h"
#include    "mem_manager.h"

#define MAX_PASSOS     5
#define MAX_PASSOS_STR 50
#define MAX_TIPO_STR   5

#define TRUE  1
#define FALSE 0


static const char *LER_PASSOS_CMD                 = "=lerPassos"        ;
static const char *LER_BOOL_CMD                   = "=lerBooleano"      ;
static const char *LER_TIPO_MOVIMENTO_CMD         = "=lerTipoMovimento" ;
static const char *FIM_CMD                        = "=fim"              ;

/*****Protótipos das funções encapuladas no módulo *****/
   static char* AlocarEspacoParaNome();
   static LIS_tppLista CriarListaPassos(const PAS_tppPasso passos, const int tamanho);
   static void DestruirValor(void *pValor);

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
      
      PAS_tppPasso PASSOS[3][MAX_PASSOS];
      int PASSOS_SIZE[3];

      PAS_CriarPasso(&PASSOS[0][0], NORTE, 2);
      PASSOS_SIZE[0] = 1;

      PAS_CriarPasso(&PASSOS[1][0], SUL, 2);
      PAS_CriarPasso(&PASSOS[1][1], ESTE, 5);
      PASSOS_SIZE[1] = 2;
      
      PAS_CriarPasso(&PASSOS[2][0], OESTE, 2);
      PAS_CriarPasso(&PASSOS[2][1], NOROESTE, 1);
      PAS_CriarPasso(&PASSOS[2][2], ESTE, 0);
      PASSOS_SIZE[2] = 3;

      /*Testar Ler tipo de movimento*/

         if (strcmp (ComandoTeste, LER_TIPO_MOVIMENTO_CMD) == 0)
         {
            char *tipoStr;
            int tipoEsperado;
            PEC_tpTipoMovimento tipoObtido;
            MEM_Alloc(sizeof(tipoStr)*MAX_TIPO_STR, (void **) &tipoStr);

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
                  TST_NotificarFalha("A lista de passos obtida não é igual à esperada");
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

   LIS_tppLista CriarListaPassos(PAS_tppPasso *passos, const int tamanho)
   {
      int i;
      LIS_tppLista pPassos;
      LIS_CriarLista(&pPassos, DestruirValor, NULL);

      for (i = 0; i < tamanho; i++)
      {
         PAS_tppPasso pPasso;
         pPasso = *(passos + i);
         LIS_InserirElementoApos(pPassos, pPasso);
      }

      return pPassos;
   }

   int ListaDePassosSaoIguais(LIS_tppLista pPassos1, LIS_tppLista pPassos2)
   {
      PAS_tppPasso pPasso1;
      PAS_tppPasso pPasso2;
      LIS_tpCondRet ret1 = LIS_CondRetOK;
      LIS_tpCondRet ret2 = LIS_CondRetOK;

      LIS_IrInicioLista(pPassos1);
      LIS_IrInicioLista(pPassos2);

      while (ret1 == LIS_CondRetOK && ret2 == LIS_CondRetOK)
      {
         int saoIguais;
         LIS_ObterValor(pPassos1, (void **) &pPasso1);
         LIS_ObterValor(pPassos2, (void **) &pPasso2);

         PAS_CompararPassos(pPasso1, pPasso2, &saoIguais);
         if (!saoIguais)
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

/**********Fim do módulo de implementação: TGRA Teste Grafo direcionado **********/

