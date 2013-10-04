#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "grafo.h"


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
static const char * TORNAR_ORIGEM_CMD    = "=tornarCorrOrigem"  ;

#define TRUE  1
#define FALSE 0

#define DIM_VT_GRAFO   10

#define VAZIO     0
#define NAO_VAZIO 1

static GRA_tppGrafo pGrafo;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( void * pValor );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  Fun��o: TGRA Tetar grafo
*
*     Comandos dispon�veis:
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
*     =tornarCorrOrigem             CondRetEsp
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
            } /* if */

            CondRet = GRA_DestruirGrafo(&pGrafo) ;

           return TST_CompararInt( CondRetEsp, CondRet, "Erro ao destruir grafo" ) ;

         }
     
   //   /* Testar inserir elemento antes */

   //      else if ( strcmp ( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
   //      {
   //         char dadoAInserir = 0;
         //char * pDado = ( char * ) malloc( sizeof( dadoAInserir ) );

   //         numLidos = LER_LerParametros( "ici", 
         //	&inxLista , &dadoAInserir, &CondRetEsp ) ;

         //*pDado = dadoAInserir;

   //         if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */
   //
   //         CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , pDado ) ;

   //         if ( CondRet != LIS_CondRetOK )
   //         {
   //             TST_NotificarFalha( "N�o foi possivel inserir elemento antes" ) ;
         //	return TST_CondRetErro;
   //         } /* if */

   //         return TST_CompararInt( CondRetEsp, CondRet , "Condicao de retorno errada ao inserir antes." ) ;

   //      } /* fim ativa: Testar inserir elemento antes */

   //   /* Testar inserir elemento apos */

   //      else if ( strcmp ( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
   //      {
         //char dadoAInserir = 0;
         //char * pDado = ( char * ) malloc( sizeof( dadoAInserir ) );

   //         numLidos = LER_LerParametros( "ici" , 
         //	  &inxLista, &dadoAInserir , &CondRetEsp ) ;

         //*pDado = dadoAInserir;

   //         if ( ( numLidos != 3 ) 
         //	|| ( ! ValidarInxLista ( inxLista, NAO_VAZIO ) ) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

   //         CondRet = LIS_InserirElementoApos( vtListas [ inxLista ], pDado ) ;

   //         if ( CondRet != LIS_CondRetOK )
   //         {
         //	TST_NotificarFalha ( "N�o foi possivel inserir elemento apos" ) ;
         //	return TST_CondRetErro;
   //         } /* if */

   //         return TST_CompararInt( CondRetEsp, CondRet, "Condicao de retorno errada ao inserir apos." ) ;

   //      } /* fim ativa: Testar inserir elemento apos */

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
   //                  "Condi��o de retorno errada ao excluir."   ) ;

   //      } /* fim ativa: Testar excluir simbolo */

       ///* Testar obter valor do elemento corrente */

   //      else if ( strcmp ( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
   //      {
         //char * pDadoObtido;
         //char dadoEsperado = 0;

   //         numLidos = LER_LerParametros("ici", 
         //	&inxLista , &dadoEsperado , &CondRetEsp ) ;

   //         if ( ( numLidos != 3 ) || ( ! ValidarInxLista ( inxLista, NAO_VAZIO ) ) )
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

   //         CondRet = LIS_ObterValor( vtListas[inxLista] , &pDadoObtido ) ;

         //if( CondRet != TST_CondOK )
         //{
         //	return CondRet;
         //}

         //return TST_CompararChar(dadoEsperado,*pDadoObtido,"Valor do elemento errado.");

   //      } /* fim ativa: Testar obter valor do elemento corrente */


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

     ///* LIS  &Avan�ar elemento */

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

   //      } /* fim ativa: LIS  &Avan�ar elemento */

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

   //      } /* fim ativa: LIS  &Avan�ar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Comparar valores
*
***********************************************************************/

   int CompararValores( void * pValor1 , void * pValor2 )
   {
      char valor1 = (char) * (char *) pValor1;
      char valor2 = (char) * (char *) pValor2;

      if ( valor1 > valor2 )
     {
        return 1;
     }
     
      if ( valor1 < valor2 )
     {
        return -1;
     }

     return 0;

   } /* Fim fun��o: TLIS -Comparar valores */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

   //int ValidarInxLista( int inxLista , int Modo )
   //{

   //   if ( ( inxLista <  0 )
   //     || ( inxLista >= DIM_VT_LISTA ))
   //   {
   //      return FALSE ;
   //   } /* if */
   //      
   //   if ( Modo == VAZIO )
   //   {
   //      if ( vtListas[ inxLista ] != 0 )
   //      {
   //         return FALSE ;
   //      } /* if */
   //   } else
   //   {
   //      if ( vtListas[ inxLista ] == 0 )
   //      {
   //         return FALSE ;
   //      } /* if */
   //   } /* if */
   //      
   //   return TRUE ;

   //} /* Fim fun��o: TLIS -Validar indice de lista */

/********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/

