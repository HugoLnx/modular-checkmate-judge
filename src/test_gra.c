#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "grafo.h"
#include    "conteudo.h"


static const char * CRIAR_GRAFO_CMD      = "=criarGrafo"        ;
static const char * DESTRUIR_GRAFO_CMD   = "=destruirGrafo"     ;
static const char * INS_VERT_CMD         = "=insVertice"        ;
static const char * INS_ARESTA_CMD       = "=insAresta"         ;
static const char * OBTER_VALOR_CMD      = "=obterValor"        ;
static const char * ALTER_VALOR_CMD      = "=alterarValor"      ;
static const char * EXC_VERT_CMD         = "=excluirVertice"    ;
static const char * IR_ORIGEM_CMD        = "=irOrigem"          ;
static const char * IR_VERTICE_CMD       = "=irVertice"         ;
static const char * IR_ARESTA_CMD        = "=irPelaAresta"      ;
static const char * DESTRUIR_VERT_CMD    = "=destruirCorr"      ;
static const char * DESTRUIR_ARESTA_CMD  = "=destruirAresta"    ;
static const char * TORNAR_ORIGEM_CMD    = "=tornarOrigem"  ;

#define TRUE  1
#define FALSE 0
#define MAX_CHARS_NOME 3

#define DIM_VT_GRAFO   10

#define VAZIO     0
#define NAO_VAZIO 1

