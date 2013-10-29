/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*     "=criar"           - chama a fun��o TAB_CriarMatriz( )
*     "=irnorte"         - chama a fun��o TAB_IrNorte( )
*     "=irsul"           - chama a fun��o TAB_IrSul( )
*     "=ireste"          - chama a fun��o TAB_IrEste( )
*     "=iroeste"         - chama a fun��o TAB_IrOeste( )
*     "=irnordeste"      - chama a fun��o TAB_IrNordeste( )
*     "=irsudeste"       - chama a fun��o TAB_IrSudeste( )
*     "=irsudoeste"      - chama a fun��o TAB_IrSudoeste( )
*     "=irnoroeste"      - chama a fun��o TAB_IrNoroeste( )
*     "=atribuir" <Char> - chama a fun��o TAB_AtribuirValorCorr(  )
*     "=destroi"         - chama a fun��o TAB_DestruirMatriz( )
*     "=obter" <Char>    - chama a fun��o TAB_ObterValorCorr( ) e compara
*                          o valor retornado com o valor <Char>
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"
#include    "lista.h"

#include    "generico.h"
#include    "lerparm.h"

#include    "tabuleiro.h"
#include    "mem_manager.h"

/* Tabela dos nomes dos comandos de teste relacionados ao m�dulo */

#define     CRIAR_TAB_CMD       "=criar"
#define     OBTER_VAL_CMD       "=obter"
#define     ATRIBUIR_VAL_CMD    "=atribuir"
#define     DESTROI_CMD         "=destruir"

#define     IR_NORTE_CMD       "=irnorte"
#define     IR_SUL_CMD         "=irsul"
#define     IR_ESTE_CMD        "=ireste"
#define     IR_OESTE_CMD       "=iroeste"
#define     IR_NORDESTE_CMD    "=irnordeste"
#define     IR_SUDESTE_CMD     "=irsudeste"
#define     IR_SUDOESTE_CMD    "=irsudoeste"
#define     IR_NOROESTE_CMD    "=irnoroeste"
#define     IR_CASA_CMD    "=ircasa"


#define     FIM_CMD         "=fim"

/* Tabela dos nomes dos comandos de teste espec�ficos do teste */
#define     VALIDAR_EST_TAB_CMD "=validarEstrutura"
#define     SELECIONAR_CMD       "=selecionar"
#define     VALORES_SIZE 9
#define     TABULEIROES_SIZE 10


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
int IndiceDoValor( LIS_tppLista Valor );
void PreencherArrayDeValores();

static TAB_tpMatriz * Matrizes[TABULEIROES_SIZE] ;
static LIS_tppLista VALORES[VALORES_SIZE] ;

static int iMat = 0 ;

/***********************************************************************
*
*  $FC Fun��o: TTAB Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      TAB_tpCondRet CondRetObtido   = TAB_CondRetOK ;
      TAB_tpCondRet CondRetEsperada = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int IndiceValorEsperado = -1;
	  int IndiceValorObtido = -1;
	  int IndiceValorDado = -1;
	  
	  LIS_tppLista ValorObtido = NULL;

	  int Linhas = 0 ;
	  int Colunas = 0 ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;


	  PreencherArrayDeValores();

      /* Testar TAB Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_CriarTabuleiro( Matrizes + iMat ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." ) ;

         }


      /* Testar TAB Destruir matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_DestruirMatriz( Matrizes + iMat ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o � poss�vel destruir uma matriz que n�o existe.") ;

         } /* fim ativa: Testar TAB Destruir matriz */

		 
      /* Testar TAB Ir norte */

		 else if ( strcmp( ComandoTeste , IR_NORTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoNorte( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Norte.") ;

         } /* fim ativa: Testar TAB Ir norte */


		/* Testar TAB Ir sul */

		 else if ( strcmp( ComandoTeste , IR_SUL_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoSul( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Sul.") ;

         } /* fim ativa: Testar TAB Ir sul */


		/* Testar TAB Ir este */

		 else if ( strcmp( ComandoTeste , IR_ESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoEste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Este.") ;

         } /* fim ativa: Testar TAB Ir este */


		/* Testar TAB Ir oeste */

		 else if ( strcmp( ComandoTeste , IR_OESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoOeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Oeste.") ;

         } /* fim ativa: Testar TAB Ir oeste */

		 
		/* Testar TAB Ir nordeste */

		 else if ( strcmp( ComandoTeste , IR_NORDESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoNordeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Nordeste.") ;

         } /* fim ativa: Testar TAB Ir nordeste */


		/* Testar TAB Ir sudeste */

		 else if ( strcmp( ComandoTeste , IR_SUDESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoSudeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Sudeste.") ;

         } /* fim ativa: Testar TAB Ir sudeste */


		/* Testar TAB Ir sudoeste */

		 else if ( strcmp( ComandoTeste , IR_SUDOESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoSudoeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Sudoeste.") ;

         } /* fim ativa: Testar TAB Ir sudoeste */


		/* Testar TAB Ir noroeste */

		 else if ( strcmp( ComandoTeste , IR_NOROESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_IrNoNoroeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Noroeste.") ;

         }




		/* Testar TAB Ir casa */

		 else if ( strcmp( ComandoTeste , IR_CASA_CMD ) == 0 )
       {

         char *nome;
         MEM_Alloc(sizeof(char)*3, (void**) &nome);

			NumLidos = LER_LerParametros( "si", nome, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            }

			CondRetObtido = TAB_IrCasa(Matrizes[iMat], nome) ;

         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
								"N�o foi poss�vel ir para a casa.") ;

         }



      /* Testar Selecionar indice na array de matrizes */

         else if ( strcmp( ComandoTeste , SELECIONAR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &iMat ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( iMat < 0 || iMat > TABULEIROES_SIZE - 1 )
			{
				TST_NotificarFalha("S� � poss�vel fazer sele��o nos indices de 0 � 9") ;
				return TST_CondRetErro ;
			} /* if */

			return TST_CondRetOK ;

         }


      /* Testar Finalizar teste */

         else if ( strcmp( ComandoTeste , FIM_CMD ) == 0 )
         {
            MEM_LiberarTodaMemoriaAlocada();
            return TST_CondRetOK;
         }

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TTAB Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

int IndiceDoValor( LIS_tppLista Valor )
{
	int i;

	if ( Valor == NULL )
	{
		return -1;
	}

	for ( i = 0 ; i < VALORES_SIZE ; i++ )
	{
		if ( VALORES[i] == Valor )
		{
			return i;
		}
	}

	return -1;
}

void PreencherArrayDeValores()
{
	int i;

	if ( VALORES[0] != NULL )
	{
		return;
	}

	for ( i = 0 ; i < VALORES_SIZE ; i++ )
	{
		LIS_CriarLista( &VALORES[i], NULL, NULL );
	}
}