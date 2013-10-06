/***************************************************************************
* Módulo de implementação: TLIS Teste lista de símbolos
*
* Arquivo gerado:              test_lis.c
* Letras identificadoras:      TLIS
*
* Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
* Autores:
*   - rc: Robert Corrêa
*   - hg: Hugo Roque
*
* Histórico de evolução:
*    Versão  Autor    Data     Observações
*    1.0     rc    12/set/2013 Adaptação da função CriarLista para ser testavel e testes para inserção de somente valores char.
*    2.0     rc    15/set/2013 Implementação e adaptação do restante das funções de teste para testar somente dado o tipo char.
*    3.0     hg    10/out/2013 Adaptação do módulo para trabalhar com uma lista cujos valores terão um tipo qualquer.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"


static const char CRIAR_LISTA_CMD         [] = "=criarlista"    ;
static const char DESTRUIR_LISTA_CMD      [] = "=destruirlista" ;
static const char ESVAZIAR_LISTA_CMD      [] = "=esvaziarlista" ;
static const char INS_ELEM_ANTES_CMD      [] = "=inselemantes"  ;
static const char INS_ELEM_APOS_CMD       [] = "=inselemapos"   ;
static const char OBTER_VALOR_CMD         [] = "=obtervalorelem";
static const char EXC_ELEM_CMD            [] = "=excluirelem"   ;
static const char IR_INICIO_CMD           [] = "=irinicio"      ;
static const char IR_FIM_CMD              [] = "=irfinal"       ;
static const char AVANCAR_ELEM_CMD        [] = "=avancarelem"   ;
static const char PROCURAR_ELEM_CMD       [] = "=procurarelem"  ;
static const char ESTA_VAZIA_CMD          [] = "=estavazia"     ;
static const char NUM_ELEMENTOS_CMD       [] = "=numelementos"  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[DIM_VT_LISTA];

/*****Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor(void *pValor);
   
   static int CompararValores(void *pValor1, void *pValor2);

   static int ValidarInxLista(int inxLista, int Modo);

/***** Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
* Função: TLIS Testar lista
*
* Descrição da função
*    Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*    Comandos disponíveis:
*
*    =criarlista                   inxLista  CondRetEsp
*    =destruirlista                inxLista  CondRetEsp
*    =esvaziarlista                inxLista  CondRetEsp
*    =inselemantes                 inxLista  char  CondRetEsp
*    =inselemapos                  inxLista  char  CondRetEsp
*    =obtervalorelem               inxLista  char  CondRetEsp
*    =excluirelem                  inxLista  CondRetEsp
*    =irinicio                     inxLista  CondRetEsp
*    =irfinal                      inxLista  CondRetEsp
*    =avancarelem                  inxLista  numElem CondRetEsp
*    =procurarelem                 inxLista  char    CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
   {
      int inxLista   = -1,
          numLidos   = -1,
          CondRetEsp = -1;

      TST_tpCondRet CondRet;
      LIS_tppLista ppLista = NULL;

      /*Testar CriarLista */

         if (strcmp(ComandoTeste, CRIAR_LISTA_CMD) == 0)
         {
            numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

            if ((numLidos != 2) || (! ValidarInxLista (inxLista, VAZIO)))
            {
               return TST_CondRetParm;
            }

            CondRet = LIS_CriarLista(&ppLista, DestruirValor, CompararValores);

            if(CondRet ==  LIS_CondRetOK)
            {
               vtListas[inxLista] = ppLista;
               return TST_CompararPonteiroNulo(1,vtListas[inxLista], "Erro em ponteiro de nova lista.");
            }

            return TST_CondRetErro;
         }

       /*Testar Destruir lista */

         else if (strcmp(ComandoTeste, DESTRUIR_LISTA_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

            if ((numLidos != 2) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            CondRet = LIS_DestruirLista(vtListas[inxLista]);
            vtListas[inxLista] = NULL;

            return TST_CompararInt(CondRetEsp, CondRet, "Erro ao destruir lista");

         }
     
      /*Testar inserir elemento antes */

         else if (strcmp (ComandoTeste, INS_ELEM_ANTES_CMD) == 0)
         {
            char dadoAInserir = 0;
            char *pDado = (char *) malloc(sizeof(dadoAInserir));

            numLidos = LER_LerParametros("ici", &inxLista, &dadoAInserir, &CondRetEsp);

            *pDado = dadoAInserir;

            if ((numLidos != 3) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }
   
            CondRet = LIS_InserirElementoAntes(vtListas[inxLista], pDado);

            if (CondRet != LIS_CondRetOK)
            {
                TST_NotificarFalha("Não foi possivel inserir elemento antes");
                return TST_CondRetErro;
            }

            return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao inserir antes.");

         }

      /*Testar inserir elemento apos */

         else if (strcmp (ComandoTeste, INS_ELEM_APOS_CMD) == 0)
         {
         char dadoAInserir = 0;
         char *pDado = (char *) malloc(sizeof(dadoAInserir));

            numLidos = LER_LerParametros("ici", &inxLista, &dadoAInserir, &CondRetEsp);

         *pDado = dadoAInserir;

            if ((numLidos != 3) || (! ValidarInxLista (inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            CondRet = LIS_InserirElementoApos(vtListas [inxLista], pDado);

            if (CondRet != LIS_CondRetOK)
            {
               TST_NotificarFalha ("Não foi possivel inserir elemento apos");
               return TST_CondRetErro;
            }

            return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao inserir apos.");

         }

        /*Testar excluir simbolo */

         else if (strcmp(ComandoTeste, EXC_ELEM_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

            if ((numLidos != 2) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            return TST_CompararInt(CondRetEsp,
                      LIS_ExcluirElemento(vtListas[inxLista]),
                     "Condição de retorno errada ao excluir.");

         }

       /*Testar obter valor do elemento corrente */

         else if (strcmp (ComandoTeste, OBTER_VALOR_CMD) == 0)
         {
            char *pDadoObtido;
            char dadoEsperado = 0;

            numLidos = LER_LerParametros("ici", &inxLista, &dadoEsperado, &CondRetEsp);

            if ((numLidos != 3) || (! ValidarInxLista (inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            CondRet = LIS_ObterValor(vtListas[inxLista], &pDadoObtido);

            if(CondRet != TST_CondOK)
            {
               return CondRet;
            }

            return TST_CompararChar(dadoEsperado,*pDadoObtido,"Valor do elemento errado.");

         }


       /*Testar ir para o elemento inicial */

         else if (strcmp(ComandoTeste, IR_INICIO_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

            if ((numLidos != 2) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            LIS_IrInicioLista(vtListas[inxLista]);

            return TST_CompararInt(CondRetEsp,
                                   LIS_IrInicioLista(vtListas[inxLista]),
                                   "Erro ao ir para o inicio da lista");

         }

        /*Testar ir para o elemento final */

         else if (strcmp(ComandoTeste, IR_FIM_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

            if ((numLidos != 2) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            return TST_CompararInt(CondRetEsp,
                                   LIS_IrFinalLista(vtListas[inxLista]),
                                   "Erro ao ir para o final da lista");

         }

       /*Testar Esvaziar lista lista */

         else if (strcmp(ComandoTeste, ESVAZIAR_LISTA_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii", &inxLista, &CondRetEsp);

            if ((numLidos != 2) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            return TST_CompararInt(CondRetEsp,
                                   LIS_EsvaziarLista(vtListas[inxLista]),
                                   "Erro ao esvaziar a lista");

         }

     /* Testar avançar elemento */

         else if (strcmp(ComandoTeste, AVANCAR_ELEM_CMD) == 0)
         {
            int numElem = -1;

            numLidos = LER_LerParametros("iii", &inxLista, &numElem, &CondRetEsp);

            if ((numLidos != 3) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            return TST_CompararInt(CondRetEsp,
                      LIS_AvancarElementoCorrente(vtListas[inxLista], numElem),
                      "Condicao de retorno errada ao avancar");

         }

        /* Testar Procurar elemento */

         else if (strcmp(ComandoTeste, PROCURAR_ELEM_CMD) == 0)
         {
         char dadoASerProcurado = -1;

            numLidos = LER_LerParametros("ici", &inxLista, &dadoASerProcurado, &CondRetEsp);

            if ((numLidos != 3) || (! ValidarInxLista(inxLista, NAO_VAZIO)))
            {
               return TST_CondRetParm;
            }

            return TST_CompararInt(CondRetEsp,
                      LIS_ProcurarValor(vtListas[inxLista], &dadoASerProcurado),
                      "Condicao de retorno errada ao avancar");

         }

        /* Testar está vazia */

       else if (strcmp(ComandoTeste, ESTA_VAZIA_CMD) == 0)
       {
          int resposta = -1;
          int respostaEsperada = -1;

          numLidos = LER_LerParametros("iii", &inxLista, &respostaEsperada,
             &CondRetEsp);

          if ((numLidos != 3)
             || (! ValidarInxLista(inxLista, NAO_VAZIO)))
          {
             return TST_CondRetParm;
          }

          CondRet = LIS_EstaVazia(vtListas[inxLista], &resposta);

          if(resposta == respostaEsperada)
          {
            return TST_CompararInt(CondRetEsp, CondRet, "Erro ao checar se a lista esta vazia");
          }
          
          return TST_NotificarFalha("Retorno da funcao LIS_EstaVazia nao corresponde ao valor esperado");

       }

        /*LIS  & Num Elementos */

       else if (strcmp(ComandoTeste, NUM_ELEMENTOS_CMD) == 0)
       {
          int numDeElementos = -1;
          int numDeElementosEsperados = -1;

          numLidos = LER_LerParametros("iii", &inxLista, &numDeElementosEsperados,
             &CondRetEsp);

          if ((numLidos != 3)
             || (! ValidarInxLista(inxLista, NAO_VAZIO)))
          {
             return TST_CondRetParm;
          }

          CondRet = LIS_NumELementos(vtListas[inxLista], &numDeElementos);

          if(numDeElementos == numDeElementosEsperados)
          {
            return TST_CompararInt(CondRetEsp, CondRet, "Erro ao checar se a lista esta vazia");
          }
          
          return TST_NotificarFalha("Retorno da funcao LIS_EstaVazia nao corresponde ao valor esperado");

       }

      return TST_CondRetNaoConhec;

   }


/***** Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
* Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor(void *pValor)
   {

      free(pValor);

   }


/***********************************************************************
*
* Função: TLIS -Comparar valores
*
***********************************************************************/

   int CompararValores(void *pValor1, void *pValor2)
   {
      char valor1 = (char) *(char *) pValor1;
      char valor2 = (char) *(char *) pValor2;

     if (valor1 > valor2)
     {
        return 1;
     }
     
     if (valor1 < valor2)
     {
        return -1;
     }

     return 0;

   }


/***********************************************************************
*
* Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista(int inxLista, int Modo)
   {

      if ((inxLista <  0) || (inxLista >= DIM_VT_LISTA))
      {
         return FALSE;
      }
         
      if (Modo == VAZIO)
      {
         if (vtListas[inxLista] != 0)
         {
            return FALSE;
         }
      } else
      {
         if (vtListas[inxLista] == 0)
         {
            return FALSE;
         }
      }
         
      return TRUE;

   }

/**********Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