static GRA_tppGrafo pGrafo;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor(void *pValor);
   static char* AlocarEspacoParaNome();

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  Função: TGRA Testar grafo
*
*     Comandos disponíveis:
*
*     =criarGrafo                   CondRetEsp
*     =destruirGrafo                CondRetEsp
*     =insVertice                   nome valor   CondRetEsp
*     =insAresta                    nome vertice CondRetEsp
*     =obterValor                   string CondRetEsp
*     =alterarValor                 string CondRetEsp
*     =excluirVertice               CondRetEsp
*     =irOrigem                     nome CondRetEsp
*     =irVertice                    nome CondRetEsp
*     =irPelaAresta                 nome CondRetEsp
*     =destruirCorr                 CondRetEsp
*     =destruirAresta               nome CondRetEsp
*     =tornarOrigem                 CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
      int inxGrafo   = -1,
          numLidos   = -1,
          CondRetEsp = -1;

      TST_tpCondRet CondRet;

      /* Testar CriarGrafo */

         if ( strcmp ( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp );

            if (numLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRet = GRA_CriarGrafo( &pGrafo , DestruirValor );

            if( CondRet ==  GRA_CondRetOK )
            {
               CondRet = TST_CompararPonteiroNulo(1 , pGrafo , "Erro em ponteiro de nova lista." ) ;
               return CondRet;
            }

            return TST_CondRetErro;

         }

       /* Testar Destruir grafo */

         else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if (numLidos != 1)
            {
               return TST_CondRetParm ;
            }

            CondRet = GRA_DestruirGrafo(&pGrafo) ;

           return TST_CompararInt( CondRetEsp, CondRet, "Erro ao destruir grafo" ) ;

         }
     
      /* Testar inserir vertice */

         else if (strcmp(ComandoTeste, INS_VERT_CMD) == 0)
         {
            char *pNome = AlocarEspacoParaNome();
            char *pDado = AlocarEspacoParaNome();
            CON_tppConteudo pConteudo;

            numLidos = LER_LerParametros( "ssi", pNome, pDado, &CondRetEsp );

            if (numLidos != 3)
            {
               return TST_CondRetParm;
            }
   
            CON_CriarConteudo(&pConteudo, pDado);

            CondRet = GRA_InserirVertice(pGrafo, pNome, pConteudo);

            return TST_CompararInt( CondRetEsp, CondRet , "Condicao de retorno errada ao inserir vértice." ) ;

         }
    
      /* Testar inserir aresta */

         else if (strcmp(ComandoTeste, INS_ARESTA_CMD) == 0)
         {
            char *pNomeAresta = AlocarEspacoParaNome();
            char *pNomeVertice = AlocarEspacoParaNome();

            numLidos = LER_LerParametros( "ssi", pNomeAresta, pNomeVertice, &CondRetEsp );

            if (numLidos != 3)
            {
               return TST_CondRetParm;
            }
   
            CondRet = GRA_InserirArestaDoCorrentePara(pGrafo, pNomeAresta, pNomeVertice);

            return TST_CompararInt( CondRetEsp, CondRet , "Condicao de retorno errada ao inserir aresta." ) ;
         }

      /* Testar obter valor do vértice corrente */

         else if (strcmp(ComandoTeste, OBTER_VALOR_CMD) == 0)
         {
            CON_tppConteudo pConteudoObtido;
            char *pDadoEsperado = AlocarEspacoParaNome();
            char *pDadoObtido;

            numLidos = LER_LerParametros("si", pDadoEsperado , &CondRetEsp);

            if (numLidos != 2)
            {
               return TST_CondRetParm;
            }

            CondRet = GRA_ObterConteudoCorrente(pGrafo, (void**) &pConteudoObtido);

            CON_ObterValorDoConteudo(pConteudoObtido, &pDadoObtido);

            if(CondRet != TST_CondOK)
            {
         	   return TST_NotificarFalha("Um erro ocorreu ao obter o valor.");
            }

            return TST_CompararString(pDadoEsperado, pDadoObtido, "Valor do elemento errado.");
         }

       /* Testar alterar valor do vértice corrente */

         else if (strcmp(ComandoTeste, ALTER_VALOR_CMD) == 0)
         {
            char *pNovoValor = AlocarEspacoParaNome();
            CON_tppConteudo pNovoConteudo;

            numLidos = LER_LerParametros("si", pNovoValor , &CondRetEsp);

            if (numLidos != 2)
            {
               return TST_CondRetParm;
            }

            CON_CriarConteudo(&pNovoConteudo, pNovoValor);

            CondRet = GRA_AlterarConteudoCorrente(pGrafo, pNovoConteudo);

            // TODO: liberar o espaço do antigo corrente?

            return TST_CompararInt(TST_CondOK, CondRet, "Ocorreu um erro ao alterar o valor.");
         }


       /* Testar tornar corrente uma origem */

         else if (strcmp(ComandoTeste, TORNAR_ORIGEM_CMD) == 0)
         {
            numLidos = LER_LerParametros("i", &CondRetEsp);

            if (numLidos != 1)
            {
               return TST_CondRetParm;
            }

            CondRet = GRA_TornarCorrenteUmaOrigem(pGrafo);

            return TST_CompararInt(TST_CondOK, CondRet, "Ocorreu um erro ao tornar o corrente uma origem.");
         }

       // /* Testar excluir simbolo */

   //      else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
   //      {

   //         numLidos = LER_LerParametros( "ii" ,
   //               &inxLista , &CondRetEsp ) ;

   //         if ( ( numLidos != 2 )
   //           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

   //         return TST_CompararInt( CondRetEsp ,
   //                   LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
   //                  "Condição de retorno errada ao excluir."   ) ;

   //      } /* fim ativa: Testar excluir simbolo */

       ///* Testar ir para o elemento inicial */

   //      else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
   //      {

   //         numLidos = LER_LerParametros( "ii" ,
         //	&inxLista, &CondRetEsp ) ;

   //         if ( ( numLidos != 2 )
   //           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

   //         LIS_IrInicioLista( vtListas[ inxLista ] ) ;

         //return TST_CompararInt(CondRetEsp, LIS_IrInicioLista( vtListas[ inxLista ] ), "Erro ao ir para o inicio da lista" );

   //      } /* fim ativa: Testar ir para o elemento inicial */

       // /* LIS  &Ir para o elemento final */

   //      else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
   //      {

   //         numLidos = LER_LerParametros( "ii" , 
         //	&inxLista ,  &CondRetEsp) ;

   //         if ( ( numLidos != 2 )
   //           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

   //         return TST_CompararInt(CondRetEsp, LIS_IrFinalLista( vtListas[ inxLista ] ), "Erro ao ir para o final da lista" );

   //      } /* fim ativa: LIS  &Ir para o elemento final */

       ///* Testar Esvaziar lista lista */

   //      else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
   //      {

   //         numLidos = LER_LerParametros( "ii" ,
         //	&inxLista , &CondRetEsp ) ;

   //         if ( ( numLidos != 2 )
   //           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

         //return TST_CompararInt(CondRetEsp, LIS_EsvaziarLista( vtListas[ inxLista ] ), "Erro ao esvaziar a lista" ) ;

   //      } /* fim ativa: Testar Esvaziar lista lista */

     ///* LIS  &Avançar elemento */

   //      else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
   //      {
         // int numElem = -1;

   //         numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
   //                             &CondRetEsp ) ;

   //         if ( ( numLidos != 3 )
   //           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

   //         return TST_CompararInt( CondRetEsp ,
   //                   LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
   //                   "Condicao de retorno errada ao avancar" ) ;

   //      } /* fim ativa: LIS  &Avançar elemento */

       // /* LIS  &Procurar elemento */

   //      else if ( strcmp( ComandoTeste , PROCURAR_ELEM_CMD ) == 0 )
   //      {
         //char dadoASerProcurado = -1;

   //         numLidos = LER_LerParametros( "ici" , &inxLista , &dadoASerProcurado ,
   //                             &CondRetEsp ) ;

   //         if ( ( numLidos != 3 )
   //           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

   //         return TST_CompararInt( CondRetEsp ,
   //                   LIS_ProcurarValor(vtListas[ inxLista ], &dadoASerProcurado),
   //                   "Condicao de retorno errada ao avancar" ) ;

   //      } /* fim ativa: LIS  &Avançar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor(void *pValor)
   {
      CON_DestruirConteudo((CON_tppConteudo*) &pValor);
   }

   char* AlocarEspacoParaNome()
   {
      return (char*) malloc(sizeof(char)*(MAX_CHARS_NOME+1));
   }

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

